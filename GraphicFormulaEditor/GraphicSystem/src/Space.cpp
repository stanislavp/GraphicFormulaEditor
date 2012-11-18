#include "../Space.h"

namespace Graphic
{

Space::Space(GlyphPtr parent) : Variable(parent)
{
	SetText(QString(" "));
}

QString Space::__Type()
{
	return QString("space");
}

}
