#pragma once

#include "Composite.h"

namespace Graphic
{

class Row : public Composite
{
public:
        Row(GlyphPtr parent = GlyphPtr(), QPoint position = QPoint());

	//! Рисует глиф на сцене
	//virtual void Draw(QGraphicsScenePtr scene);

	//! Возвращает максимальную прямоугольную область, занимаемую глифом
	//virtual QRect Bound();

	//! Определяет пересечение точки с областью глифа
	//virtual GlyphPtr Intersects(const QPoint &point);

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
	 * Добавляет к глифу потомка.
	 * Будет работать только для глифов, наследуемых от Composite.
	 * Для простых глифов будет иметь пустую реализацию по умолчанию.
	 */
	virtual void Add(GlyphPtr glyph, size_t position);

	/**
	 * Пробует удалять потомок глифа по позици.
	 */
	//virtual bool Remove(size_t position);

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
	 */
	//virtual GlyphPtr Parent() throw();

	virtual QString Type() const;

	virtual ~Row();

protected:
	static QString __Type();

protected:
	QPoint position_;
};

}
