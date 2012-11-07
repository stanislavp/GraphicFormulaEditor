#pragma once

//! Own
#include "Composite.h"
#include "Variable.h"
#include "Row.h"

namespace Graphic
{

//! Forward declaration
class BracketsPair;

typedef boost::shared_ptr<BracketsPair> BracketsPairPtr;

class BracketsPair : public Composite
{
public:
	BracketsPair(GlyphPtr parent = GlyphPtr());
	BracketsPair(GlyphPtr parent, QPoint position = QPoint());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound();

	//! Определяет пересечение точки с областью глифа
	virtual GlyphPtr Intersects(const QPoint &point);

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
	 * У каждого глифа есть позиция.
	 * Установкой позиции для глифа занимаются только компоновщики.
	 */
	virtual void SetPosition(const QPoint &point);

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition();

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
	 */
	//virtual GlyphPtr Parent() throw();
private:
	QPoint position_;
	GlyphPtr row_;
	GlyphPtr frontBracket_;
	GlyphPtr backBracket_;
};

}
