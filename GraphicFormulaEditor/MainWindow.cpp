#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QObject(parent)
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

	connect(delete_.get(), SIGNAL(clicked()), this, SLOT(AddGlyph()));
	connect(add_.get(), SIGNAL(clicked()), this, SLOT(DeleteGlyph()));
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
}

void MainWindow::DeleteGlyph()
{
	std::cerr << "Confirm. " << std::endl;
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

}

void MainWindow::__try__()
{
	using namespace Graphic;

	mainGlyph_->SetPosition(QPoint(100, 100));

        GlyphPtr leveled(new LeveledExpression(mainGlyph_));
	glyphs_->push_back(leveled);

	GlyphPtr variable(new Variable(GlyphPtr(), QString("s")));
	glyphs_->push_back(variable);
        //leveled->Add(variable, (1 << 15) + 1);
        adding(leveled, variable, (1 << 15) + 1);

	GlyphPtr variable2(new Variable(GlyphPtr(), QString("m")));
	glyphs_->push_back(variable2);
        //leveled->Add(variable2, 0);
        adding(leveled, variable2, 0);

	GlyphPtr space(new Space());
	glyphs_->push_back(space);

	GlyphPtr brackets(new BracketsPair());
	glyphs_->push_back(brackets);

	GlyphPtr variable3(new Variable());
	glyphs_->push_back(variable3);

	GlyphPtr operation1(new Operation(GlyphPtr(), QString("+")));
	glyphs_->push_back(operation1);

	GlyphPtr operation2(new Operation(GlyphPtr(), QString("*")));
	glyphs_->push_back(operation2);

	GlyphPtr variable4(new Variable());
	glyphs_->push_back(variable4);

        // функция
	GlyphPtr func1(new Function(QString("sin")));
	glyphs_->push_back(func1);

        // аргумент функции func1
	GlyphPtr arg1(new Variable(GlyphPtr(), QString("x")));
	glyphs_->push_back(arg1);

        // дробь
        GlyphPtr frac1(new Fraction(mainGlyph_));
        glyphs_->push_back(frac1);

        // числитель frac1
        GlyphPtr variable5(new Variable(GlyphPtr(), QString("z")));
        glyphs_->push_back(variable5);

        // знаменатель frac1
        GlyphPtr variable6(new Variable(GlyphPtr(), QString("t")));
        glyphs_->push_back(variable6);

        // операция в числителе frac1
        GlyphPtr operation3(GlyphPtr(new Operation(GlyphPtr(), QString("+"))));

        //mainGlyph_->Add(leveled, 10);
        //mainGlyph_->Add(space, 10);
        //mainGlyph_->Add(operation2, 10);
        //mainGlyph_->Add(brackets, 10);

        adding(mainGlyph_, leveled, 10);
        adding(mainGlyph_, space, 10);
        adding(mainGlyph_, operation2, 10);
        adding(mainGlyph_, brackets, 10);

        //brackets->Add(variable3, 10);
        //brackets->Add(operation1, 10);
        //brackets->Add(variable4, 10);

        adding(brackets, variable3, 10);
        adding(brackets, operation1, 10);
        adding(brackets, variable4, 10);

        //frac1->Add(variable5, (1 << 15));
        //frac1->Add(variable6, 0);
        //frac1->Add(operation3, (1 << 15) + 1);
        //frac1->Add(func1, (1 << 15) + 2);

        adding(frac1, variable5, (1 << 15));
        adding(frac1, variable6, 0);
        adding(frac1, operation3, (1 << 15) + 1);
        adding(frac1, func1, (1 << 15) + 2);

        //func1->Add(arg1, 15);

        adding(func1, arg1, 15);

        GlyphPtr frac2(new Fraction());
        glyphs_->push_back(frac2);

        //frac2->Add(new Variable(frac2), 1 << 15);
        //frac2->Add(new Variable(frac2), 0);

        adding(frac2, new Variable(frac2), 0);

        //frac1->Add(new Operation(frac1, QString("+")), 1);
        //frac1->Add(frac2, 2);

        adding(frac1, new Operation(frac1, QString("+")), 1);
        adding(frac1, frac2, 2);

        //mainGlyph_->Add(frac1, 15);
        adding(mainGlyph_, frac1, 15);

        adding(frac1, new Operation(frac1, QString("*")), (1 << 15) + 3);

        GlyphPtr frac3(new Fraction(frac2));

        adding(frac3, new Variable(frac2), 1 << 15);
        adding(frac3, new Variable(frac2), 0);
        adding(frac2, frac3, 1 << 15);

	removing(mainGlyph_, 1);

	removing(mainGlyph_, 0);

	adding(mainGlyph_, leveled, 0);

	removing(brackets, 2);

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
