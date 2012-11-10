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
        numerator->SetPosition(QPoint(position_.x(), position_.y() - bound.height()));
    } else {
        denominator->Add(glyph, position);

        QRect bound = denominator->Bound();
        denominator->SetPosition(QPoint(position_.x(), position_.y() + line_->boundingRect().height()));
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
    return QRect(top.x(), top.y(), top.width() + bottom.width(), top.height() + bottom.height());
}


void Fraction::SetPosition(const QPoint &point)
{
    numerator->SetPosition(QPoint(point.x(), point.y() - numerator->Bound().height()));
    denominator->SetPosition(QPoint(point.x(), point.y() + denominator->Bound().height()));
    position_.setX(point.x());
    position_.setY(point.y());
}

QPoint Fraction::GetPosition()
{
    return position_;
}

GlyphPtr Fraction::Intersects(const QPoint &point)
{
	GlyphPtr glyph = numerator->Intersects(point);

	if(glyph)
		return glyph;

	glyph = denominator->Intersects(point);

	if(glyph)
		return glyph;

	//! Проверять собственный bound
}

void Fraction::Remove(size_t position)
{

}

void Fraction::UpdateLine()
{
    QRect _top = numerator->Bound();
    QRect _bottom = denominator->Bound();

    line_->setLine(position_.x(), position_.y()/* + std::max(_top.height(), _bottom.height())*/,
                   position_.x() + std::max(_top.width(), _bottom.width()),
                   position_.y() /*+ std::max(_top.height(), _bottom.height())*/);
}


Fraction::~Fraction()
{

}

}
