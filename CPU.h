/*
 * File:   CPU.h
 * Author: Aziz OKAY
 *
 * Created on 29 Ekim 2016 Çarşamba, 00:27
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <fstream>
#include "Memory.h"
using namespace std;

class CPU {
public:
    /*** CONSTRUCTORS ***/
    CPU();
    CPU(int op);
    CPU(string inst);


    int getPC();
    int getOption() const;
    int getNthRegister(int nth);
    string getInstruction();



    void print();
    bool halted();
    void setPC(int newPC);
    void setOption(int newOp);
    void setInstruction(string newString);
    void setNthRegister(int newR1, int nth);
    int execute(string line, Memory &memObj);

    int gtuAtoi(char *str);
    bool isNumber(char isNum);
    bool isEndOfLine(char isEnd);
    void gtuToLower(string &line);

    int jmpInstruction(string line);
    int jpnInstruction(string line);
    int addInstruction(string line, Memory &memObj);
    int subInstruction(string line, Memory &memObj);
    int movInstruction(string line, Memory &memObj);
    void dropAllSpace(string line, string &newLine);
    int movToReg(string line, int regNum, Memory &memObj);
    int movToMem(string line, int memNum, Memory &memObj);
    int prnInstruction(string line, Memory &memObj);

private:
    int PC;
    int option;
    int regArr[5];
    string instruction;

};

#endif /* CPU_H */
