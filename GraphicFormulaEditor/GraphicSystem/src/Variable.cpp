#include "../Variable.h"

//! STL
#include <stdexcept>

namespace Graphic
{

Variable::Variable(GlyphPtr parent) : parent_(parent)
{
	text_.setPlainText(QString("y"));
}

Variable::Variable(GlyphPtr parent, const QString &text, const QPoint &position)
	: parent_(parent), position_(position)
{
	text_.setPlainText(text);
}

void Variable::Draw(QGraphicsScenePtr scene)
{
	if(scene)
	{
	text_.setPos(position_);
		scene->addItem(&text_);
	}
}

QRect Variable::Bound()
{
    std::cout << " ";
	return text_.boundingRect().toRect();
}

GlyphPtr Variable::Intersects(const QPoint &point)
{
	/**
	 * Эталонный bound.
	 * boundingRect возвращает bound без привязки\
	 * к координатам, поэтому берём его, переводим координаты в свои\
	 * и проверяем на вхождение точки.
	 */

	QRect _textBound = text_.boundingRect().toRect();
	QRect tempBound(position_.x(),
					position_.y(),
					_textBound.width(),
					_textBound.height());
        if(tempBound.contains(point)) {
            std::cerr << (size_t)(this) << std::endl;
				return this;
        }

	return GlyphPtr();
}

GlyphPtr Variable::Parent() throw()
{
	return parent_;
}

void Variable::SetText(const QString &text)
{
	if(!text.isEmpty())
		text_.setPlainText(text);
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
}


}
