#include "../Function.h"

//!
#include <stdexcept>

namespace Graphic
{

Function::Function(const QString &name, GlyphPtr parent, QPoint position):
	Composite(parent), position_(position)
{
    name_ = (new Variable(parent, name, position));
    brackets_ = (new BracketsPair(parent));

    brackets_->SetPosition(position_ + QPoint(name_->Bound().width(), 0));
}

void Function::Draw(QGraphicsScenePtr scene)
{
    name_->Draw(scene);
    brackets_->Draw(scene);
}

QRect Function::Bound()
{
    QRect result = name_->Bound();

    int width = result.width();
    int height = result.height();

    result = brackets_->Bound();

    width += result.width();
    height = std::max(height, result.height());

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

bool Function::Intersects(const QPoint &point, GlyphList &list)
{
	if(brackets_->Intersects(point, list))
	{
		list.push_back(this);
		return true;
	} else if(name_->Intersects(point, list))
	{
		list.push_back(this);
		return true;
	}
	return false;
}

void Function::Add(GlyphPtr glyph, size_t position)
{
    brackets_->Add(glyph, position);
}

void Function::Remove(size_t position)
{
    brackets_->Remove(position);
}

Function::~Function()
{
    delete brackets_;
    delete name_;
}

}
