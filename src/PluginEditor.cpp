/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiMarkovEditor::MidiMarkovEditor (MidiMarkovProcessor& p)
: AudioProcessorEditor (&p), miniPianoKbd{kbdState, juce::MidiKeyboardComponent::horizontalKeyboard},
audioProcessor (p)

{    


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 450);

    // listen to the mini piano
    kbdState.addListener(this);  
    addAndMakeVisible(miniPianoKbd);
    
    addAndMakeVisible(offset_slider);
    offset_slider.setRange(0,12,1);
    offset_slider.setValue(4);
    offset_slider.setTextValueSuffix (" quarters");
    offset_slider.addListener(this);
    addAndMakeVisible (offset_label);
    offset_label.setText ("Offset", juce::dontSendNotification);
    offset_label.attachToComponent (&offset_slider, false);
    
    addAndMakeVisible(duration_slider);
    duration_slider.setRange(0,2,0.125);
    duration_slider.setValue(1);
    duration_slider.setTextValueSuffix (" times");
    duration_slider.addListener(this);
    addAndMakeVisible (duration_label);
    duration_label.setText ("Duration", juce::dontSendNotification);
    duration_label.attachToComponent (&duration_slider, false);
    
    addAndMakeVisible(markov_on_off);
    markov_on_off.setClickingTogglesState(true);
    markov_on_off.onClick = [this] { updateToggleState(&markov_on_off);};
    addAndMakeVisible(markov_on_off_label);
    markov_on_off_label.setText ("Markov OFF", juce::dontSendNotification);
    markov_on_off_label.attachToComponent (&markov_on_off, false);

}

MidiMarkovEditor::~MidiMarkovEditor()
{
}

//==============================================================================
void MidiMarkovEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    background = juce::ImageCache::getFromMemory(BinaryData::background_jpg,BinaryData::background_jpgSize);
   
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

   // g.setColour (juce::Colours::white);
   // g.setFont (15.0f);
   // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MidiMarkovEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    float rowHeight = getHeight()/5;
    
    auto sliderRight = 200;
    auto btnLeft = 50;
    //offset_slider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    offset_slider.setBounds(getWidth() - sliderRight, getHeight() - 2 * rowHeight, getWidth()/4, 20);
    duration_slider.setBounds (getWidth() - sliderRight, getHeight() - 2 * rowHeight + 50,  getWidth()/4, 20);

    markov_on_off.setBounds(btnLeft/2, rowHeight/2, 2*btnLeft, 20);
    
    miniPianoKbd.setBounds(0,getHeight()-rowHeight, getWidth(), rowHeight);
    
}

 void MidiMarkovEditor::sliderValueChanged (juce::Slider *slider)
{
     if (slider == &offset_slider){
         audioProcessor.setOffset(offset_slider.getValue());
         
     }

     else if (slider == &duration_slider){
         audioProcessor.setDuration(duration_slider.getValue());
     }
                
}

void MidiMarkovEditor::buttonClicked(juce::Button* btn)
{
}

void MidiMarkovEditor::handleNoteOn(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
    juce::MidiMessage msg1 = juce::MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity);
    audioProcessor.addMidi(msg1, 0);
    
}

void MidiMarkovEditor::handleNoteOff(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
    juce::MidiMessage msg2 = juce::MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity);
    audioProcessor.addMidi(msg2, 0); 
}


void MidiMarkovEditor::updateToggleState (juce::Button* button){
    audioProcessor.markov_on_off(button->getToggleState());
    std::cout << button->getToggleState() << std::endl;
    if(button->getToggleState()){
        markov_on_off_label.setText ("Markov ON", juce::dontSendNotification);
    }else{
        markov_on_off_label.setText ("Markov OFF", juce::dontSendNotification);
    }
}
