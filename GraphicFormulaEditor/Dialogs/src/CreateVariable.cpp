#include "../CreateVariable.h"

namespace Dialog
{


CreateVariable::CreateVariable(Graphic::GlyphPtr &variable, Graphic::GlyphPtr glyphParent, QWidget *parent)
	: QDialog(parent), variable_(variable), parent_(glyphParent)
{
	text_ = new QLineEdit();
	hint_ = new QLabel(tr("Name/value: "));
	ok_ = new QPushButton(tr("OK"));
	cancel_ = new QPushButton(tr("Cancel"));

	/**
	 * LAYOUTS
	 */

	//! Text layout
	hlayout_ = new QHBoxLayout();

	hlayout_->addWidget(hint_);
	hlayout_->addWidget(text_);

	//! Button layout
	buttonLayout_ = new QHBoxLayout();

	buttonLayout_->addWidget(ok_);
	buttonLayout_->addWidget(cancel_);

	//! Main layout
	vlayout_ = new QVBoxLayout();

	vlayout_->addLayout(hlayout_);
	vlayout_->addLayout(buttonLayout_);

	setLayout(vlayout_);

	/**
	 * BINDING
	 */

	connect(cancel_, SIGNAL(clicked()), this, SLOT(close()));
	connect(ok_, SIGNAL(clicked()), this, SLOT(close()));
}

void CreateVariable::Create()
{
	QString text(text_->text());

	if(!text.isEmpty())
	{
		variable_ = new Graphic::Variable(parent_, text);
		close();
	}
}


}
