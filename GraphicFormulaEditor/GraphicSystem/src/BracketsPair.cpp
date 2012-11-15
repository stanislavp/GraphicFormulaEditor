#include "../BracketsPair.h"

// STL
#include <stdexcept>

namespace Graphic
{

BracketsPair::BracketsPair(GlyphPtr parent, QPoint position):
    Composite(parent), position_(position),
    frontBracket_(new Variable(parent, "(", position)),
    backBracket_(new Variable(parent, ")", position)) {

    row_ = (new Row(GlyphPtr(this), position_ + QPoint(frontBracket_->Bound().width(), 0)));

}

void BracketsPair::Draw(QGraphicsScenePtr scene)
{
	frontBracket_->Draw(scene);
	if(row_)
		row_->Draw(scene);
	backBracket_->Draw(scene);
}

QRect BracketsPair::Bound()
{
    using std::max;

    QRect result = frontBracket_->Bound();

    int width = result.width();
    int height = result.height();

    result = backBracket_->Bound();
    width += result.width();
    height = max(height, result.height());

    if(row_) {
	result = row_->Bound();
	width += result.width();
	height = max(height, result.height());
    }

    return QRect(0, 0, width, height);
}

bool BracketsPair::Intersects(const QPoint &point, GlyphList &list)
{
	if(frontBracket_->Intersects(point, list))
	{
		list.back() = this;
		return true;
	} else if(backBracket_->Intersects(point, list))
	{
		list.back() = this;
		return true;
	} else if(row_->Intersects(point, list))
	{
		list.push_back(this);
		return true;
	}
	return false;
}

void BracketsPair::Add(GlyphPtr glyph, size_t position)
{
    row_->Add(glyph, position);
    backBracket_->SetPosition(row_->GetPosition() + QPoint(row_->Bound().width(), 0));
}

void BracketsPair::Remove(size_t position)
{
    if(row_)
	row_->Remove(position);
    else
	throw std::runtime_error("BracketsPair::Remove: row_ has null pointer");
}

void BracketsPair::SetPosition(const QPoint &point)
{
    frontBracket_->SetPosition(point);

    QPoint position = point;
    QRect bounds = frontBracket_->Bound();
    position.setX(position.x() + bounds.width());

    if(row_) {
	row_->SetPosition(position);
	position.setX(position.x() + row_->Bound().width());
    }

    backBracket_->SetPosition(position);
    position_.setX(point.x());
    position_.setY(point.y());
}

QPoint BracketsPair::GetPosition()
{
    return position_;
}

BracketsPair::~BracketsPair()
{
    delete frontBracket_;
    delete row_;
    delete backBracket_;
}

GlyphPtr BracketsPair::get(size_t position)
{
    if(position	> 0)
	throw std::out_of_range("Index out of range");
    return row_;
}

}
