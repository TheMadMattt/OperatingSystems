//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_CHILD_H
#define HOUSEMULTITHREADING_CHILD_H


#include "Person.h"
#include "../Resources/TV.h"
#include "../Resources/Shower.h"

class Child: public Person {
public:
    Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv, Shower &shower);
    ~Child();

    enum ChildStatus{
        IDLE, WATCHING, SHOWERING, PLAYING
    };

    void startHouse() override;

    std::string getPersonStatus() override;

    void setChildStatus(ChildStatus _childStatus);

    void watchingTV() override;

    void showering() override;

private:
    ChildStatus childStatus;
    TV &tv;
    Shower &shower;
};


#endif //HOUSEMULTITHREADING_CHILD_H
