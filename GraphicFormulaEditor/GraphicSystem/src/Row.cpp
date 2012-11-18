#include "../Row.h"
#include "../Dummy.h"

namespace Graphic
{

Row::Row(GlyphPtr parent, QPoint position)
	: Composite(parent), position_(position)
{

}

void Row::Add(GlyphPtr glyph, size_t position)
{
	 if(contents_.size() == 1) {
		  try {
			   DummyPtr ptr = dynamic_cast<DummyPtr>(contents_.back());
			   if(ptr != 0) {
				    Remove(0);
			   }
		  } catch(const std::exception& e) {
		  }
	 }

	 if(contents_.empty())
	{
		//! TODO: указать родителя, как this
		glyph->SetPosition(position_);
		contents_.push_back(glyph);
	} else
	{
		  int count = 0;
		  bool inserted = false;
		  for(Content::iterator it = contents_.begin(); it != contents_.end(); ++it, ++count) {
			   if(count == position) {
				    Content::iterator _it = it;
				    --_it;
				    if(_it != contents_.begin() && it != contents_.begin()) {
					     --_it;
					     QPoint lastPosition = (*_it)->GetPosition();
					     glyph->SetPosition(QPoint(lastPosition.x() + (*_it)->Bound().width(), lastPosition.y()));
				    }

				    contents_.insert(it, glyph);
				    inserted = true;
				    break;
			   }
		  }

		  if(!inserted) {
			   QPoint lastPosition = contents_.back()->GetPosition();
			   glyph->SetPosition(QPoint(lastPosition.x() + contents_.back()->Bound().width(), lastPosition.y()));

			   contents_.push_back(glyph);
		  }
	 }
}

void Row::SetPosition(const QPoint &point)
{
	 position_.setX(point.x());
	 position_.setY(point.y());

	 int cumlWidth = 0;
	 int rowHeight = Bound().height();

	 for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it) {
		  int localHeight = (*it)->Bound().height();
		  int topIndent = (rowHeight - localHeight) / 2;

		  (*it)->SetPosition(QPoint(point.x() + cumlWidth, point.y() + topIndent));
		  cumlWidth += (*it)->Bound().width();
	 }
}

QPoint Row::GetPosition()
{
	return position_;
}

Row::~Row()
{

}

}
