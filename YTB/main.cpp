#include "Menu.h"

int main(void) {

    Menu* menu = new Menu();
    menu->turnOnGame();

    delete menu;
    return EXIT_SUCCESS;
}