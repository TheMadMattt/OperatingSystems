#include <utility>
#include "Printing.h"

Printing::Printing(HouseSetup &houseSetup)
    :   tableSetup(houseSetup)
{
}

Printing::~Printing() {
    refresh();
    closeMenu();
}

void Printing::menu() {

    int key;
    bool finished = false;

    while((key = getch()) && !finished)
    {
        std::lock_guard<std::mutex> lockGuard(menuMutex);
        switch(key)
        {	case KEY_DOWN:
                menu_driver(myMenu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(myMenu, REQ_UP_ITEM);
                break;
            case KEY_PPAGE:
                menu_driver(myMenu, REQ_SCR_UPAGE);
                break;
            case KEY_NPAGE:
                menu_driver(myMenu, REQ_SCR_DPAGE);
                break;
            case 27: //ESC
                stop();
                finished = true;
                break;
            default:
                break;
        }
        refresh();
    }
}

void Printing::createMenu(std::vector<std::pair<std::string, std::string>> personsStatus,
                          std::vector<std::pair<std::string, std::string>> resourcesStatusBegin) {

    init();
    this-> personsNumber = personsStatus.size();
    this->personStatus = std::move(personsStatus);
    this->resourcesStatus = std::move(resourcesStatusBegin);
    myMenuItems = new ITEM*[personsNumber];

    for (int i = 0; i < personsNumber; ++i) {
        myMenuItems[i] = new_item(this->personStatus[i].first.c_str(), this->personStatus[i].second.c_str());
    }

    myMenu = new_menu(myMenuItems);
    set_menu_mark(myMenu, " ");
    refresh();
    post_menu(myMenu);

    for (int i = 0; i < this->resourcesStatus.size(); ++i) {
        mvprintw(LINES - (5+resourcesStatus.size()) + i, 0, this->resourcesStatus[i].second.c_str());
    }

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
    tableSetup.finishedHouse = true;
}

void Printing::closeMenu() {

    unpost_menu(myMenu);
    free_menu(myMenu);
    for (int i = 0; i < personStatus.size(); ++i) {
        free_item(myMenuItems[i]);
    }

    endwin();

}

void Printing::updateMenu(int personId, std::string status, std::string cycle) {

    std::lock_guard<std::mutex> lockGuard(menuMutex);
    personStatus[personId].first = std::move(cycle);
    personStatus[personId].second = std::move(status);
    myMenuItems[personId] = new_item(this->personStatus[personId].first.c_str(), this->personStatus[personId].second.c_str());

    auto currentMenuItem = myMenu->curitem;
    unpost_menu(myMenu);
    set_menu_items(myMenu,myMenuItems);
    set_current_item(myMenu,currentMenuItem);
    post_menu(myMenu);

    for (int i = 0; i < resourcesStatus.size(); ++i) {
        mvprintw(LINES - (5 +resourcesStatus.size()) + i, 0, resourcesStatus[i].second.c_str());
    }

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();
}

void Printing::updateResourcesStates(const std::string& resourceName, const std::string& status) {

    for (auto & resource : resourcesStatus) {
        if(resource.first == resourceName){
            resource.second = status;
        }
    }

    std::lock_guard<std::mutex> lockGuard(menuMutex);

    for (int i = 0; i < resourcesStatus.size(); ++i) {
        mvprintw(LINES - (5+resourcesStatus.size()) + i, 0, resourcesStatus[i].second.c_str());
    }

    mvprintw(LINES - 2, 0, "ESC to stop threads");
    refresh();

}
