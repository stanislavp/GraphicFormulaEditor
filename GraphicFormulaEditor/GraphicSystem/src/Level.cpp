
//! Own
#include "../Level.h"
#include "../Row.h"
#include "../Dummy.h"

//! STL
#include <stdexcept>

namespace Graphic
{

LeveledExpression::LeveledExpression(GlyphPtr parent, QPoint position)
	: Composite(parent), expression_(new Row(GlyphPtr(), position)),
	  level_(new Row(GlyphPtr(), position)), position_(position)
{
	 level_->Add(new Dummy(level_), 0);
	 expression_->Add(new Dummy(expression_), 0);
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
{/*
	 position_.setX(point.x());
	 position_.setY(point.y());

	 level_->SetPosition(QPoint(position_.x() + expression_->Bound().width(), position_.y()));
	 expression_->SetPosition(QPoint(position_.x(), position_.y() + level_->Bound().height()));*/

	 int parentHeight = Parent()->Bound().height();
	 int exprHeight = expression_->Bound().height();

	 int topIndent = (parentHeight - exprHeight) / 2;

	 expression_->SetPosition(QPoint(point.x(), Parent()->GetPosition().y() + topIndent));

	 level_->SetPosition(QPoint(point.x() + expression_->Bound().width(),
				    expression_->GetPosition().y() - level_->Bound().height()));

	 position_.setY(level_->GetPosition().y());
	 position_.setX(point.x());

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

bool LeveledExpression::Remove(size_t position)
{
	 if(position >= (1 << 15)) {
		  if(expression_)
			   return expression_->Remove(position - (1 << 15));
		  else
			   throw std::runtime_error("LeveledExpression::Remove: expression_ has null pointer");
	 } else {
		  if(level_)
			   return level_->Remove(position);
		  else
			   throw std::runtime_error("LeveledExpression::Remove: level_ has null pointer");
	 }

	 return false;
}

GlyphPtr LeveledExpression::Get(size_t position)
{
	if(position > 1)
		throw std::out_of_range("Index out of range");

	return (position == 0 ? expression_ : level_);
}

QPoint LeveledExpression::GetMinPosition() {
	 return level_->GetMinPosition();
}

size_t LeveledExpression::GetPositionByPtr(GlyphPtr ptr)
{
	 size_t position = 0;

	 try {
		  position = level_->GetPositionByPtr(ptr);
		  return position + (1 << 15);
	 } catch(std::logic_error& e) {
		  position = expression_->GetPositionByPtr(ptr);
	 }

	 return position;
}

QString LeveledExpression::__Type()
{
	return QString("LeveledExpression");
}

QString LeveledExpression::Type() const
{
	return __Type();
}

LeveledExpression::~LeveledExpression()
{
	 delete expression_;
	 delete level_;
}

}
