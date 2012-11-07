#include "../Function.h"

//!
#include <stdexcept>

namespace Graphic
{

Function::Function(const QString &name, GlyphPtr parent, QPoint position):
	Composite(parent), position_(position)
{
	name_.reset(new Variable(GlyphPtr(), name, position));
	brackets_.reset(new BracketsPair());

	brackets_->SetPosition(position_ + QPoint(name_->Bound().width(), 0));
}

void Function::Draw(QGraphicsScenePtr scene)
{
    name_->Draw(scene);
    brackets_->Draw(scene);
}

QRect Function::Bound()
{
    using std::max;

    QRect result = name_->Bound();

    int width = result.width();
    int height = result.height();

    result = brackets_->Bound();

    width += result.width();
    height = max(height, result.height());

    return QRect(0, 0, width, height);
}

void Function::SetPosition(const QPoint &point)
{
    name_->SetPosition(point);

    brackets_->SetPosition(point + QPoint(name_->Bound().width(), 0));

    position_.setX(point.x());
    position_.setY(point.y());
}

QPoint Function::GetPosition()
{
    return position_;
}

GlyphPtr Function::Intersects(const QPoint &point)
{
	GlyphPtr glyph = brackets_->Intersects(point);
	if(glyph)
		return glyph;
	else
	{
		glyph = name_->Intersects(point);
		if(glyph)
		{
			return FunctionPtr(this);
		}
	}
	return GlyphPtr();
}

void Function::Add(GlyphPtr glyph, size_t position)
{
    brackets_->Add(glyph, position);
}

void Function::Remove(size_t position)
{

}


}
