#include "../Operation.h"

//! STL
#include <stdexcept>

namespace Graphic
{

Operation::Operation(GlyphPtr parent)
	: parent_(parent), position_(QPoint())
{
	text_.reset(new QGraphicsTextItem());
}

Operation::Operation(GlyphPtr parent, const QString &text, QPoint position)
	: parent_(parent), position_(position)
{
	text_.reset(new QGraphicsTextItem());
	text_->setPlainText(text);
}

void Operation::Draw(QGraphicsScenePtr scene)
{
	if(scene && text_)
	{
	text_->setPos(position_);
		scene->addItem(text_.get());
	}
}

QRect Operation::Bound()
{
	if(text_)
		return text_->boundingRect().toRect();

	throw std::logic_error("Operation::Bound(): text_ null pointer. ");
}

void Operation::SetPosition(const QPoint &point)
{
	position_.setX(point.x());
	position_.setY(point.y());
}

QPoint Operation::GetPosition()
{
	return position_;
}

GlyphPtr Operation::Intersects(const QPoint &point)
{
	if(text_)
	{
		QRect _bound = text_->boundingRect().toRect();
		if(_bound.contains(point))
			return OperationPtr(this);
	}
	return GlyphPtr();
}

GlyphPtr Operation::Parent() throw()
{
	return parent_;
}

Operation::~Operation()
{

}

}
