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
        int before = numerator->Bound().height();
        numerator->Add(glyph, position - (1 << 15));

        int after = numerator->Bound().height();
        SetPosition(QPoint(position_.x(), position_.y() + after - before));
    } else {
        int before = denominator->Bound().height();
        denominator->Add(glyph, position);

        int after = denominator->Bound().height();
        SetPosition(QPoint(position_.x(), position_.y() - after + before));
    }

#ifdef DEBUG
    std::cout << "Fraction after adding: " << position_.x() << " " << position_.y() << std::endl;
#endif

}

void Fraction::Draw(QGraphicsScenePtr scene)
{
    numerator->Draw(scene);
    UpdateLine();
    scene->addItem(line_.get());
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

void Fraction::Remove(size_t position)
{

}

void Fraction::UpdateLine()
{
    QRect _top = numerator->Bound();
    QRect _bottom = denominator->Bound();

    line_->setLine(position_.x(), position_.y() + std::max(_top.height(), _bottom.height()),
                   position_.x() + std::max(_top.width(), _bottom.width()),
                   position_.y() + std::max(_top.height(), _bottom.height()));
}


Fraction::~Fraction()
{

}

}
