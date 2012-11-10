#include "../Fraction.h"
#include "../Row.h"

#ifdef DEBUG
#include <iostream>
#endif

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

#ifdef DEBUG
    std::cout << "Fraction: " << position_.x() << " " << position_.y() << std::endl;
#endif

    if(position >= (1 << 15)) {
        numerator->Add(glyph, position - (1 << 15));

        QRect bound = numerator->Bound();
        numerator->SetPosition(QPoint(position_.x(), position_.y()));
    } else {
        denominator->Add(glyph, position);

        QRect bound = denominator->Bound();
        denominator->SetPosition(QPoint(position_.x(), position_.y() + line_->boundingRect().height() + numerator->Bound().height()));
    }

#ifdef DEBUG
    std::cout << "Fraction after adding: " << position_.x() << " " << position_.y() << std::endl;
#endif

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
        return QRect(0, 0, std::max(top.width(), bottom.width()), top.height() + bottom.height() + line_->boundingRect().height());
}


void Fraction::SetPosition(const QPoint &point)
{
    numerator->SetPosition(QPoint(point.x(), point.y()));
    denominator->SetPosition(QPoint(point.x(), point.y() + numerator->Bound().height()));
    position_.setX(point.x());
    position_.setY(point.y());
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
