#pragma once

//! Own
#include "Variable.h"

namespace Graphic
{

class Space : public Variable
{
public:
	Space(GlyphPtr parent = GlyphPtr());

	virtual QString Type() const;

protected:
	static QString __Type();

};

}
