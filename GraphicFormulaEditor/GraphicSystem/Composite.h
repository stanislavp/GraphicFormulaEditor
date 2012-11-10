#pragma once

//! Own
#include "Glyph.h"

//! STL
#include <list>

namespace Graphic
{

class Composite : public Glyph
{
public:

	typedef std::list<GlyphPtr> Content;

	Composite(GlyphPtr parent = GlyphPtr());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound();

	//! Определяет пересечение точки с областью глифа
	virtual bool Intersects(const QPoint &point, GlyphList &list);

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
	virtual void Remove(size_t position);

        /**
         * Обновляет позиции элементов после изменения контейнера.
         */
        virtual void updatePositions(int height);

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
         */
	virtual GlyphPtr Parent() throw();

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
