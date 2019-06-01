#include <iostream>
#include "Threads/Person.h"
#include "Threads/Child.h"
#include "Threads/Adult.h"
#include "House.h"

int main() {

    House house = House(2,3);

    house.start();

    return 0;
}