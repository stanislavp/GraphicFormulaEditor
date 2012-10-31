#pragma once

#include "Composite.h"

namespace Graphic
{

class Fraction : public Composite
{
public:
	Fraction(GlyphPtr parent = GlyphPtr());
	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	/**
	 * У каждого глифа есть позиция.
	 * Установкой позиции для глифа занимаются только компоновщики.
	 */
	virtual void SetPosition(const QPoint &point);

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition();

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	//virtual QRect Bound();

	//! Определяет пересечение точки с областью глифа
	//virtual GlyphPtr Intersects(const QPoint &point);

	/**
	 * Добавляет к глифу потомка.
	 * Будет работать только для глифов, наследуемых от Composite.
	 * Для простых глифов будет иметь пустую реализацию по умолчанию.
	 */
	virtual void Add(GlyphPtr glyph, size_t position);

	/**
	 * Пробует удалять потомок глифа по позици.
	 */
	virtual void Remove(size_t position);

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
	 */
	//virtual GlyphPtr Parent() throw();

	virtual ~Fraction();

private:
	QPoint position_;
};


}
