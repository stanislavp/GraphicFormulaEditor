#pragma once

//! Boost
#include <boost/shared_ptr.hpp>

//! Qt
#include <QGraphicsScene>
#include <QRect>

namespace Graphic
{

typedef boost::shared_ptr<QGraphicsScene> QGraphicsScenePtr;

class Glyph;
typedef boost::shared_ptr<Glyph> GlyphPtr;

/**
 * DESIGN PATTERN: COMPOSITE.
 * Glyph - структурная единица формулы.
 * Описывает интерфейс как сложных элементов, наследуемых от компоновщика,
 * так и примитивных листовых элементов.
 * Таким образом поддерживается прозрачность структуры.
 * Хоть это и уменьшает безопасность, но позволяет не применять RTTI для динамического приведения типов,
 * либо раздувать интерфейс лишними методами и производить лишние проверки указателей.
 */

/**
 * TODO: Написать forward declaration.
 */

class Glyph
{
public:

	Glyph();

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene) = 0;

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound() = 0;

	/**
	 * У каждого глифа есть позиция.
	 * Установкой позиции для глифа занимаются только компоновщики.
	 */
	virtual void SetPosition(const QPoint &point) = 0;

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition() = 0;

	//! Определяет пересечение точки с областью глифа
	virtual GlyphPtr Intersects(const QPoint &point) = 0;

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
	virtual GlyphPtr Parent() throw();

	virtual ~Glyph();

protected:
    size_t topMargin;
};


}
