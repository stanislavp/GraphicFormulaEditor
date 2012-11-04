#include "../Composite.h"

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
	/*int top = std::numeric_limits<int>::max(),
			left = std::numeric_limits<int>::max(),
			right = std::numeric_limits<int>::min(),
			bottom = std::numeric_limits<int>::min();*/

    int width = 0, height = 0;

	for(Content::const_iterator _it(contents_.begin()); _it != contents_.end(); ++_it)
	{
		QRect _bound = (*_it)->Bound();

		/*if(_bound.top() < top)
			top = _bound.top();

		if(_bound.left() < left)
			left = _bound.left();

		if(_bound.right() > right)
			right = _bound.right();

		if(_bound.bottom() > bottom)
			bottom = _bound.bottom();*/

		width += _bound.width();
		height += _bound.height();
	}

	return QRect(0, 0, width, height);

	//return QRect(left, top, std::abs(right - left), std::abs(top - bottom));
}

GlyphPtr Composite::Intersects(const QPoint &point)
{
	for(Content::const_iterator _it(contents_.begin()); _it != contents_.end(); ++_it)
	{
		GlyphPtr _glyph = (*_it)->Intersects(point);
		if(_glyph)
			return _glyph;
	}
	return GlyphPtr();
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

void Composite::Remove(size_t position)
{

	if(position >= contents_.size())
		throw std::overflow_error("Composite::Remove: position > size. ");

	size_t _count = 0;

	for(Content::iterator _it(contents_.begin()); _it != contents_.end(); ++_it, ++_count)
	{
		if(_count == position)
		{
			contents_.erase(_it);
		}
	}
}

GlyphPtr Composite::Parent() throw()
{
	return parent_;
}


}
