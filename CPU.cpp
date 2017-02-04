/*
 * File:   CPU.cpp
 * Author: Aziz OKAY
 *
 * Created on 29 Ekim 2016 Çarşamba, 00:27
 */

#include "CPU.h"
#include "Memory.h"
/**
 * no parameter constructor
 */
CPU::CPU() {
    setPC(1);
    for(int i = 0; i < 5; ++i)
        regArr[i] = 0;
}

CPU::CPU(int op) {
    setOption(op);
    setPC(1);
    for(int i = 0; i < 5; ++i)
        regArr[i] = 0;
}
/**
 * constructor that take a one instructor
 * @param inst a single instructor
 */
CPU::CPU(string inst) {
    setInstruction(inst);
   setPC(1);
    for(int i = 0; i < 5; ++i)
        regArr[i] = 0;
}
/*** All necessary getter function ***/
int CPU::getPC() { return PC; }
int CPU::getOption() const { return option;}
int CPU::getNthRegister(int nth) { return regArr[nth];}
string CPU::getInstruction() {return instruction;}

/*** All necessary setter function ***/
void CPU::setPC(int newPC) { PC = newPC; }
void CPU::setOption(int newOp) {
    if(newOp == 0 || newOp == 1 || newOp == 2)
        option = newOp;
    else {
        cerr << "Anknowen option number!!! Option has been set with 0" << endl;
    }
}
void CPU::setNthRegister(int newR1, int nth) { regArr[nth] = newR1;}
void CPU::setInstruction(string newString) {instruction = newString;}

/**
 * The function that print all register to screen
 * @param regArr array that hold registers
 */
void CPU::print() {
    cout << "Register Values:" << endl;
    for(int i = 0; i < 5; i++)
        cout << "[" << i << "]" << " -> " << getNthRegister(i) << endl;
}

/**
 * The function that check if program finish or not
 * @return true if program finish false otherwise
 */
bool CPU::halted() {
    return !getInstruction().compare(0, 3, "hlt");
}

/**
 * function that execute a single line of program
 * @param line include single instruction
 * @return 0 if there is no problem -1 is there a problem
 */
int CPU::execute(string line, Memory &memObj) {
    int resultOfJmp = 0;
    string newLine(256, '\0');
    gtuToLower(line);
    dropAllSpace(line, newLine);

    if(newLine.compare(0, 3, "mov") == 0) {
        if(movInstruction(newLine, memObj) == -1)
            return -1;
    }
    else if(newLine.compare(0, 3, "add") == 0) {
        if(addInstruction(newLine, memObj) == -1)
            return -1;
    }
    else if(newLine.compare(0, 3, "sub") == 0) {
        if(subInstruction(newLine, memObj) == -1)
            return -1;
    }
    else if(newLine.compare(0, 3, "jmp") == 0) {
        resultOfJmp = jmpInstruction(newLine);

        if(resultOfJmp == 0)
            ;
        else if(resultOfJmp != -1)
             setPC(resultOfJmp - 1);
        else
            return -1;
    }
    else if(newLine.compare(0, 3, "prn") == 0) {
        if(prnInstruction(newLine, memObj) == -1)
            return -1;
    }
    else
        return -1;
    if(getOption() == 1)
        print();
    if(getOption() == 2)

    setPC(getPC()+1);
    return 0;
}
/**
 * Function that we use for chance all line with lower case
 * @param line source string
 */
void CPU::gtuToLower(string &line) {
    for(int i = 0; isEndOfLine(line[i]); i++) {
        if(line[i] >= 'A' && line[i] <= 'Z')
            line[i] += 32;
    }
}

/**
 * The function that check given character is number or not
 * @param str source for searching
 * @return is true if it is number false otherwise
 */
bool CPU::isNumber(char isNum) {
	return (isNum >= 48 && isNum <= 57);
}

/**
 * The function that convert string to integer
 * @param str string that will be converted the integer
 * @return is integer value of string
 */
int CPU::gtuAtoi(char *str){
    int result = 0;
    for(int i = 0; isNumber(str[i]) ; i++){
        result = result * 10 + str[i] - '0';
    }
    return result;
}

/**
 * The function that check given character is en of line or ';'
 * @param str source for searching
 * @return true if it is end of line false otherwise
 */
bool CPU::isEndOfLine(char isEnd) {
    return (isEnd != '\0' && isEnd != '\n' && isEnd != ';');
}

/**
 * The function update program counter if is necessary
 * @return new program counter if is necessary 0 otherwise
 */
int CPU::jmpInstruction(string line) {
    int result = -1, regNum;
    if(line[3] == 'r') {
        regNum = line[4] - '0';
        if(regNum >= 1 && regNum <= 5) {
            if(getNthRegister(regNum-1) == 0)
                return gtuAtoi(&line[6]);
            else
                return 0;
        }
        else
            return -1;
    }
    else
        return gtuAtoi(&line[3]);

    return result;
}

/**
 * The function that drop all space character in the line
 * @param newLine, new string without space char
 */
void CPU::dropAllSpace(string line, string &newLine) {
    int j = 0;
    for(int i = 0; isEndOfLine(line[i]); i++) {
        if(line[i] != ' ') {
            newLine[j] = line[i];
            j++;
        }
    }
    newLine[j] = '\0';
}

/**
 * The function update program counter if is necessery
 * @param line that will be processed
 * @return new program counter if is necessery 0 otherwise
 */
int CPU::jpnInstruction(string line) {
    int result = -1, regNum;
    if(line[3] == 'r') {
        regNum = line[4] - '0';
        if(regNum >= 1 && regNum <= 5) {
            if(getNthRegister(regNum-1) <= 0)
                return gtuAtoi(&line[6]);
            else
                return 0;
        }
        else
            return -1;
    }else
        return -1;
    return result;
}
/**
 * The function that move given register or constant number to register
 * @param line is we read to file
 * @return 0 if there is no problem -1 otherwise
 */
int CPU::movInstruction(string line, Memory &memObj) {
    int regNum1, memIndex;
    if(line[3] == 'r') {
        regNum1 = line[4] - '0';
        if(regNum1 >= 1 && regNum1 <= 5) {
            return movToReg(line, regNum1, memObj);
        }else
            return -1; // register but not valid register
    }else if(line[3] == '#') {
        memIndex = gtuAtoi(&line[4]);
        cout << "memIndex is :" << memIndex << endl;
        if(memIndex >= 0 && memIndex < 50)
            return movToMem(line, memIndex, memObj); //call movtomem
        else
            return -1;
    }else
        return -1; // not valid memory address

return 0;
}

/**
 * Move function that for move value to memory
 * @param line line the instruction string
 * @param memObj return -1 is there a problem
 * @return -1 is there a problem
 */
int CPU::movToMem(string line, int memNum, Memory &memObj) {
    int regNum2, memIndex;

    if(line[line.find(',')+1] == 'r') {
        regNum2 = line[line.find(',')+2] - '0';
        if(regNum2 >= 1 && regNum2 <= 5) {
            regArr[regNum2-1] = memObj.getMem(memNum);
        }
        else
            return -1; // problem with second register
    }
    else if(line[line.find(',')+1] == '#') {
        memIndex = gtuAtoi(&line[line.find(',')+2]);
        if(memIndex >= 1 && memIndex <= 50)
            memObj.setMem(memIndex-1, memObj.getMem(memNum));
        else
            return -1;
    }
    else if(isNumber(line[line.find(',')+1])) {
        memObj.setMem(memNum, gtuAtoi(&line[6]));
    }
    else
        return -1; // after first register problem
    return 0;
}
/**
 * Move function that for move value to register
 * @param line the instruction string
 * @return return -1 is there a problem
 */
int CPU::movToReg(string line, int regNum, Memory &memObj) {
    int regNum2, memIndex;

    if(line[6] == 'r') {
        regNum2 = line[7] - '0';
        if(regNum2 >= 1 && regNum2 <= 5) {
            regArr[regNum2-1] = regArr[regNum-1];
        }
        else
            return -1; // problem with second register
    }
    else if(line[6] == '#') {
        memIndex = gtuAtoi(&line[7]);
        if(memIndex >= 1 && memIndex <= 50)
            memObj.setMem(memIndex, getNthRegister(regNum-1));
        else
            return -1;
    }
    else if(isNumber(line[6])) {
        setNthRegister(gtuAtoi(&line[6]), regNum-1);
    }
    else
        return -1; // after first register problem
    return 0;
}


/**
 * The function that add given register or constant number to another register
 * @param line is we read to file
 * @return 0 if there is no problem -1 otherwise
 */
int CPU::addInstruction(string line, Memory &memObj) {
    int regNum1, regNum2, memIndex;
    regNum1 = line[4] - '0';
    if(regNum1 >= 1 && regNum1 <= 5) {
        if(line[6] == 'r') {
            regNum2 = line[7] - '0';
            if(regNum2 >= 1 && regNum2 <= 5)
                setNthRegister(getNthRegister(regNum2-1)+
                getNthRegister(regNum1-1), regNum1-1);
        } else if(line[6] == '#') {
            memIndex = gtuAtoi(&line[7]);
            if(memIndex >= 1 && memIndex <= 50)
                regArr[regNum1-1] += memObj.getMem(memIndex-1);
            else
                return -1; // memeory numari yanlis
        }
        else
            setNthRegister(getNthRegister(regNum1-1)+ gtuAtoi(&line[6]), regNum1-1);
    }
    else
        return -1; // register number not valid
return 0;
}

/**
 * The function that sub given register or constant number to another register
 * @param line is we read to file
 * @return 0 if there is no problem -1 otherwise
 */
int CPU::subInstruction(string line, Memory &memObj) {
    int regNum1, regNum2, memIndex;
    regNum1 = line[4] - '0';
    if(regNum1 >= 1 && regNum1 <= 5) {
        if(line[6] == 'r') {
            regNum2 = line[7] - '0';
            if(regNum2 >= 1 && regNum2 <= 5)
                setNthRegister(getNthRegister(regNum1-1) -
                getNthRegister(regNum2-1), regNum1-1);
        } else if(line[6] == '#') {
            memIndex = gtuAtoi(&line[7]);
            if(memIndex >= 1 && memIndex <= 50)
                regArr[regNum1-1] -= memObj.getMem(memIndex-1);
            else
                return -1; // memeory numari yanlis
        }
        else
           setNthRegister(getNthRegister(regNum1-1) - gtuAtoi(&line[6]), regNum1-1);
    }
    else
        return -1; // register number not valid
return 0;
}

/**
 * The function that print given register or constant number to screen
 * @param line is we read to file
 * @return 0 if there is no problem -1 otherwise
 */
int CPU::prnInstruction(string line, Memory &memObj){
    int regNum;
    if(line[3] == 'r') {
        regNum = line[4] - '0';
        if(regNum >= 1 && regNum <= 5)
            cout << getNthRegister(regNum-1) << endl;
        else
            return -1; // not valid register number
    } else if(line[3] == '#') {
        cout << memObj.getMem(gtuAtoi(&line[4])-1) << endl;
    }
    else
        cout << gtuAtoi(&line[3]) << endl;
return 0;
}
