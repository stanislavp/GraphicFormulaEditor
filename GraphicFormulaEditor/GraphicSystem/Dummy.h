#pragma once

#include "Variable.h"

namespace Graphic
{

class Dummy;

typedef Dummy* DummyPtr;

class Dummy : public Variable
{
public:
	 Dummy(GlyphPtr parent = GlyphPtr());

	 virtual QString Type() const;

protected:
	static QString __Type();
};

}