/* 
 * File:   CPUProgram.cpp
 * Author: Aziz OKAY
 * 
 * Created on 29 Ekim 2016 Cuma, 00:51
 */

#include "CPUProgram.h"
/**
 * constructor that take a string as a parameter
 * @param fileName name of file
 */
CPUProgram::CPUProgram(char *fileName) {
    ReadFile(fileName);
}

/**
 * the function return number that line of program
 * @return number of program
 */
int CPUProgram::size() {
    return getAllLine().size();
}

/**
 * the function that return all program line
 * @return string vector of all program
 */
vector<string> CPUProgram::getAllLine(){
    return allLine;
}

void CPUProgram::setAllLine(vector<string> all) {
    allLine.resize(all.size());
    for(int i = 0; i < all.size(); i++)
        allLine.at(i) = all.at(i);
}

/**
 * function that returned special line of program
 * @param lineNum line number of bonded program counter
 * @return line that indicated program counter 
 */
string CPUProgram::getLine(int lineNum) {
    return getAllLine()[lineNum];
}

/**
 * function that read all instructions in file
 * @param fileName name of file
 * @return 0 if there is a problem with file 1 otherwise
 */
int CPUProgram::ReadFile(char *fileName) {
    ifstream inputStream;
    string line;
    inputStream.open(fileName);
    
    if(inputStream.is_open()){
        while(inputStream.eof() != true) {
            getline(inputStream, line);
            allLine.push_back(line);
        }
        return 1;
    }else{
        cerr << "Error opening file!!!" << endl;
        return 0;
    }	
    inputStream.close();
}
