#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene_.reset(new GraphicsScene());
	mainGlyph_.reset(new Graphic::Row());
	glyphs_.reset(new std::vector<Graphic::GlyphPtr>());

	connect(scene_.get(), SIGNAL(clickOver(QPoint)), this, SLOT(FindGlyph(QPoint)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::FindGlyph(QPoint point)
{
	//! Find
	std::cerr << "Confirm" << std::endl;
	Graphic::GlyphPtr glyph = mainGlyph_->Intersects(point);

        std::cerr << (size_t)(&*glyph) << std::endl;
	if(glyph)
	{
		Graphic::IteratorBacklightPtr ib(new Graphic::IteratorBacklight(glyph));
		backlights_.push_back(ib);
		ib->Draw(scene_);
	}
}

void MainWindow::__try2__()
{
//	scene_->clear();
//	mainGlyph_->Draw(scene_);
}

void MainWindow::__try__()
{
	using namespace Graphic;

	mainGlyph_->SetPosition(QPoint(100, 100));

	GlyphPtr variable(new Variable(GlyphPtr()));
	glyphs_->push_back(variable);

	GlyphPtr variable2(new Variable(GlyphPtr()));
	glyphs_->push_back(variable2);

	GlyphPtr operation(new Operation(GlyphPtr(), QString("+")));
	glyphs_->push_back(operation);

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

        mainGlyph_->Add(variable, 10);
	mainGlyph_->Add(operation, 10);
	mainGlyph_->Add(space, 10);
	mainGlyph_->Add(variable2, 10);
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

	mainGlyph_->Draw(scene_);

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

}
