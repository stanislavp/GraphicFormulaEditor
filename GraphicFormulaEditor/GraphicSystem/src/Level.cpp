#include "../Level.h"

namespace Graphic
{

LeveledExpression::LeveledExpression(GlyphPtr parent)
    : Composite(parent)
{

}


//! Рисует глиф на сцене
void LeveledExpression::Draw(QGraphicsScenePtr scene)
{

}

//! Возвращает максимальную прямоугольную область, занимаемую глифом
QRect LeveledExpression::Bound()
{

}

//! Определяет пересечение точки с областью глифа
GlyphPtr LeveledExpression::Intersects(const QPoint &point)
{

}

/**
 * У каждого глифа есть позиция.
 * Установкой позиции для глифа занимаются только компоновщики.
 */
void LeveledExpression::SetPosition(const QPoint &point)
{

}

/**
 * Возвращает позицию глифа.
 */
QPoint LeveledExpression::GetPosition()
{

}

/**
 * Добавляет к глифу потомка.
 * Будет работать только для глифов, наследуемых от Composite.
 * Для простых глифов будет иметь пустую реализацию по умолчанию.
 */
void LeveledExpression::Add(GlyphPtr glyph, size_t position)
{

}

/**
 * Пробует удалять потомок глифа по позици.
 */
void LeveledExpression::Remove(size_t position)
{

}

}
