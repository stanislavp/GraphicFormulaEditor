#pragma once

//! Own
#include "Glyph.h"

//! Qt
#include <QGraphicsRectItem>
#include <QBrush>

namespace Graphic
{

//! Forward declaration
class IteratorBacklight;

//typedef boost::shared_ptr<IteratorBacklight> IteratorBacklightPtr;

typedef IteratorBacklight* IteratorBacklightPtr;

//typedef boost::shared_ptr<QGraphicsRectItem> QGraphicsRectItemPtr;

typedef QGraphicsRectItem* QGraphicsRectItemPtr;

class IteratorBacklight
{
public:
	IteratorBacklight(GlyphPtr glyph = GlyphPtr());

	void Draw(QGraphicsScenePtr scene);
	void SetGlyph(GlyphPtr glyph);

	GlyphPtr GetGlyph();
	void SetBrush(QBrush brush);

	~IteratorBacklight();

private:
	void UpdateRectangle();

private:
	GlyphPtr glyph_;
	QBrush *brush_;
	QGraphicsRectItemPtr rectangle_;
};



}
