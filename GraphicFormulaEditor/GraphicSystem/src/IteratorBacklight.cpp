#include "../IteratorBacklight.h"

namespace Graphic
{

IteratorBacklight::IteratorBacklight(GlyphPtr glyph)
    : glyph_(glyph), rectangle_(new QGraphicsRectItem())
{

}

void IteratorBacklight::Draw(QGraphicsScenePtr scene)
{
    if(scene)
    {
        UpdateRectangle();
		scene->addItem(rectangle_);
    }
}

void IteratorBacklight::UpdateRectangle()
{
    if(glyph_)
    {
        std::cerr << (size_t)(&*glyph_) << std::endl;

        QRect _bound = glyph_->Bound();
        QPoint _position = glyph_->GetPosition();

        rectangle_->setRect(_bound.x() + _position.x(),
                            _bound.y() + _position.y(),
                            _bound.width(),
                            _bound.height());
        rectangle_->setBrush(QBrush(QColor(0, 0, 255, 50)));
    }
}

void IteratorBacklight::SetGlyph(GlyphPtr glyph)
{
    if(glyph)
        glyph_ = glyph;
}

}
