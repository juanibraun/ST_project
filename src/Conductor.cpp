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
    new_note.start = start * dur_coeff;
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
    it->duration = dur_coeff * finish - it->start;
    
    //std::cout << "new_note: "<< noteNumber << " velocity: " << notes.front() .velocity << " duration: " << notes.front().duration << std::endl;
    
    
}

void Conductor::printSize(){
    
    for (int i = 0; i<128; i++){
        std::cout << "note: " << i << " size: " << this->played_notes.size() << std::endl;
    }
    
}




std::string Conductor::generateEvent(){
  
    note current_note = played_notes.front();
    played_notes.pop_front();
    
    return std::to_string(current_note.note) + "," + std::to_string(current_note.velocity) + "," + std::to_string(current_note.start) + "," + std::to_string(current_note.duration);

    // Improvement: generate events without duration and the modify them
    

    
}

splitted_event Conductor::splitEvent(std::string event){
    
    note current_note = readEvent(event);
    
    splitted_event out;
    out.note = std::to_string(current_note.note) + "," + std::to_string(current_note.velocity) + "," + std::to_string(0) + "," + std::to_string(current_note.duration);
    
    out.trigger = std::to_string(current_note.start);
    
    return out;

    // Improvement: generate events without duration and the modify them
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
    //return (played_notes.size()>0 and played_notes.front().duration != 0);
    return (played_notes.size()>0 and (played_notes.front().duration > 0));
}

void Conductor::clearNotes(){
        played_notes.clear();
}

int Conductor::getTimeOffset(){
    return time_offset;
}

void Conductor::setTimeOffset(int ofs){
    time_offset = ofs;
}

void Conductor::setDuration(double dur){
    dur_coeff = dur;
}

