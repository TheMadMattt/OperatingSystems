//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_CHILD_H
#define HOUSEMULTITHREADING_CHILD_H


#include "Person.h"
#include "../Resources/TV.h"
#include "../Resources/Shower.h"
#include "../HouseStuff.h"

class Child: public Person {
public:
    Child(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, HouseStuff &houseStuff, int adultsNumber);
    ~Child();

    enum ChildStatus{
        IDLE, WATCHING, SHOWERING, PLAYING, EATING, FINISHED
    };

    void startHouse() override;

    std::string getPersonStatus() override;

    void setChildStatus(ChildStatus _childStatus);

    void watchingTV() override;

    void showering() override;

    void eating() override;

private:
    ChildStatus childStatus;
    HouseStuff &houseStuff;

    int adultsNumber;

    void playingConsole();
};


#endif //HOUSEMULTITHREADING_CHILD_H
