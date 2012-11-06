#pragma once

#include "Composite.h"

//! Qt
#include <QGraphicsLineItem>

namespace Graphic
{

typedef boost::shared_ptr<QGraphicsLineItem> QGrapicsLineItemPtr;

class Fraction : public Composite
{
public:
    Fraction(GlyphPtr parent = GlyphPtr(), QPoint position = QPoint());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

        //! Возвращает максимальную прямоугольную область, занимаемую глифом
        virtual QRect Bound();

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
         *
         * @param position - 0..(2^15) - 1 - добавляем к знаменателю, От 2^15 - в числитель
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

	void UpdateLine();

	QPoint position_;
	GlyphPtr numerator;
	GlyphPtr denominator;
	QGrapicsLineItemPtr line_;
};


}
