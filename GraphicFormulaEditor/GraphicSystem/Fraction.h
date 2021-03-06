#pragma once

#include "Composite.h"

//! Qt
#include <QGraphicsLineItem>

namespace Graphic
{

typedef QGraphicsLineItem* QGrapicsLineItemPtr;

//! Forward declaration
class Fraction;

typedef Fraction* FractionPtr;

class Fraction : public Composite
{
public:
    Fraction(GlyphPtr parent = GlyphPtr(), QPoint position = QPoint());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound() const ;

	/**
	 * У каждого глифа есть позиция.
	 * Установкой позиции для глифа занимаются только компоновщики.
	 */
	virtual void SetPosition(const QPoint &point);

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition() const ;

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	//virtual QRect Bound();

	//! Определяет пересечение точки с областью глифа
	virtual bool Intersects(const QPoint &point, GlyphList &list) const ;

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
	virtual bool Remove(size_t position);

	/**
	 * Возвращает потомка глифа по позиции.
	 */
	virtual GlyphPtr Get(size_t position) const ;

	/**
	* Возвращает позицию глифа в родителе по указателю.
	* Будет вызываться только у сложных глифов.
	*/
	virtual size_t GetPositionByPtr(GlyphPtr ptr) const ;

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
	 */
	//virtual GlyphPtr Parent() throw();

	virtual QString Type() const;

	virtual ~Fraction();

protected:
	static QString __Type();

private:

	void UpdateLine();

	QPoint position_;
	GlyphPtr numerator;
	GlyphPtr denominator;
	QGrapicsLineItemPtr line_;
};


}
