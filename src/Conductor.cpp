//
//  Conductor.cpp
//  midi-canon-v1
//
//  Created by Juan Braun on 18/7/23.
//

#include "Conductor.h"



Conductor::Conductor(){
    
    
}

void Conductor::addNoteOn(int noteNumber, int vel, double start){
    
    note new_note;
    new_note.note = noteNumber;
    new_note.start = start;
    new_note.velocity = vel;
    
    notes[noteNumber].push_back (new_note);
    //std::cout << "new_note: " << noteNumber << " velocity: " << notes[noteNumber].back().velocity << " start: " << notes[noteNumber].back().start << std::endl;
    
}

void Conductor::addNoteOff(int noteNumber, double finish){
    double duration;
    duration = finish - notes[noteNumber].back().start;
    notes[noteNumber].back().duration = duration;
    
    //std::cout << "new_note: "<< noteNumber << " velocity: " << notes[noteNumber].back().velocity << " duration: " << duration << std::endl;
    
    
}

void Conductor::printSize(){
    
    for (int i = 0; i<128; i++){
        std::cout << "note: " << i << " size: " << this->notes[i].size() << std::endl;
    }
    
}
std::string Conductor::generateEvent(int n){
    note current_note = notes[n].front();
    notes[n].pop_front();
    return std::to_string(n) + "," + std::to_string(current_note.velocity) + "," + std::to_string(current_note.start) + "," + std::to_string(current_note.duration);
}

note Conductor::readEvent(std::string &event){
    static const char COMMA = ',';
    

    
    std::stringstream stream(event);
    int note_num, velocity;
    float start, duration;
    
    stream >> note_num;
    stream.ignore(1,",");
    stream >> velocity;
    stream.ignore(1,",");
    stream >> start;
    stream.ignore(1,",");
    stream >> duration;
    
    

}


