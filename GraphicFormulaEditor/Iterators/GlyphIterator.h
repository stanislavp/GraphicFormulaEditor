#pragma once

//! Own
#include "Iterator.h"

namespace Iterator
{
class GlyphIterator : public Iterator
{

public:

	GlyphIterator(GlyphPtr glyph);

	//! Операторы доступа

	virtual void First();
	virtual void Next();
	virtual bool IsValid();
	virtual GlyphPtr Get();
private:
	unsigned current_;
};
}
