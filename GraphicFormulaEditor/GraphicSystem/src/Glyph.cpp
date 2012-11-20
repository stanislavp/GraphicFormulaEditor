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

bool Glyph::Remove(size_t position)
{
	//! Default implementation
	 return false;
}

GlyphPtr Glyph::Parent() const throw()
{
	//! Default implementation
	return GlyphPtr();
}

size_t Glyph::GetPositionByPtr(GlyphPtr ptr) const
{
	 //! Default implementation
	 return 0;
}

QString Glyph::__Type()
{
	return QString("Glyph");
}


Glyph::~Glyph()
{

}

}
