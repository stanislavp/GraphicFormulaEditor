#pragma once

//! Own
#include "Glyph.h"

//! Qt
#include <QGraphicsRectItem>

namespace Graphic
{

//! Forward declaration
class IteratorBacklight;

typedef boost::shared_ptr<IteratorBacklight> IteratorBacklightPtr;

typedef boost::shared_ptr<QGraphicsRectItem> QGraphicsRectItemPtr;

class IteratorBacklight
{
public:
    IteratorBacklight(GlyphPtr glyph = GlyphPtr());

    void Draw(QGraphicsScenePtr scene);
    void SetGlyph(GlyphPtr glyph);

private:
    void UpdateRectangle();

private:
    GlyphPtr glyph_;
    QGraphicsRectItemPtr rectangle_;
};



}
