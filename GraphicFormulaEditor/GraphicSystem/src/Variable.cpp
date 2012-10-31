#include "../Variable.h"

//! STL
#include <stdexcept>

namespace Graphic
{

Variable::Variable(GlyphPtr parent) : parent_(parent)
{
	text_.reset(new QGraphicsTextItem());
	text_->setPlainText(QString("y"));
}

Variable::Variable(GlyphPtr parent, const QString &text, const QPoint &position)
	: parent_(parent), position_(position)
{
	text_.reset(new QGraphicsTextItem());
	text_->setPlainText(text);
}

void Variable::Draw(QGraphicsScenePtr scene)
{
	if(text_ && scene)
	{
		text_->setPos(position_);
		scene->addItem(text_.get());
	}
}

QRect Variable::Bound()
{
	if(text_)
	{
		return text_->boundingRect().toRect();
	}

	throw std::logic_error("Variable::Bound: text item null pointer. ");
}

GlyphPtr Variable::Intersects(const QPoint &point)
{
	if(text_)
	{
		QRect _bound = text_->boundingRect().toRect();
		if(_bound.contains(point))
			return VariablePtr(this);
	}
	return GlyphPtr();
}

GlyphPtr Variable::Parent() throw()
{
	return parent_;
}

void Variable::SetText(const QString &text)
{
	if(text_ && !text.isEmpty())
		text_->setPlainText(text);
}

void Variable::SetPosition(const QPoint &point)
{
	position_.setX(point.x());
	position_.setY(point.y());
}

QPoint Variable::GetPosition()
{
	return position_;
}

Variable::~Variable()
{
	text_.reset();
}


}
