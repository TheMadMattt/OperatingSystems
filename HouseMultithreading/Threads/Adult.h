//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_ADULT_H
#define HOUSEMULTITHREADING_ADULT_H


#include "Person.h"
#include "../Resources/TV.h"
#include "../Resources/Shower.h"

class Adult: public Person {

public:
    Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, TV &tv, Shower &shower);

    ~Adult();

    enum AdultStatus{
        IDLE, WATCHING, STOPPED_WATCHING, SHOWERING
    };

    void startHouse() override;

    std::string getPersonStatus() override;

    void setAdultStatus(AdultStatus _adultStatus);

    void watchingTV() override;

    void showering() override;

private:
    AdultStatus adultStatus;
    TV &tv;
    Shower &shower;
};


#endif //HOUSEMULTITHREADING_ADULT_H
