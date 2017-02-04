/* 
 * File:   Memory.cpp
 * Author: Aziz OKAY
 * 
 * Created on 29 Ekim 2016 Cumartesi, 18:39
 */

#include "Memory.h"
#include "CPU.h"
#include "CPUProgram.h"

Memory::Memory() {
    for(int i = 0; i < 50; i++)
        setMem(i, 0);
}

/**
 * getter function that get a special index of memory
 * @param index to point memory element
 * @return unsiged int that index pointed
 */
unsigned int Memory::getMem(int index) const {
    if(index >= 0 && index < 50)
        return memArr[index];
    else {
        cerr << "Out of range for memory" << endl;
        exit (EXIT_FAILURE);
    }
        
}

void Memory::setMem(int index, unsigned int value) {
    if(index >= 0 && index < 50)
        memArr[index] = value;
    else {
        cerr << "Out of range for memory" << endl;
        exit (EXIT_FAILURE);
    }
}

/**
 * The function that print all memory content to screen
 * @param memoryArray array that hold memory
 */
void Memory::printAll() {
    cout << "Memory Values:" << endl;
    for(int i = 0; i < 50; i++)
        cout << "[" << i << "]" << " -> " << getMem(i) << endl;
}






