//
//  Conductor.cpp
//  midi-canon-v1
//
//  Created by Juan Braun on 18/7/23.
//

#include "Conductor.h"



Conductor::Conductor(){
    
    played_notes = new std::list <note>;
    position = played_notes->begin();
    
}

void Conductor::addNoteOn(int noteNumber, int vel, double start){
    
    note new_note;
    new_note.note = noteNumber;
    new_note.start = start;
    new_note.velocity = vel;
    
    played_notes->push_back (new_note);
    //std::cout << "new_note: " << noteNumber << " velocity: " << notes.front().velocity << " start: " << notes.front().start << std::endl;
    
}

void Conductor::addNoteOff(int noteNumber, double finish){
    auto it = played_notes->end();
     int i = 1;
    do{
        std::advance(it, -i);
        i--;
        //std::cout << "note in it: "<< it->note << std::endl;
    }
    while (it->note != noteNumber);
    it->duration = finish - it->start;
    
    //std::cout << "new_note: "<< noteNumber << " velocity: " << notes.front() .velocity << " duration: " << notes.front().duration << std::endl;
    
    
}

void Conductor::printSize(){
    
    for (int i = 0; i<128; i++){
        std::cout << "note: " << i << " size: " << this->played_notes->size() << std::endl;
    }
    
}

void Conductor::clearNotes(){
    played_notes->clear();
}
std::string Conductor::generateEvent(){
    
  
    note current_note = *position;
    std::advance(position, 1);
    
    if(position == played_notes->end()) {
    
        position = played_notes->begin();
        std::cout << "reset position "<< std::endl;
    }
    
    
    return std::to_string(current_note.note) + "," + std::to_string(current_note.velocity) + "," + std::to_string(current_note.start) + "," + std::to_string(current_note.duration);
    
    
}

note Conductor::readEvent(std::string &event){
    
    note out;
    
    std::stringstream stream(event);
    int note_num;
    int velocity;
    double start, duration;
    
    stream >> note_num;
    stream.ignore(256,',');
    stream >> velocity;
    stream.ignore(256,',');
    stream >> start;
    stream.ignore(256,',');
    stream >> duration;
    
    //std::cout<< "Read Event: "<< note_num << "," << velocity << "," << start << "," << duration << std::endl;
    
    out.note = note_num;
    out.velocity = velocity;
    out.duration = duration;
    out.start = start;
    
    return out;
}

bool Conductor::availableEvents(){
    return (played_notes->size() > 0) && (played_notes->back().duration > 0.001);
}


