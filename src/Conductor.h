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


#endif

class Conductor{
public:
    Conductor();
    
    void addNoteOn(int noteNumber, int vel, double start);
    
    void addNoteOff(int noteNumber, double finish);
    
    void printSize();
    
    void clearNotes();
    
    std::string generateEvent();
    
    note readEvent(std::string &event);
    
    bool availableEvents();
    
private:
    std::list <note> * played_notes;
    std::list<note>::iterator position;
    
};
