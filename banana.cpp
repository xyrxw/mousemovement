#include <Windows.h>
#include <iostream>
#include "driver.h"

int main() {
    // BRAZIL ON TOP
    // 3 MONKEYS = GOLD BANANA
    // MOUSE MOVE LOVERS
    // #JOIN US

    MouseController mouse;
    if (mouse.MoveMouse(100, 100)) {
        std::cout << "Mouse moved successfully.\n";
    }

    if (mouse.Click(MouseController::Button::LeftButtonDown)) {
        std::cout << "Mouse left button clicked.\n";

        // Release Left Button
        mouse.Click(MouseController::Button::LeftButtonUp);
    }

    system("pause");
}