#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene_.reset(new QGraphicsScene());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::__try__()
{
	using namespace Graphic;

	GlyphPtr row(new Row());
	row->SetPosition(QPoint(100, 100));
	glyphs_.push_back(row);

	GlyphPtr variable(new Variable(GlyphPtr()));
	glyphs_.push_back(variable);

	GlyphPtr variable2(new Variable(GlyphPtr()));
	glyphs_.push_back(variable2);

	GlyphPtr operation(new Operation(GlyphPtr(), QString("+")));
	glyphs_.push_back(operation);

	GlyphPtr space(new Space());
	glyphs_.push_back(space);

	row->Add(variable, 10);
	row->Add(operation, 10);
	row->Add(space, 10);
	row->Add(variable2, 10);

	row->Draw(scene_);

	ui->FormulaView->setScene(scene_.get());

}
