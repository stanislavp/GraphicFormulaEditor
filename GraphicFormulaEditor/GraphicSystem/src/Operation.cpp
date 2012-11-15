#include "../Operation.h"

//! STL
#include <stdexcept>
#include "../../Exceptions/IsPlainGlyph.h"

namespace Graphic
{

Operation::Operation(GlyphPtr parent)
	: parent_(parent), position_(QPoint())
{
	text_ = (new QGraphicsTextItem());
}

Operation::Operation(GlyphPtr parent, const QString &text, QPoint position)
	: parent_(parent), position_(position)
{
	text_ = (new QGraphicsTextItem());
	text_->setPlainText(text);
}

void Operation::Draw(QGraphicsScenePtr scene)
{
	if(scene && text_)
	{
	text_->setPos(position_);
		scene->addItem(text_);
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

bool Operation::Intersects(const QPoint &point, GlyphList &list)
{
	if(text_)
	{
		QRect _textBound = text_->boundingRect().toRect();
		QRect tempBound(position_.x(), position_.y(),
						_textBound.width(), _textBound.height());

		if(tempBound.contains(point))
		{
			list.push_back(this);
			return true;
		}
	}
	return false;
}

GlyphPtr Operation::Get(size_t position)
{
	throw Exception::IsPlainGlyph("Operation::Get(): is plain. ");
}

GlyphPtr Operation::Parent() throw()
{
	return parent_;
}

Operation::~Operation()
{

}

}
