#include <cstddef>

#pragma once

/**
 * Класс CursorPosition определяет позицию курсора в строке.
 * Позволяет перемещаться по строке.
 */

// рисовать его, нет? хз. По сути надо.

class CursorPosition {
public:
    CursorPosition(size_t position = 0): position(position) {
    }

    void getPosition();

    void moveLeft();
    void moveRight();

    //void draw();

private:
    size_t position;
};
