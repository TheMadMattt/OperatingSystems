//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_CHILD_H
#define HOUSEMULTITHREADING_CHILD_H


#include "Person.h"
#include "../Resources/TV.h"

class Child: public Person {
public:
    Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv);
    ~Child();

    enum ChildStatus{
        IDLE, WATCHING, STOPPED_WATCHING, SHOWERING, PLAYING
    };

    void startHouse() override;

    std::string getChildStatus();

    void setChildStatus(ChildStatus _childStatus);

    void watchingTV() override;

private:
    ChildStatus childStatus;
    HouseSetup &houseSetup;
    TV &tv;
};


#endif //HOUSEMULTITHREADING_CHILD_H
