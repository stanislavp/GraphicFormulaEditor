#include "../Dummy.h"

namespace Graphic
{

Dummy::Dummy(GlyphPtr parent): Variable(parent)
{
	 SetText(" ");
}

QString Dummy::__Type()
{
	return QString("dummy");
}

}
