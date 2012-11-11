#include "../Row.h"

namespace Graphic
{

Row::Row(GlyphPtr parent, QPoint position)
	: Composite(parent), position_(position)
{

}

void Row::Add(GlyphPtr glyph, size_t position)
{
	/**
	 * Пока забъём на position, будем пихать в конец
	 */

        if(contents_.empty())
	{
		//! TODO: указать родителя, как this
		glyph->SetPosition(position_);
		contents_.push_back(glyph);
	} else
	{
		QPoint lastPosition = contents_.back()->GetPosition();

		glyph->SetPosition(QPoint(lastPosition.x() + contents_.back()->Bound().width(), lastPosition.y()));
		contents_.push_back(glyph);
	}
}

void Row::SetPosition(const QPoint &point)
{
    QPoint shift(0, 0);
    for(Content::iterator i = contents_.begin(); i != contents_.end(); ++i) {
        (*i)->SetPosition(point + shift);
        shift.setX(shift.x() + (*i)->Bound().width());
    }

	position_.setX(point.x());
	position_.setY(point.y());
}

QPoint Row::GetPosition()
{
	return position_;
}

Row::~Row()
{

}

}
