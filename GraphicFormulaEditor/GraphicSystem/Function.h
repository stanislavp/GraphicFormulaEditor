#pragma once

//! Own
#include "Composite.h"
#include "BracketsPair.h"

namespace Graphic
{

//! Forward declaration
class Function;

//typedef boost::shared_ptr<Function> FunctionPtr;

typedef Function* FunctionPtr;

class Function : public Composite
{
public:
	Function(const QString &name, GlyphPtr parent = GlyphPtr(), QPoint position = QPoint());

	//! Рисует глиф на сцене
	virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	virtual QRect Bound();

	// Устанавливает позицию глифа
	virtual void SetPosition(const QPoint &point);

	// Возвращает позицию глифа
	virtual QPoint GetPosition();

	//! Определяет пересечение точки с областью глифа
	virtual bool Intersects(const QPoint &point, GlyphList &list);

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

	virtual ~Function();
private:
	QPoint position_;
	GlyphPtr brackets_;
	GlyphPtr name_;
};

}
