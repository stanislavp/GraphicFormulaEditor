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

QRect Operation::Bound() const
{
	if(text_)
		return text_->boundingRect().toRect();

	throw std::logic_error("Operation::Bound(): text_ null pointer. ");
}

void Operation::SetPosition(const QPoint &point)
{
	position_.setX(point.x());
	position_.setY(point.y());
	text_->setPos(position_);
}

QPoint Operation::GetPosition() const
{
	return position_;
}

bool Operation::Intersects(const QPoint &point, GlyphList &list) const
{
	if(text_)
	{
		QRect _textBound = text_->boundingRect().toRect();
		QRect tempBound(position_.x(), position_.y(),
						_textBound.width(), _textBound.height());

		if(tempBound.contains(point))
		{
			list.push_back(const_cast<OperationPtr>(this));
			return true;
		}
	}
	return false;
}

GlyphPtr Operation::Get(size_t position) const
{
	throw Exception::IsPlainGlyph("Operation::Get(): is plain. ");
}

GlyphPtr Operation::Parent() const throw()
{
	return parent_;
}

QString Operation::__Type()
{
	return QString("Operation");
}

QString Operation::Type() const
{
	return __Type();
}

Operation::~Operation()
{
	delete text_;
}

}
