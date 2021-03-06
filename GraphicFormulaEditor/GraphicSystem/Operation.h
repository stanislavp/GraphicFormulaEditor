#pragma once

//! Own
#include "Glyph.h"

//! Qt
#include <QGraphicsTextItem>

namespace Graphic
{

//typedef boost::shared_ptr<QGraphicsTextItem> QGraphicsTextItemPtr;

typedef QGraphicsTextItem* QGraphicsTextItemPtr;

//! Forward declaration
class Operation;
//typedef boost::shared_ptr<Operation> OperationPtr;

typedef Operation* OperationPtr;

class Operation : public Glyph
{
public:

	Operation(GlyphPtr parent = GlyphPtr());
	Operation(GlyphPtr parent, const QString &text, QPoint position = QPoint());

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

	//! Определяет пересечение точки с областью глифа
	virtual bool Intersects(const QPoint &point, GlyphList &list) const ;

	/**
	 * Добавляет к глифу потомка.
	 * Будет работать только для глифов, наследуемых от Composite.
	 * Для простых глифов будет иметь пустую реализацию по умолчанию.
	 */
	//virtual void Add(GlyphPtr glyph, size_t position);

	/**
	 * Пробует удалять потомок глифа по позици.
	 */
	//virtual bool Remove(size_t position);

	virtual GlyphPtr Get(size_t position) const ;

	/**
	 * Возвращает родителя глифа.
	 * Пустой указатель, если родителя нет.
	 */
	virtual GlyphPtr Parent()  const throw();

	virtual QString Type() const;

	~Operation();

protected:
	static QString __Type();

protected:
	GlyphPtr parent_;
	QPoint position_;
	QGraphicsTextItemPtr text_;
};

}
