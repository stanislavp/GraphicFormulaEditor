#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QObject(parent), selected_(0)
{
	//! GUI Initialization
	window_.reset(new QWidget);
	view_.reset(new QGraphicsView);

	scene_.reset(new GraphicsScene);
	selectedList_.reset(new QListWidget);

	delete_.reset(new QPushButton("Delete"));
	delete_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	add_.reset(new QPushButton("Add"));
	add_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	variable_.reset(new QPushButton("x"));
	variable_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	function_.reset(new QPushButton("f(x)"));
	function_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	fraction_.reset(new QPushButton("x / y"));
	fraction_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	leveled_.reset(new QPushButton("x^y"));
	leveled_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	radix_.reset(new QPushButton("sqrt(x)"));
	radix_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	hlayout_.reset(new QHBoxLayout);

	vlayout_.reset(new QVBoxLayout);
	buttonsLayout_.reset(new QHBoxLayout);

	hlayout_->addWidget(view_.get());
	hlayout_->addWidget(selectedList_.get());
	hlayout_->setStretch(0, 4);
	hlayout_->setStretch(1, 1);

	buttonsLayout_->addWidget(delete_.get());
	buttonsLayout_->addWidget(add_.get());
	buttonsLayout_->addWidget(variable_.get());
	buttonsLayout_->addWidget(function_.get());
	buttonsLayout_->addWidget(fraction_.get());
	buttonsLayout_->addWidget(leveled_.get());
	buttonsLayout_->addWidget(radix_.get());

	vlayout_->addLayout(buttonsLayout_.get());
	vlayout_->addLayout(hlayout_.get());

	window_->setLayout(vlayout_.get());

	mainGlyph_ = (new Graphic::Row());
	glyphs_.reset(new std::vector<Graphic::GlyphPtr>());

	//! Binding
	connect(scene_.get(), SIGNAL(clickOver(QPoint)), this, SLOT(FindGlyph(QPoint)));
	connect(selectedList_.get(), SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelected()));

	connect(add_.get(), SIGNAL(clicked()), this, SLOT(AddGlyph()));
	connect(delete_.get(), SIGNAL(clicked()), this, SLOT(DeleteGlyph()));
	connect(variable_.get(), SIGNAL(clicked()), this, SLOT(ClickVariable()));
	connect(function_.get(), SIGNAL(clicked()), this, SLOT(ClickFunction()));
	connect(fraction_.get(), SIGNAL(clicked()), this, SLOT(ClickFraction()));
	connect(leveled_.get(), SIGNAL(clicked()), this, SLOT(ClickLeveled()));
	connect(radix_.get(), SIGNAL(clicked()), this, SLOT(ClickRadix()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::Show()
{
	window_->show();
}

void MainWindow::AddGlyph()
{
	std::cerr << "Confirm. " << std::endl;

	/*
	    Здесь как-то надо слепить это дело с теми кнопками.
	    Запилить одну переменную смежную, в которую будем
	    создавать добавляемый глиф? И тут проверять было
	    ли все правильно выделено?
	*/
	/*
	if(selected_) {
	    // пихаем после выделенного глифа
	    Graphic::GlyphPtr glyph = selected_->GetGlyph();

	    if(glyph->Parent()) {
		Graphic::GlyphPtr parent = glyph->Parent();

		try {
		    size_t position = parent->GetPositionByPtr(glyph);
			adding(parent, , position + 1);
		} catch(std::logic_exception& e) {
		    std::cerr << e.what() << std::endl;
		}
	    }
	} else {
	    // пихаем в конец
		adding(mainGlyph_, , 0);
	}
	*/
}

void MainWindow::DeleteGlyph()
{
	if(selected_)
	{
		std::cerr << "Confirm." << std::endl;

		Graphic::GlyphPtr glyph = selected_->GetGlyph();

		if(glyph->Parent()) {
			Graphic::GlyphPtr parent = glyph->Parent();
			try {
				size_t position = parent->GetPositionByPtr(glyph);
				removing(parent, position);
				delete glyph;
				std::cerr << "Deleted." << std::endl;
			} catch(std::logic_error& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

}

void MainWindow::ClickVariable()
{

}

void MainWindow::ClickFunction()
{

}

void MainWindow::ClickFraction()
{

}

void MainWindow::ClickLeveled()
{

}

void MainWindow::ClickRadix()
{

}


void MainWindow::ChangeSelected()
{
	for(std::vector<Graphic::IteratorBacklightPtr>::const_iterator _it(backlights_.begin());
		_it != backlights_.end(); ++_it)
	{
		delete *_it;
	}

	backlights_.clear();

	QList<QListWidgetItem*> selected(selectedList_->selectedItems());

	if(!selected.empty())
	{
		std::map<QListWidgetItem*, Graphic::GlyphPtr>::const_iterator _find = selectedMap_.find(selected.front());

		if(_find != selectedMap_.end())
		{
			Graphic::GlyphPtr glyph = _find->second;

			Graphic::IteratorBacklightPtr iterator = new Graphic::IteratorBacklight(glyph);
			selected_ = iterator;
			backlights_.push_back(iterator);

			iterator->Draw(scene_.get());
		}
	}
}

void MainWindow::FindGlyph(QPoint point)
{
	Graphic::GlyphList list;

	if(mainGlyph_->Intersects(point, list))
	{
		selectedMap_.clear();
		selectedList_->clear();

		for(Graphic::GlyphList::const_iterator _it(list.begin()); _it != list.end(); ++_it)
		{
			QListWidgetItem *item = new QListWidgetItem(tr("Item"));
			selectedList_->addItem(item);

			selectedMap_[item] = *_it;
		}
	} else
	{
		selectedList_->clear();
		selectedMap_.clear();
		backlights_.clear();
	}
}

void MainWindow::__try2__()
{
	Iterator::GlyphIterator _it(mainGlyph_);
}

void MainWindow::__try__()
{
	using namespace Graphic;

	mainGlyph_->SetPosition(QPoint(100, 100));

	GlyphPtr function(new Function(QString("sin"), mainGlyph_));

	GlyphPtr var(new Variable(function));

	GlyphPtr oper(new Operation(function, QString("+")));

	GlyphPtr func2(new Function(QString("cos"), function));

	GlyphPtr var2(new Variable(func2, QString("x")));

	glyphs_->push_back(function);
	glyphs_->push_back(var);
	glyphs_->push_back(oper);
	glyphs_->push_back(func2);
	glyphs_->push_back(var2);

	adding(mainGlyph_, function, 0);
	adding(function, var, 0);
	adding(function, oper, 1);
	adding(function, func2, 2);
	adding(func2, var2, 0);

        mainGlyph_->Draw(scene_.get());

	view_->setScene(scene_.get());

}

void MainWindow::adding(Graphic::GlyphPtr where, Graphic::GlyphPtr what, size_t position)
{
    where->Add(what, position);
    mainGlyph_->SetPosition(mainGlyph_->GetPosition());
}

void MainWindow::removing(Graphic::GlyphPtr where, size_t position)
{
    where->Remove(position);
    mainGlyph_->SetPosition(mainGlyph_->GetPosition());
}
