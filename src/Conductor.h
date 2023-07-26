//
//  Conductor.h
//  midi-canon-v1
//
//  Created by Juan Braun on 18/7/23.
//

#ifndef Conductor_h
#define Conductor_h

#include <stdio.h>
#include <iostream>
#include <list>
#include <sstream>

struct note {
    int note;
    int velocity;
    double start;
    double duration;
} ;

struct splitted_event {
    std::string note, trigger;
};

#endif

class Conductor{
public:
    Conductor();
    
    void addNoteOn(int noteNumber, int vel, double start);
    
    void addNoteOff(int noteNumber, double finish);
    
    void printSize();
    
    void clearNotes();
    
    std::string generateEvent();
    
    splitted_event splitEvent(std::string event);
    
    note readEvent(std::string &event);
    
    bool availableEvents();
    
    int getTimeOffset();
    
    void setTimeOffset(int ofs);
    
    void setDuration(double dur);
    
private:
    std::list <note> played_notes;

    int read_count;
    int write_count;
    
    int time_offset;
    double dur_coeff;
    
};
