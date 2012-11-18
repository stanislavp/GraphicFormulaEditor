#include "../Composite.h"
#include "../Dummy.h"

//! STL
#include <stdexcept>
#include <vector>
#include <limits>
#include <cmath>

namespace Graphic
{


Composite::Composite(GlyphPtr parent) : parent_(parent)
{

}

void Composite::Draw(QGraphicsScenePtr scene)
{
	for(Content::const_iterator _it(contents_.begin()); _it != contents_.end(); ++_it)
	{
		(*_it)->Draw(scene);
	}
}

QRect Composite::Bound()
{
	 int width = 0, height = 0;

	 for(Content::const_iterator _it(contents_.begin()); _it != contents_.end(); ++_it)
	 {
		  QRect _bound = (*_it)->Bound();

		  width += _bound.width();
		  height = std::max(height, _bound.height());
	 }

	 return QRect(0, 0, width, height);
}

bool Composite::Intersects(const QPoint &point, GlyphList &list)
{
	for(Content::const_iterator _it(contents_.begin()); _it != contents_.end(); ++_it)
	{
		if((*_it)->Intersects(point, list))
		{
			list.push_back(this);
			return true;
		}
	}
	return false;
}

void Composite::Add(GlyphPtr glyph, size_t position)
{
	size_t _size = contents_.size();

	if(position < _size)
	{
		if(position)
		{
			size_t _count = 0;

			for(Content::iterator _it(contents_.begin()); _it != contents_.end(); ++_it, ++_count)
			{
				if(_count == position)
				{
					contents_.insert(_it, glyph);
				}
			}
		} else
		{
			contents_.push_front(glyph);
		}
	} else
	{
		contents_.push_back(glyph);
	}
}

bool Composite::Remove(size_t position)
{

	if(position >= contents_.size())
		throw std::overflow_error("Composite::Remove: position > size. ");

	size_t _count = 0;

	if(contents_.size() == 1) {
		 try {
			  DummyPtr ptr = dynamic_cast<DummyPtr>(contents_.back());
			  if(ptr == 0) {
				   contents_.erase(contents_.begin());
				   Add(new Dummy(Parent()), 0);
				   return true;
			  } else
				   return false;
		 } catch(const std::exception& e) {
		 }
	}

	for(Content::iterator _it(contents_.begin()); _it != contents_.end(); ++_it, ++_count)
	{
		if(_count == position)
		{
			contents_.erase(_it);
			return true;
		}
	}

	return false;
}

GlyphPtr Composite::Get(size_t position) {
	if(position >= contents_.size())
		throw std::out_of_range("Index out of range");

	int count = 0;
	for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it, ++count) {
		if(count == position)
			return *it;
	}
}

size_t Composite::GetPositionByPtr(GlyphPtr ptr)
{
	 size_t result = 0;
	 for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it, ++result) {
		  if(*it == ptr)
		  return result;
	 }

	 throw std::logic_error("This glyph is not here.");
}

GlyphPtr Composite::Parent() throw()
{
	return parent_;
}

QString Composite::__Type()
{
	return QString("Composite");
}

QString Composite::Type() const
{
	return __Type();
}

Composite::~Composite()
{
	for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it)
	{
		delete *it;
	}
}


}
