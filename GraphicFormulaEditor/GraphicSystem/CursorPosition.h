#include <QPoint>

#pragma once

/**
 * Класс CursorPosition определяет позицию курсора.
 *
 */

// рисовать его, нет? хз. По сути надо.

namespace Graphic {

    class CursorPosition {
    public:
        CursorPosition(const QPoint& position = QPoint()): position(position) {
        }

        QPoint getPosition();

        void moveLeft();
        void moveRight();



        //void draw();

    private:
        QPoint position;
    };

}
