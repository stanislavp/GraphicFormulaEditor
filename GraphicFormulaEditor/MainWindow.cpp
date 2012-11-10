#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene_.reset(new GraphicsScene());
	mainGlyph_ = (new Graphic::Row());
	glyphs_.reset(new std::vector<Graphic::GlyphPtr>());

	connect(scene_.get(), SIGNAL(clickOver(QPoint)), this, SLOT(FindGlyph(QPoint)));
	connect(ui->selectedList, SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelected()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::ChangeSelected()
{
	for(std::vector<Graphic::IteratorBacklightPtr>::const_iterator _it(backlights_.begin());
		_it != backlights_.end(); ++_it)
	{
		delete *_it;
	}

	backlights_.clear();

	QList<QListWidgetItem*> selected(ui->selectedList->selectedItems());

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
		ui->selectedList->clear();

		for(Graphic::GlyphList::const_iterator _it(list.begin()); _it != list.end(); ++_it)
		{
			QListWidgetItem *item = new QListWidgetItem(tr("Item"));
			ui->selectedList->addItem(item);

			selectedMap_[item] = *_it;
		}
	} else
	{
		ui->selectedList->clear();
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

	GlyphPtr leveled(new LeveledExpression());
	glyphs_->push_back(leveled);

	GlyphPtr variable(new Variable(GlyphPtr(), QString("s")));
	glyphs_->push_back(variable);
	leveled->Add(variable, (1 << 15) + 1);

	GlyphPtr variable2(new Variable(GlyphPtr(), QString("m")));
	glyphs_->push_back(variable2);
	leveled->Add(variable2, 0);

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
        GlyphPtr frac1(new Fraction());
        glyphs_->push_back(frac1);

        // числитель frac1
        GlyphPtr variable5(new Variable(GlyphPtr(), QString("z")));
        glyphs_->push_back(variable5);

        // знаменатель frac1
        GlyphPtr variable6(new Variable(GlyphPtr(), QString("t")));
        glyphs_->push_back(variable6);

        // операция в числителе frac1
        GlyphPtr operation3(GlyphPtr(new Operation(GlyphPtr(), QString("+"))));

	mainGlyph_->Add(leveled, 10);
	mainGlyph_->Add(space, 10);
	mainGlyph_->Add(operation2, 10);
	mainGlyph_->Add(brackets, 10);

	brackets->Add(variable3, 10);
	brackets->Add(operation1, 10);
	brackets->Add(variable4, 10);

        mainGlyph_->Add(frac1, 15);

        frac1->Add(variable5, (1 << 15));
        frac1->Add(variable6, 0);
        frac1->Add(operation3, (1 << 15) + 1);
        frac1->Add(func1, (1 << 15) + 2);

        func1->Add(arg1, 15);

		mainGlyph_->Draw(scene_.get());

	/**
	 * IteratorBacklight TEST
	 */

	//Graphic::IteratorBacklightPtr _ib(new IteratorBacklight(frac1));
	//backlights_.push_back(_ib);
	//_ib->SetGlyph(func1);

	//_ib->Draw(scene_);

	/**
	*/

	ui->FormulaView->setScene(scene_.get());

//	FindGlyph(QPoint(185, 110));

}
