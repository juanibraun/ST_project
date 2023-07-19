//
//  Listener.cpp
//  midi-markov-v1
//
//  Created by Juan Braun on 18/7/23.
//

#include "Listener.hpp"


Listener::Listener(){
    
    
}

void Listener::add_noteOn(int noteNumber, int vel, double start){
    
    note new_note;
    new_note.start = start;
    new_note.velocity = vel;
    notes[noteNumber].push_back (new_note);
    std::cout << "new_note: " << noteNumber << " velocity: " << notes[noteNumber].back().velocity << " start: " << notes[noteNumber].back().start << std::endl;
    
}

void Listener::add_noteOff(int noteNumber, double finish){
    double duration;
    duration = finish - notes[noteNumber].back().start;
    notes[noteNumber].back().duration = duration;
    
    std::cout << "new_note: "<< noteNumber << " velocity: " << notes[noteNumber].back().velocity << " duration: " << duration << std::endl;
    
    
}

void Listener::printSize(){
    
    for (int i = 0; i<128; i++){
        std::cout << "note: " << i << " size: " << this->notes[i].size() << std::endl;
    }
        
}
