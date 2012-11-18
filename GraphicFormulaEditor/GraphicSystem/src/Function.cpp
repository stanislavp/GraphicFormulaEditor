#include "../Function.h"
#include "../Dummy.h"

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

	 brackets_->Add(new Dummy(brackets_), 0);
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
	 QRect bracketsBound = brackets_->Bound();
	 QRect nameBound = name_->Bound();

	 int topIndent = (bracketsBound.height() - nameBound.height()) / 2;

	 name_->SetPosition(QPoint(point.x(), point.y() + topIndent));

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
		list.back() = this;
		return true;
	} else if(name_->Intersects(point, list))
	{
		list.back() = this;
		return true;
	}
	return false;
}

void Function::Add(GlyphPtr glyph, size_t position)
{
	 brackets_->Add(glyph, position);
}

bool Function::Remove(size_t position)
{
	return brackets_->Remove(position);
}

GlyphPtr Function::Get(size_t position)
{
	if(position > 0)
		throw std::out_of_range("Index out of range");

	return brackets_;
}

size_t Function::GetPositionByPtr(GlyphPtr ptr)
{
	 return brackets_->GetPositionByPtr(ptr);
}

QString Function::__Type()
{
	return QString("function");
}

QString Function::Type() const
{
	return __Type();
}


Function::~Function()
{
	 delete brackets_;
	 delete name_;
}

}
