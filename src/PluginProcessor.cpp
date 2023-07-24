/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiMarkovProcessor::MidiMarkovProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
, markovModel_notes{}, markovModel_triggers(), conductor()
{

}


MidiMarkovProcessor::~MidiMarkovProcessor()
{
}

//==============================================================================
const juce::String MidiMarkovProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiMarkovProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiMarkovProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiMarkovProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiMarkovProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiMarkovProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiMarkovProcessor::getCurrentProgram()
{
    return 0;
}

void MidiMarkovProcessor::setCurrentProgram (int index)
{
}

const juce::String MidiMarkovProcessor::getProgramName (int index)
{
    return {};
}

void MidiMarkovProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidiMarkovProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    sample_rate = sampleRate;
    conductor.setTimeOffset(4);
    conductor.setDuration(1);
     
    
}

void MidiMarkovProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    conductor.clearNotes();
    generatedMessages.clear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiMarkovProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiMarkovProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    ////////////
    // deal with MIDI
    
    // transfer any pending notes into the midi messages and
    // clear pending - these messages come from the addMidi function
    // which the UI might call to send notes from the piano widget
    
    auto numSamples = buffer.getNumSamples();
    
    if (midiToProcess.getNumEvents() > 0){
        midiMessages.addEvents(midiToProcess, midiToProcess.getFirstEventTime(), midiToProcess.getLastEventTime()+1, 0);
        midiToProcess.clear();
    }
    
    //Get position in the host
    juce::AudioPlayHead::CurrentPositionInfo position_info;
    if (auto* playHead = getPlayHead()){
        playHead->getCurrentPosition(position_info);
    }
    if (!position_info.isPlaying){
        conductor.clearNotes();
    }
    
    // Read incoming MIDI buffer and add notes to conductor
    // /*
    for (const auto metadata : midiMessages){
        
        auto message = metadata.getMessage();
        if (message.isNoteOn()){
            conductor.addNoteOn(message.getNoteNumber(), message.getVelocity(), position_info.timeInSeconds);
        }
        if (message.isNoteOff()){
            conductor.addNoteOff(message.getNoteNumber(),position_info.timeInSeconds);
        }
    }
    
    midiMessages.clear(); // Clear the midi buffer bc already copied input notes to conductor
    
    if(markov){
        if (conductor.availableEvents()){
            splitted_event event = conductor.generateSplittedEvent();
            markovModel_notes.putEvent(event.note);
            markovModel_triggers.putEvent(event.trigger);
        }
        
        int sample_offset = (int)(60 / position_info.bpm * conductor.getTimeOffset() * sample_rate);
        
        if ( (false) ){
            std::cout << "starting time: " << (float)(60 / position_info.bpm * conductor.getTimeOffset()) << std::endl;
            
            std::cout << "sample offset: "<< sample_offset << ", current position: "<< position_info.timeInSamples << std::endl;
        }
        
        if (position_info.timeInSamples > sample_offset)
        {
            // Check if conductor has something to play
            std::string markov_event = markovModel_notes.getEvent(true);
            std::cout << "release: mark note " << markov_event << " order " << markovModel_notes.getOrderOfLastEvent()<< std::endl;
            
            note n = conductor.readEvent(markov_event);
            n.start = std::stod(markovModel_triggers.getEvent(true)); 
                
            juce::MidiMessage nOn = juce::MidiMessage::noteOn(1, n.note, (uint8_t)n.velocity);
            auto sampleNumber =  (int) (sample_offset + (n.start) * sample_rate);
            generatedMessages.addEvent(nOn,sampleNumber);
                 
            juce::MidiMessage nOff = juce::MidiMessage::noteOff(1, n.note, (uint8_t)n.velocity);
            sampleNumber =  (int) (sample_offset + (n.start + n.duration) * sample_rate);
            generatedMessages.addEvent(nOff,sampleNumber);

            
            // //  true means it only selects from states having at least 2 observations
            
            //std::cout << "release: mark note " << event << " order " << markovModel.getOrderOfLastEvent()<< std::endl;
            
            //std::cout<< "Read Event: "<<  n.note << "," << n.velocity << "," << n.start + position_info.timeInSeconds << "," << n.duration << std::endl;
            
        }
    }else{

        int sample_offset = (int)(60 / position_info.bpm * conductor.getTimeOffset() * sample_rate);
        
        if ( (false) ){
            std::cout << "starting time: " << (float)(60 / position_info.bpm * conductor.getTimeOffset()) << std::endl;
            
            std::cout << "sample offset: "<< sample_offset << ", current position: "<< position_info.timeInSamples << std::endl;
        }
        
        if (position_info.timeInSamples > sample_offset)
        {
            // Check if conductor has something to play
            if (conductor.availableEvents()){
                std::string event = conductor.generateEvent();
                
                note n = conductor.readEvent(event);
                
                juce::MidiMessage nOn = juce::MidiMessage::noteOn(1, n.note, (uint8_t)n.velocity);
                auto sampleNumber =  (int) (sample_offset + (n.start) * sample_rate);
                generatedMessages.addEvent(nOn,sampleNumber);
                
                juce::MidiMessage nOff = juce::MidiMessage::noteOff(1, n.note, (uint8_t)n.velocity);
                sampleNumber =  (int) (sample_offset + (n.start + n.duration) * sample_rate);
                generatedMessages.addEvent(nOff,sampleNumber);
            }
        }
    }
    

    

    
    // Dummy version - copy from one buffer to the other while delaying
    /*
    int sample_offset = (int)(60 / position_info.bpm * conductor.getTimeOffset() * sample_rate);
    for (const auto metadata : midiMessages){
        
        auto message = metadata.getMessage();
        
        if (message.isNoteOn()){
            
            juce::MidiMessage nOn = juce::MidiMessage::noteOn(1, message.getNoteNumber() , (uint8_t)message.getVelocity());
            auto sampleNumber =  (int) (position_info.timeInSamples + sample_offset);
            generatedMessages.addEvent(nOn,sampleNumber);
        }
        
        if (message.isNoteOff()){
            
            juce::MidiMessage nOff = juce::MidiMessage::noteOff(1, message.getNoteNumber() , (uint8_t)message.getVelocity());
            auto sampleNumber =  (int) (position_info.timeInSamples + sample_offset);
            generatedMessages.addEvent(nOff,sampleNumber);
        }
    }
    
    midiMessages.clear();
    */
    
    // Add messages to midiBuffer whose sample value is whithin the current buffer
    
    for (const auto metadata : generatedMessages){
        if ( (false) ){
            std::cout << metadata.getMessage().getDescription() << " Sample position: " << metadata.samplePosition << std::endl;
            std::cout <<"max sample of buffer " << position_info.timeInSamples << std::endl;
        }
        if (metadata.samplePosition > position_info.timeInSeconds * sample_rate)
                    break;
        auto message = metadata.getMessage();
        midiMessages.addEvent(message,metadata.samplePosition);
        //std::cout << metadata.getMessage().getDescription() << " Sample position: " << metadata.samplePosition << std::endl;
    }
    
    

 
    //std::cout << generatedMessages.getNumEvents()<< std::endl;
    // Erase past messages
    generatedMessages.clear(0, (juce::int32) (position_info.timeInSeconds * sample_rate) );
    

    
    //std::cout << " Generated messages buffer size: " << generatedMessages.getNumEvents() << std::endl;
        
}


//==============================================================================
bool MidiMarkovProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidiMarkovProcessor::createEditor()
{
    return new MidiMarkovEditor (*this);
}

//==============================================================================
void MidiMarkovProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiMarkovProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiMarkovProcessor();
}


void MidiMarkovProcessor::addMidi(juce::MidiMessage msg, int sampleOffset)
{
  
    midiToProcess.addEvent(msg, sampleOffset);
}


void MidiMarkovProcessor::setOffset(double ofs){
    offset = ofs;
    conductor.setTimeOffset((int)offset);
    
}
void MidiMarkovProcessor::setDuration(double dur){
    duration = dur;
        conductor.setDuration(duration);
    
}

void MidiMarkovProcessor::markov_on_off(bool state){
    markov = state;
}
