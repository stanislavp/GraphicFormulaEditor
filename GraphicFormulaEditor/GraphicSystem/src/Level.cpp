
//! Own
#include "../Level.h"
#include "../Row.h"

//! STL
#include <stdexcept>

namespace Graphic
{

LeveledExpression::LeveledExpression(GlyphPtr parent, QPoint position)
	: Composite(parent), expression_(new Row(GlyphPtr(), position)),
	  level_(new Row(GlyphPtr(), position)), position_(position)
{

}

void LeveledExpression::Draw(QGraphicsScenePtr scene)
{
	if(!expression_)
		throw std::runtime_error("LeveledExpression::Bound(): expression_ null ptr. ");

	if(!level_)
		throw std::runtime_error("LeveledExpression::Bound(): level_ null ptr. ");

	expression_->Draw(scene);
	level_->Draw(scene);
}

QRect LeveledExpression::Bound()
{
	QRect expressionBound;
	if(expression_)
		expressionBound = expression_->Bound();
	else
		throw std::runtime_error("LeveledExpression::Bound(): expression_ null ptr. ");

	QRect levelBound;
	if(level_)
		levelBound = level_->Bound();
	else
		throw std::runtime_error("LeveledExpression::Bound(): level_ null ptr. ");

	return QRect(0, 0, expressionBound.width() + levelBound.width(), expressionBound.height() + levelBound.height());
}

bool LeveledExpression::Intersects(const QPoint &point, GlyphList &list)
{
	if(expression_)
	{
		if(expression_->Intersects(point, list))
		{
			list.push_back(this);
			return true;
		}
	} else
		throw std::runtime_error("LeveledExpression::Intersects(): expression_ null ptr. ");

	if(level_)
	{
		if(level_->Intersects(point, list))
		{
			list.push_back(this);
			return true;
		}
	} else
		throw std::runtime_error("LeveledExpression::Intersects(): level_ null ptr. ");

	return false;
}

void LeveledExpression::SetPosition(const QPoint &point)
{
	position_.setX(point.x());
	position_.setY(point.y());

	expression_->SetPosition(QPoint(position_.x(), position_.y() + level_->Bound().height()));
	QRect bound = expression_->Bound();
	level_->SetPosition(QPoint(position_.x() + bound.width(), position_.y()));

}

QPoint LeveledExpression::GetPosition()
{
	return position_;
}

void LeveledExpression::Add(GlyphPtr glyph, size_t position)
{
	if(position >= (1 << 15))
	{
		expression_->Add(glyph, position - (1 << 15));
		expression_->SetPosition(QPoint(position_.x(), position_.y()));
	} else
	{
		level_->Add(glyph, position);

		QRect bound = expression_->Bound();
		level_->SetPosition(QPoint(position_.x() + bound.width(), position_.y() - bound.height()));
	}
}

void LeveledExpression::Remove(size_t position)
{

}

}
