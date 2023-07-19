//
//  Listener.hpp
//  midi-markov-v1
//
//  Created by Juan Braun on 18/7/23.
//

#ifndef Listener_hpp
#define Listener_hpp

#include <stdio.h>
#include <iostream>
#include <list>

struct note {
    int velocity;
    double start;
    double duration;
} ;
typedef std::list <note> single_note_list;

#endif

class Listener{
public:
    Listener();
    
    void add_noteOn(int noteNumber, int vel, double start);
    
    void add_noteOff(int noteNumber, double finish);
    
    void printSize();
    
private:
    single_note_list notes[127];
    
};
