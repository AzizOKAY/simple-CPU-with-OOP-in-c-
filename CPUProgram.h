/* 
 * File:   CPUProgram.h
 * Author: Aziz OKAY
 *
 * Created on 29 Ekim 2016 Cuma, 00:51
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class CPUProgram {
    public:
        CPUProgram(){;};
        CPUProgram(char *fileName);
        
        int size();
        vector<string> getAllLine();
        void setAllLine(vector<string> all);
        string getLine(int lineNum);
        int ReadFile(char *fileName);
        
    private:
        vector<string> allLine;
};

#endif /* CPUPROGRAM_H */
