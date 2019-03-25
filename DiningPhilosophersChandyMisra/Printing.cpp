#include <utility>

#include <utility>
#include "Printing.h"

Printing::Printing(TableSetup &table, int philsNumber) : table(table), philsNumber(philsNumber)
{}


Printing::~Printing() {
    refresh();
}

void Printing::createMenu(std::vector<std::string> philosophersStates) {

    init();

    this->philosophersStates = std::move(philosophersStates);
    this->myMenuItems = new ITEM*[philsNumber];

    for (int i = 0; i < philsNumber; ++i) {
        myMenuItems[i] = new_item(this->philosophersStates[i].c_str(), nullptr);
    }

    myMenu = new_menu(myMenuItems);

    post_menu(myMenu);
    mvprintw(LINES - 2, 4, "ESC to stop threads");
    refresh();
}

void Printing::init() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

}

void Printing::start() {

    int c;
    bool finished = false;

    while((c = getch()) && !finished)
    {
        switch(c)
        {	case KEY_DOWN:
                menu_driver(myMenu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(myMenu, REQ_UP_ITEM);
                break;
            case 27:
                stop();
                finished = true;
                break;
            default:
                break;
        }

    }

}

void Printing::stop() {

    table.done = true;
}

void Printing::updateMenu(int philId, std::string state) {

    std::lock_guard<std::mutex> lock_guard(menuLock);

    philosophersStates[philId] = std::move(state);

    myMenuItems[philId] = new_item(philosophersStates[philId].c_str(), nullptr);

    auto currentItem = myMenu->curitem;

    unpost_menu(myMenu);

    set_menu_items(myMenu, myMenuItems);
    set_current_item(myMenu, currentItem);

    post_menu(myMenu);
    refresh();
}
