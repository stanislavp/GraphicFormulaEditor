#pragma once

//! Own
#include "Glyph.h"

//! Qt
#include <QGraphicsTextItem>


namespace Graphic
{

//typedef boost::shared_ptr<QGraphicsTextItem> QGraphicsTextItemPtr;

typedef QGraphicsTextItem* QGraphicsTextItemPtr;

class Variable;
//typedef boost::shared_ptr<Variable> VariablePtr;

typedef Variable* VariablePtr;

/**
 * TODO.
 * Есть непонятная проблема shared_ptr валит QGraphicTextItem при вызове дестркутора.
 */

class Variable : public Glyph
{
public:

	Variable(GlyphPtr parent = GlyphPtr());
	Variable(GlyphPtr parent, const QString &text, const QPoint &position = QPoint());

	virtual void Draw(QGraphicsScenePtr scene);

	virtual QRect Bound();

	virtual GlyphPtr Intersects(const QPoint &point);

	virtual GlyphPtr Parent() throw();

	virtual void SetText(const QString &text);

	virtual void SetPosition(const QPoint &point);

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition();

	virtual ~Variable();
protected:
	GlyphPtr parent_;
	QGraphicsTextItem text_;
	QPoint position_;
};

}
