#pragma once

//! Own
#include "Glyph.h"

//! STL
#include <list>

namespace Graphic
{

//! Forward declaration
class Composite;

typedef Composite* CompositePtr;

class Composite : public Glyph
{
public:

	typedef std::list<GlyphPtr> Content;

	Composite(GlyphPtr parent = GlyphPtr());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound() const ;

	//! Определяет пересечение точки с областью глифа
	virtual bool Intersects(const QPoint &point, GlyphList &list) const;

	/**
	 * Сдвигает элементы вниз, после добавления(изменения высоты) одного из элементов.
	 */
   // void updateVertical();

	/**
	 * Добавляет к глифу потомка.
	 * Будет работать только для глифов, наследуемых от Composite.
	 * Для простых глифов будет иметь пустую реализацию по умолчанию.
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
	virtual GlyphPtr Parent() const throw();

	virtual QString Type() const;

	virtual ~Composite();

protected:
	static QString __Type();

protected:

	/**
	 * Компоновщик будет хранить свои потомки в списке.
	 * Обеспечивает вставку за O(1), но поиск за O(n)
	 */
	Content contents_;

	//! Указатель на глиф-родитель
	GlyphPtr parent_;
};

}
