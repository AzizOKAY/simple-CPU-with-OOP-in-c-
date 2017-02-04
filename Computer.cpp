/*
 * File:   Computer.cpp
 * Author: Aziz OKAY
 *
 * Created on 03 Kasım 2016 Perşembe, 23:48
 */

#include "Computer.h"



Computer::Computer(int option) {
    comCPU.setOption(option);
}

Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, int option){
    setCPU(myCPU);
    setMemory(myMemory);
    setCPUProgram(myCPUProgram);
}

CPU Computer::getCPU() const { return comCPU;}
Memory Computer::getMemory() const {return comMemory;}
CPUProgram Computer::getCPUProgram() const {return comCPUProgram;}

void Computer::setCPU(CPU myCPU) {
    comCPU.setInstruction(myCPU.getInstruction());
    comCPU.setOption(myCPU.getOption());
    comCPU.setPC(1);
    for(int i = 0; i < 5; i++)
        comCPU.setNthRegister(myCPU.getNthRegister(i), i);
}


void Computer::setMemory(Memory myMemory){
    for(int i = 0; i < 50; i++)
        comMemory.setMem(i, myMemory.getMem(i));
}


void Computer::setCPUProgram(CPUProgram myCPUProgram) {
    comCPUProgram.setAllLine(myCPUProgram.getAllLine());
}

int Computer::execute() {
    int i = 0;
    comCPU.setInstruction(comCPUProgram.getLine(i));
    while(!comCPU.halted()) {
        comCPU.execute(comCPUProgram.getLine(i), comMemory);
        ++i;
        comCPU.setInstruction(comCPUProgram.getLine(i));
    }

    return 0;
}
