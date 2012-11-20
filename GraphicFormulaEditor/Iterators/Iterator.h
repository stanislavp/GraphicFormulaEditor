#pragma once

#include "../GraphicSystem/Glyph.h"

namespace Iterator
{

using Graphic::GlyphPtr;

class Iterator
{

public:

	Iterator(GlyphPtr glyph) : node_(glyph) { }

	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsValid() = 0;

protected:
	GlyphPtr node_;
};

}
