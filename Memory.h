/* 
 * File:   Memory.h
 * Author: Aziz OKAY
 *
 * Created on 29 Ekim 2016 Cumartesi, 18:39
 */

#ifndef MEMORY_H
#define MEMORY_H

class Memory {
public:
    Memory();
    
    /*** Getter Function ***/
    unsigned int getMem(int index) const;
    
    /*** Setter Function ***/
    void setMem(int index, unsigned int value);
    
    void printAll();
    
private:
    unsigned int memArr[50];
};

#endif /* MEMORY_H */
