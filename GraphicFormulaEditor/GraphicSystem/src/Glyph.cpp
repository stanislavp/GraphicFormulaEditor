#include "../Glyph.h"

namespace Graphic
{

Glyph::Glyph()
{

}

void Glyph::Add(GlyphPtr glyph, size_t position)
{
	//! Default implementation
}

void Glyph::Remove(size_t position)
{
	//! Default implementation
}

GlyphPtr Glyph::Parent() throw()
{
	//! Default implementation
	return GlyphPtr();
}


Glyph::~Glyph()
{

}

} // Graphic
