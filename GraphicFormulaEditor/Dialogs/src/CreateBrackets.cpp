#include "../CreateBrackets.h"

namespace Dialog
{


CreateBrackets::CreateBrackets(Graphic::GlyphPtr glyphParent, MainWindow *parent)
	: QDialog(parent), parent_(glyphParent)
{
	hint_ = new QLabel(tr("Are you sure?"));
	ok_ = new QPushButton(tr("OK"));
	cancel_ = new QPushButton(tr("Cancel"));

	/**
	 * LAYOUTS
	 */

	//! Text layout
	hlayout_ = new QHBoxLayout();

	hlayout_->addWidget(hint_);

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
	connect(ok_, SIGNAL(clicked()), this, SLOT(Create()));

	connect(this, SIGNAL(CreateOver(Graphic::GlyphPtr)), parent, SLOT(Create(Graphic::GlyphPtr)));
}

void CreateBrackets::Create()
{
	emit CreateOver(new Graphic::BracketsPair(parent_));
	close();
}


}
