#pragma once

//! Own
#include "Variable.h"
#include "IteratorBacklight.h"

namespace Graphic
{

class Dummy;

typedef Dummy* DummyPtr;

class Dummy : public Variable
{
public:
	 Dummy(GlyphPtr parent = GlyphPtr());

	 virtual void Draw(QGraphicsScenePtr scene);

	 virtual QString Type() const;

	 ~Dummy();

protected:
	static QString __Type();

private:
	IteratorBacklightPtr backlight_;
};

}
