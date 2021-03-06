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

	virtual QRect Bound() const ;

	virtual bool Intersects(const QPoint &point, GlyphList &list) const ;

	virtual GlyphPtr Parent() const throw();

	virtual void SetText(const QString &text);

	virtual void SetPosition(const QPoint &point);

	virtual GlyphPtr Get(size_t position) const ;

	/**
	 * Возвращает позицию глифа.
	 */
	virtual QPoint GetPosition() const ;

	virtual QString Type() const;

	virtual ~Variable();

protected:
	static QString __Type();

protected:
	GlyphPtr parent_;
	QGraphicsTextItemPtr text_;
	QPoint position_;
};

}
