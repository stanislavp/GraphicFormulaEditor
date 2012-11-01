#include "../CursorPosition.h"

void CursorPosition::getPosition() {
    return position;
}

void CursorPosition::moveLeft() {
    // проверки на начало строки
    --position;
}

void CursorPosition::moveRight() {
    //проверки на конец строки
    ++position;
}
