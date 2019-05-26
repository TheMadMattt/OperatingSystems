#include <iostream>
#include "Threads/Person.h"
#include "Threads/Child.h"
#include "Threads/Adult.h"
#include "House.h"

int main() {

    House house = House(10,10);

    house.start();

    return 0;
}