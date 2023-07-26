/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "MarkovManager.h"
#include "Conductor.h"


//==============================================================================
/**
*/
class MidiMarkovProcessor  : public juce::AudioProcessor
                                #if JucePlugin_Enable_ARA
                                    , public juce::AudioProcessorARAExtension
                                #endif
{
public:
    //==============================================================================
    MidiMarkovProcessor();
    ~MidiMarkovProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    /** add some midi to be played at the sent sample offset*/
    void addMidi(juce::MidiMessage msg, int sampleOffset);
    
    void setOffset(double ofs);
    double getOffset();
    
    void setDuration(double dur);
    double getDuration();
    
    void markov_on_off(bool state);
    bool getMarkov_on_off();
    
private:

    MarkovManager markovModel_notes;
    MarkovManager markovModel_triggers;
    Conductor conductor;
    /** stores messages added from the addMidi function*/
    juce::MidiBuffer midiToProcess;
    
    juce::MidiBuffer generatedMessages;
    
    bool markov;
    double sample_rate;
    double offset;
    double duration;
    
    juce::int64 lastSample;

    
    


      //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMarkovProcessor)
};
