//
//  Conductor.cpp
//  midi-canon-v1
//
//  Created by Juan Braun on 18/7/23.
//

#include "Conductor.h"



Conductor::Conductor(){
    
    /*note n;
    n.duration = 0;
    n.start = 0;
    n.note = 0;
    n.velocity = 0;*/
    
    
    
    loop_count = 0;
    
}

void Conductor::addNoteOn(int noteNumber, int vel, double start){
    
    note new_note;
    new_note.note = noteNumber;
    new_note.start = start;
    new_note.velocity = vel;
    new_note.duration = 0;
    
    played_notes.push_back(new_note);
    
    //std::cout << "new_note: " << noteNumber << " velocity: " << played_notes->front().velocity << " start: " << played_notes->front().start << std::endl;
    //std::advance(notes_buffer_position, 1);
    
}

void Conductor::addNoteOff(int noteNumber, double finish){
    auto it = played_notes.end();
    do{
        --it;
    }
    while (it->note != noteNumber);
    it->duration = finish - it->start;
    
    //std::cout << "new_note: "<< noteNumber << " velocity: " << notes.front() .velocity << " duration: " << notes.front().duration << std::endl;
    
    
}

void Conductor::printSize(){
    
    for (int i = 0; i<128; i++){
        std::cout << "note: " << i << " size: " << this->played_notes.size() << std::endl;
    }
    
}

void Conductor::clearNotes(){
    played_notes.clear();
}
std::string Conductor::generateEvent(){
    
    note current_note = played_notes.front();
    played_notes.pop_front();
    
    
    /*
    if(notes_buffer_position == played_notes->end()) {
        
        
        current_note.duration = 0;
        current_note.start = 0;
        current_note.note = 0;
        current_note.velocity = 0;
         
        
        notes_buffer_position = played_notes->begin();
        loop_count++;
        time_offset = (1 + loop_count) * time_offset ;
        std::cout << "reset position "<< std::endl;
    }
    */
    
    
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
    return (played_notes.size()>0 and played_notes.front().duration != 0);
}

int Conductor::getTimeOffset(){
    return time_offset;
}

void Conductor::setTimeOffset(int ofs){
    time_offset = ofs;
}


