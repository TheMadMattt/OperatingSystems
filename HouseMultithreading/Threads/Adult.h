//
// Created by mateusz on 24.05.19.
//

#ifndef HOUSEMULTITHREADING_ADULT_H
#define HOUSEMULTITHREADING_ADULT_H


#include "Person.h"
#include "../Resources/TV.h"
#include "../Resources/Shower.h"
#include "../HouseStuff.h"

class Adult: public Person {

public:
    Adult(int id, unsigned int age, HouseSetup &houseSetup, Printing &print, HouseStuff &houseStuff);

    ~Adult();

    enum AdultStatus{
        IDLE, WATCHING, SHOWERING, EATING, FINISHED
    };

    void startHouse() override;

    std::string getPersonStatus() override;

    void setAdultStatus(AdultStatus _adultStatus);

    void watchingTV() override;
    void showering() override;

    void eating() override;


private:
    AdultStatus adultStatus;
    HouseStuff &houseStuff;
};


#endif //HOUSEMULTITHREADING_ADULT_H
