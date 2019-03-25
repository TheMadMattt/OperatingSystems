#include <utility>

#include <utility>

//
// Created by mateusz on 25.03.19.
//

#include "Printing.h"

Printing::Printing(TableSetup &tableSetup)
    :   tableSetup(tableSetup)
{
}

Printing::~Printing() {
    refresh();
    closeMenu();
}

void Printing::menu() {

    int c;
    bool finished = false;

    while((c = getch()) && !finished)
    {
        std::lock_guard<std::mutex> lockGuard(menuMutex);
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
        refresh();
    }
}

void Printing::createMenu(std::vector<std::string> philosophersStatus) {

    init();
    int philosophersNumber = static_cast<int>(philosophersStatus.size());
    this->philosopherStatus = std::move(philosophersStatus);
    myMenuItems = new ITEM*[philosophersNumber];

    for (int i = 0; i < philosophersNumber; ++i) {
        myMenuItems[i] = new_item(this->philosopherStatus[i].c_str(), nullptr);
    }

    myMenu = new_menu(myMenuItems);
    set_menu_mark(myMenu, " ");
    refresh();
    post_menu(myMenu);

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();
}

void Printing::init() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
}

void Printing::stop() {

    tableSetup.finishedDinner = true;

}

void Printing::closeMenu() {

    unpost_menu(myMenu);
    free_menu(myMenu);
    for (int i = 0; i < philosopherStatus.size(); ++i) {
        free_item(myMenuItems[i]);
    }

    endwin();

}

void Printing::updateMenu(int philosopherId, std::string status) {

    std::lock_guard<std::mutex> lockGuard(menuMutex);
    philosopherStatus[philosopherId] = std::move(status);
    myMenuItems[philosopherId] = new_item(philosopherStatus[philosopherId].c_str(), nullptr);

    auto currentMenuItem = myMenu->curitem;
    unpost_menu(myMenu);
    set_menu_items(myMenu,myMenuItems);
    set_current_item(myMenu,currentMenuItem);
    post_menu(myMenu);

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();
}
