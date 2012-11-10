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

    using std::max;

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
                height = max(height, _bound.height());
	}

	return QRect(0, 0, width, height);

	//return QRect(left, top, std::abs(right - left), std::abs(top - bottom));
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


void Composite::updatePositions(int height)
{
    int heightDiff = getMaxHeihgt() - height;
    for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it) {
        QPoint position;

        if(it != contents_.begin()) {
            Content::const_iterator _it = it;

            --_it;
            position = (*_it)->GetPosition() + QPoint((*_it)->Bound().width(), 0);
        } else {
            position = QPoint((*it)->GetPosition().x(), (*it)->GetPosition().y() + heightDiff);
        }

        (*it)->SetPosition(position);
    }
}


int Composite::getMaxHeihgt()
{
    int maxHeight = 0;
    for(Content::const_iterator it = contents_.begin(); it != contents_.end(); ++it) {
        maxHeight = std::max(maxHeight, (*it)->Bound().height());
    }
    return maxHeight;
}

GlyphPtr Composite::Parent() throw()
{
	return parent_;
}


}
