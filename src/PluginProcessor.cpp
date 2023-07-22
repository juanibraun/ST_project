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
, markovModel{}, conductor()
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
    position = 0;
}

void MidiMarkovProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    conductor.clearNotes();
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
    

    
    if (midiToProcess.getNumEvents() > 0){
        midiMessages.addEvents(midiToProcess, midiToProcess.getFirstEventTime(), midiToProcess.getLastEventTime()+1, 0);
        midiToProcess.clear();
    }
    
    juce::AudioPlayHead::CurrentPositionInfo position_info;
    if (auto* playHead = getPlayHead()){
        playHead->getCurrentPosition(position_info);
    }
    
    juce::MidiBuffer generatedMessages{};

    for (const auto metadata : midiMessages){
        
        auto message = metadata.getMessage();
      
        if (message.isNoteOn()){
            
            //std::cout << "timeSamp: " << message.getTimeStamp() << std::endl;
            conductor.addNoteOn(message.getNoteNumber(), message.getVelocity(),position_info.timeInSeconds);
        }
        if (message.isNoteOff()){
            
            conductor.addNoteOff(message.getNoteNumber(),position_info.timeInSeconds);
            //listener.printSize();
            //std::string state = conductor.generateEvent();
            //markovModel.putEvent(state);
            //std::cout << state << std::endl;
        }

        
    }
    // optionally wipe out the original messsages
    if (position_info.ppqPosition >= 10){
        while (conductor.availableEvents()){
            
            
            std::string event = conductor.generateEvent();
            
            //std::string event = markovModel.getEvent(true); //  true means it only selects from states having at least 2 observations
            
            //std::cout << "release: mark note " << event << " order " << markovModel.getOrderOfLastEvent()<< std::endl;
            
            note n = conductor.readEvent(event);
            
            std::cout<< "Read Event: "<<  n.note << "," << n.velocity << "," << n.start + position_info.timeInSeconds << "," << n.duration << std::endl;
            
            juce::MidiMessage nOn = juce::MidiMessage::noteOn(1, n.note, (uint8_t)n.velocity);
            generatedMessages.addEvent(nOn, (n.start + position_info.timeInSeconds) * getSampleRate());
            
            juce::MidiMessage nOff = juce::MidiMessage::noteOff(1, n.note, (uint8_t)n.velocity);
            generatedMessages.addEvent(nOff,n.start + position_info.timeInSamples + n.duration);
        }
    }
    midiMessages.clear();
    //std::cout << generatedMessages.getFirstEventTime() << std::endl;
    midiMessages.addEvents(generatedMessages, generatedMessages.getFirstEventTime(), -1, 0);
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


