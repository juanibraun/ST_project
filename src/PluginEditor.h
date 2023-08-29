/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>



//==============================================================================
/**
*/
class MidiMarkovEditor  :  public juce::AudioProcessorEditor,
                          // listen to buttons
                          public juce::Button::Listener, 
                          // listen to sliders
                          public juce::Slider::Listener

{
public:
    MidiMarkovEditor (MidiMarkovProcessor&);
    ~MidiMarkovEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged (juce::Slider *slider) override;
    void buttonClicked(juce::Button* btn) override;
    // from MidiKeyboardState
    void updateToggleState (juce::Button* button);
    


private:
    
    juce::Image background;
    juce::Slider offset_slider;
    juce::Label offset_label;
    juce::Slider duration_slider;
    juce::Label duration_label;
    juce::ToggleButton markov_on_off;
    juce::Label markov_on_off_label;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiMarkovProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMarkovEditor)
};
