#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include "Philosopher.h"
#include "Fork.h"


using namespace std;

vector<pthread_t> philosophers;
pthread_mutex_t printing;

vector<int> ids; //id filozofów
int breakLoop = true;

//Funkcja do wątków
void *run (void *arg);

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    int philoNumber;

    cout << "Ile filozofów chcesz utworzyć?: ";
    cin >> philoNumber;

    philosophers.resize(philoNumber);

    ids.resize(philoNumber);

    for (int j = 0; j < philoNumber; ++j) {
        ids[j] = j+1;
    }

    pthread_mutex_init(&printing, NULL);

    for (int i = 0; i < philoNumber; ++i) {
        pthread_create(&philosophers[i], NULL, run, &ids[i]);
    }

    char temp;

    while(temp != 'q') {

        temp = static_cast<char>(cin.get());
        if (temp == 'q') {
            breakLoop = false;
        }
    }

    for (int k = 0; k < philoNumber; ++k) {
        pthread_join(philosophers[k], NULL);
        cout << "Filozof " << k+1 << " zakończył pracę" << endl;
    }

    return 0;
}

void *run(void *arg){

    int *tmp = (int *)arg;
    Philosopher philosopher(*tmp);

    philosopher.setState(rand()%2); //ustawienie losowego stanu poczatkowego: HUNGRY or THINKING

    pthread_mutex_lock(&printing);
        cout << "Filozof " << philosopher.getId() << " rozpoczął pracę." << endl;
    pthread_mutex_unlock(&printing);

    while(breakLoop) {

        if(philosopher.getState() != Philosopher::State::HUNGRY){
            pthread_mutex_lock(&printing);
                philosopher.think();    //Filozof myśli
            pthread_mutex_unlock(&printing);

            philosopher.setState(Philosopher::State::THINKING);
            usleep(philosopher.getRandom());
            philosopher.setState(Philosopher::State::HUNGRY);
        }else{
            pthread_mutex_lock(&printing);
                philosopher.hungry();   //Filozof zgłodniał i chce jeść
            pthread_mutex_unlock(&printing);
            usleep(philosopher.getRandom());

            pthread_mutex_lock(&printing);
                philosopher.takeUpForks();  //Filozof podnosi sztućce
            pthread_mutex_unlock(&printing);
            usleep(philosopher.getRandom());

            pthread_mutex_lock(&printing);
                philosopher.eat();      //Filozof rozpoczyna jedzenie
            pthread_mutex_unlock(&printing);

            philosopher.setState(Philosopher::State::EATING);
            usleep(philosopher.getRandom());

            pthread_mutex_lock(&printing);
                philosopher.returnForks();      //Po zakończonym jedzeniu filozof zwraca sztućce
            pthread_mutex_unlock(&printing);

        }
    }

    return nullptr;

}