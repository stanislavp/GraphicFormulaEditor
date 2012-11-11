#include "../Fraction.h"
#include "../Row.h"

// STL
#include <stdexcept>

namespace Graphic
{

Fraction::Fraction(GlyphPtr parent, QPoint position)
    : Composite(parent), position_(position),
      numerator(GlyphPtr(new Row(GlyphPtr(this), position))),
      denominator(GlyphPtr(new Row(GlyphPtr(this), position))),
      line_(new QGraphicsLineItem())
{
}

void Fraction::Add(GlyphPtr glyph, size_t position)
{
    if(position >= (1 << 15)) {
        numerator->Add(glyph, position - (1 << 15));
    } else {
        denominator->Add(glyph, position);
        denominator->SetPosition(QPoint(position_.x(), position_.y() +
                                        line_->boundingRect().height() + numerator->Bound().height()));
    }
}

void Fraction::Draw(QGraphicsScenePtr scene)
{
    numerator->Draw(scene);
    UpdateLine();
    scene->addItem(line_);
    denominator->Draw(scene);
}


QRect Fraction::Bound()
{
	QRect top = numerator->Bound();
	QRect bottom = denominator->Bound();
        return QRect(0, 0, std::max(top.width(), bottom.width()),
                     top.height() + bottom.height() + line_->boundingRect().height());
}


void Fraction::SetPosition(const QPoint &point)
{
    QPoint aligned(point);
    if(Parent()) {
        int parentHeight = Parent()->Bound().height();
        int selfHeight = Bound().height();
        int diff = 0;

        if(parentHeight > selfHeight)
            diff = (parentHeight - selfHeight) / 4;
        else
            diff = selfHeight / 4;

        aligned.setY(aligned.y() - diff);

    }

    numerator->SetPosition(QPoint(aligned.x(), aligned.y()));
    denominator->SetPosition(QPoint(aligned.x(), aligned.y() + numerator->Bound().height()));
    position_.setX(aligned.x());
    position_.setY(aligned.y());
}

QPoint Fraction::GetPosition()
{
    return position_;
}

bool Fraction::Intersects(const QPoint &point, GlyphList &list)
{
	if(numerator->Intersects(point, list))
	{
		list.push_back(this);
		return true;
	} else if(denominator->Intersects(point, list))
	{
		list.push_back(this);
		return true;
	}
	return false;
}

void Fraction::Remove(size_t position)
{
    if(position >= (1 << 15)) {
	if(numerator)
	    numerator->Remove(position - (1 << 15));
	else
	    throw std::runtime_error("Fraction::Remove: numerator has null pointer");
    } else {
	if(denominator)
	    denominator->Remove(position);
	else
	    throw std::runtime_error("Fraction::Remove: denominator has null pointer");
    }
}

void Fraction::UpdateLine()
{
    QRect _top = numerator->Bound();
    QRect _bottom = denominator->Bound();

    line_->setLine(position_.x(), position_.y() + _top.height(),
                   position_.x() + std::max(_top.width(), _bottom.width()),
                   position_.y() + _top.height());
}


Fraction::~Fraction()
{

}

}
