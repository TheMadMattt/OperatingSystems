#include <iostream>
#include "Table.h"

int main() {

    int philNumber;

    std::cout << "Ilu filozofow chcesz utworzyc?: ";
    std::cin >> philNumber;

    if(philNumber<1) {
        do {
            std::cout << "Wpisz poprawna liczbe filozofow: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> philNumber;

        } while (std::cin.fail());
    }

    if(philNumber>1) {
        Table table(philNumber);
        table.startDinner();
    }else{
        Table table(5);
        table.startDinner();
    }
}