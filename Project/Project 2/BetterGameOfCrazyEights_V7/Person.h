/* 
 * File:   Person.h
 * Author: Draylend Chow
 *
 * Created on December 12, 2023, 7:42 AM
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
    protected:
        string name;
    public:
        Person() {name = "NULL";}               //Constructor
        Person(string name) {this->name = name;}//Overloaded Constructor
        
        string getName() const {return name;}           //Returns name
        void setName(string name) {this->name = name;}  //Sets name
};

#endif /* PERSON_H */