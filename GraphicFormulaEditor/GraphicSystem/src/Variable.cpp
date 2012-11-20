#include "../Variable.h"

//! STL
#include <stdexcept>
#include "../../Exceptions/IsPlainGlyph.h"

namespace Graphic
{

Variable::Variable(GlyphPtr parent) : parent_(parent), text_(new QGraphicsTextItem)
{
	text_->setPlainText(QString("y"));
}

Variable::Variable(GlyphPtr parent, const QString &text, const QPoint &position)
	: parent_(parent), text_(new QGraphicsTextItem), position_(position)
{
	text_->setPlainText(text);
}

void Variable::Draw(QGraphicsScenePtr scene)
{
	if(scene)
	{
	text_->setPos(position_);
		scene->addItem(text_);
	}
}

QRect Variable::Bound() const
{
	return text_->boundingRect().toRect();
}

bool Variable::Intersects(const QPoint &point, GlyphList &list) const
{
	/**
	 * Эталонный bound.
	 * boundingRect возвращает bound без привязки\
	 * к координатам, поэтому берём его, переводим координаты в свои\
	 * и проверяем на вхождение точки.
	 */

	QRect _textBound = text_->boundingRect().toRect();

	QRect tempBound(position_.x(), position_.y(),
					_textBound.width(),_textBound.height());
	if(tempBound.contains(point))
	{
		list.push_back(const_cast<VariablePtr>(this));
		return true;
	}
	return false;
}

GlyphPtr Variable::Parent()  const throw()
{
	return parent_;
}

void Variable::SetText(const QString &text)
{
	if(!text.isEmpty())
		text_->setPlainText(text);
}

void Variable::SetPosition(const QPoint &point)
{
	position_.setX(point.x());
	position_.setY(point.y());
	text_->setPos(position_);
}

QPoint Variable::GetPosition() const
{
	return position_;
}

GlyphPtr Variable::Get(size_t position) const
{
	throw Exception::IsPlainGlyph("Operation::Get(): is plain. ");
}

QString Variable::__Type()
{
	return QString("Variable");
}

QString Variable::Type() const
{
	return __Type();
}


Variable::~Variable()
{
	delete text_;
}


}
