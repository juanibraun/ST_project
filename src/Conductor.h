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
typedef std::list <note> single_note_list;

#endif

class Conductor{
public:
    Conductor();
    
    void addNoteOn(int noteNumber, int vel, double start);
    
    void addNoteOff(int noteNumber, double finish);
    
    void printSize();
    
    std::string generateEvent(int n);
    
    note readEvent(std::string &event);
    
    
private:
    single_note_list notes[127];
    
};
