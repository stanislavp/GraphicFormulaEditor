#include "../GlyphIterator.h"

//! Exception
#include "../../Exceptions/IsPlainGlyph.h"

namespace Iterator
{

GlyphIterator::GlyphIterator(GlyphPtr glyph) : Iterator(glyph), current_(0)
{

}

//! Операторы доступа

void GlyphIterator::First()
{
	current_ = 0;
}

void GlyphIterator::Next()
{
	++current_;
}

bool GlyphIterator::IsValid()
{
	try
	{
		node_->Get(current_);
	} catch(const Exception::IsPlainGlyph &error)
	{
		return false;
	} catch(const std::out_of_range &error)
	{
		return false;
	}

	return true;
}

GlyphPtr GlyphIterator::Get()
{
	GlyphPtr glyph;
	try
	{
		glyph = node_->Get(current_);
	} catch(const Exception::IsPlainGlyph &error)
	{
		return GlyphPtr();
	} catch(const std::out_of_range &error)
	{
		return GlyphPtr();
	}

	return glyph;
}


}
