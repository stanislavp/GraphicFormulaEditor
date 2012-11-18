#include "../IteratorBacklight.h"

namespace Graphic
{

IteratorBacklight::IteratorBacklight(GlyphPtr glyph):
	glyph_(glyph), rectangle_(new QGraphicsRectItem()), brush_(0)
{
	brush_= new QBrush(QColor(0, 0, 255, 50));
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
		 QRect _bound = glyph_->Bound();
		 QPoint _position = glyph_->GetPosition();

		 QPoint minPosition = glyph_->GetMinPosition();

		 int diff = _position.y() - minPosition.y();

		 rectangle_->setRect(_bound.x() + _position.x(),
				     _bound.y() + minPosition.y(),
				     _bound.width(),
				     _bound.height() + diff);
		 rectangle_->setBrush(*brush_);
	 }
}

void IteratorBacklight::SetBrush(QBrush brush)
{
	*brush_ = brush;
}

void IteratorBacklight::SetGlyph(GlyphPtr glyph)
{
	 if(glyph)
		 glyph_ = glyph;
}

GlyphPtr IteratorBacklight::GetGlyph() {
	 return glyph_;
}

IteratorBacklight::~IteratorBacklight()
{
	delete rectangle_;
	delete brush_;
}


}
