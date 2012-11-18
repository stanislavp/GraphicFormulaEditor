#include "../Dummy.h"

namespace Graphic
{

Dummy::Dummy(GlyphPtr parent)
	: Variable(parent), backlight_(0)
{
	 SetText(" ");
	 backlight_ = new IteratorBacklight(this);
	 backlight_->SetBrush(QBrush(QColor(255, 0, 0, 50)));
}

QString Dummy::__Type()
{
	return QString("Dummy");
}

QString Dummy::Type() const
{
	return __Type();
}

void Dummy::Draw(QGraphicsScenePtr scene)
{
	if(scene)
	{
		Variable::Draw(scene);
		backlight_->Draw(scene);
	}
}

Dummy::~Dummy()
{
	delete backlight_;
}

}
