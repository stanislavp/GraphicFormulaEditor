#include "../Fraction.h"
#include "../Row.h"
#include "../Dummy.h"

// STL
#include <stdexcept>

namespace Graphic
{

Fraction::Fraction(GlyphPtr parent, QPoint position):
	 Composite(parent), position_(position),
	 numerator(GlyphPtr(new Row(GlyphPtr(this), position))),
	 denominator(GlyphPtr(new Row(GlyphPtr(this), position))),
	 line_(new QGraphicsLineItem())
{
	 numerator->Add(new Dummy(numerator), 0);
	 denominator->Add(new Dummy(denominator), 0);
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
	 scene->addItem(line_);
	 denominator->Draw(scene);
}


QRect Fraction::Bound() const
{
	QRect top = numerator->Bound();
	QRect bottom = denominator->Bound();
		 return QRect(0, 0, std::max(top.width(), bottom.width()),
					  top.height() + bottom.height() + line_->boundingRect().height());
}


void Fraction::SetPosition(const QPoint &point)
{
	 position_.setX(point.x());
	 position_.setY(point.y());

	 int numWidth = numerator->Bound().width();
	 int denWidth = denominator->Bound().width();
	 int width = std::max(numWidth, denWidth);

	 numerator->SetPosition(QPoint(point.x() + (width - numWidth) / 2, point.y()));
	 denominator->SetPosition(QPoint(position_.x() + (width - denWidth) / 2, position_.y() + numerator->Bound().height()));

	 UpdateLine();
}

QPoint Fraction::GetPosition() const
{
	 return position_;
}

bool Fraction::Intersects(const QPoint &point, GlyphList &list) const
{
	if(numerator->Intersects(point, list))
	{
		list.push_back(const_cast<FractionPtr>(this));
		return true;
	} else if(denominator->Intersects(point, list))
	{
		list.push_back(const_cast<FractionPtr>(this));
		return true;
	}
	return false;
}

bool Fraction::Remove(size_t position)
{
	if(position >= (1 << 15)) {
		 if(numerator)
			  return numerator->Remove(position - (1 << 15));
		 else
			  throw std::runtime_error("Fraction::Remove: numerator has null pointer");
	} else {
		 if(denominator)
			  return denominator->Remove(position);
		 else
			  throw std::runtime_error("Fraction::Remove: denominator has null pointer");
	}

	return false;
}

void Fraction::UpdateLine()
{
	 QRect _top = numerator->Bound();
	 QRect _bottom = denominator->Bound();

	 line_->setLine(position_.x(), position_.y() + _top.height(),
			position_.x() + std::max(_top.width(), _bottom.width()),
			position_.y() + _top.height());
}

GlyphPtr Fraction::Get(size_t position) const
{
	if(position > 1)
		throw std::out_of_range("Index out of range");

	return (position == 0 ? numerator : denominator);
}

size_t Fraction::GetPositionByPtr(GlyphPtr ptr) const
{
	 size_t position = 0;

	 try {
		  position = numerator->GetPositionByPtr(ptr);
		  return position + (1 << 15);
	 } catch(std::logic_error& e) {
		  position = denominator->GetPositionByPtr(ptr);
	 }

	 return position;
}

QString Fraction::__Type()
{
	return QString("Fraction");
}

QString Fraction::Type() const
{
	return __Type();
}

Fraction::~Fraction()
{
	 delete numerator;
	 delete line_;
	 delete denominator;
}

}
