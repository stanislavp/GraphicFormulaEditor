#include "MainWindow.h"

//! Dialogs
#include "Dialogs/CreateVariable.h"
#include "Dialogs/CreateFunction.h"
#include "Dialogs/CreateFraction.h"
#include "Dialogs/CreateOperation.h"
#include "Dialogs/CreateBrackets.h"
#include "Dialogs/CreateLeveled.h"

//! Qt
#include <QPixmap>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), selected_(0)
{
	//! GUI Initialization
	window_.reset(new QWidget);
	view_.reset(new QGraphicsView);

	scene_.reset(new GraphicsScene);
	selectedList_.reset(new QListWidget);

	delete_.reset(new QPushButton("Delete"));
	delete_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	create_.reset(new QPushButton("New"));
	create_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	brackets_.reset(new QPushButton("( )"));
	brackets_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	variable_.reset(new QPushButton("x"));
	variable_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	function_.reset(new QPushButton("f(x)"));
	function_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	fraction_.reset(new QPushButton("x / y"));
	fraction_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	leveled_.reset(new QPushButton("x^y"));
	leveled_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	radix_.reset(new QPushButton("sqrt()"));
	radix_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	operation_.reset(new QPushButton("*/-+"));
	operation_->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	menuLayout_.reset(new QHBoxLayout);
	hlayout_.reset(new QHBoxLayout);

	vlayout_.reset(new QVBoxLayout);
	buttonsLayout_.reset(new QHBoxLayout);

	//! Actions
	CreateActions();

	//! Menus
	CreateMenus();

	menuLayout_->addWidget(menuBar_.get());

	hlayout_->addWidget(view_.get());
	hlayout_->addWidget(selectedList_.get());
	hlayout_->setStretch(0, 4);
	hlayout_->setStretch(1, 1);

	buttonsLayout_->addWidget(delete_.get());
	buttonsLayout_->addWidget(create_.get());
	buttonsLayout_->addWidget(variable_.get());
	buttonsLayout_->addWidget(function_.get());
	buttonsLayout_->addWidget(fraction_.get());
	buttonsLayout_->addWidget(leveled_.get());
	buttonsLayout_->addWidget(radix_.get());
	buttonsLayout_->addWidget(operation_.get());
	buttonsLayout_->addWidget(brackets_.get());

	vlayout_->addLayout(menuLayout_.get());
	vlayout_->addLayout(buttonsLayout_.get());
	vlayout_->addLayout(hlayout_.get());

	window_->setLayout(vlayout_.get());

	mainGlyph_ = (new Graphic::Row());
	glyphs_.reset(new std::vector<Graphic::GlyphPtr>());

	//! Binding
	connect(scene_.get(), SIGNAL(clickOver(QPoint)), this, SLOT(FindGlyph(QPoint)));
	connect(selectedList_.get(), SIGNAL(itemSelectionChanged()), this, SLOT(ChangeSelected()));

	connect(create_.get(), SIGNAL(clicked()), this, SLOT(CreateNewFormula()));
	connect(delete_.get(), SIGNAL(clicked()), this, SLOT(DeleteGlyph()));
	connect(variable_.get(), SIGNAL(clicked()), this, SLOT(ClickVariable()));
	connect(function_.get(), SIGNAL(clicked()), this, SLOT(ClickFunction()));
	connect(fraction_.get(), SIGNAL(clicked()), this, SLOT(ClickFraction()));
	connect(leveled_.get(), SIGNAL(clicked()), this, SLOT(ClickLeveled()));
	connect(radix_.get(), SIGNAL(clicked()), this, SLOT(ClickRadix()));
	connect(operation_.get(), SIGNAL(clicked()), this, SLOT(ClickOperation()));
	connect(brackets_.get(), SIGNAL(clicked()), this, SLOT(ClickBrackets()));

	view_->setScene(scene_.get());
}

MainWindow::~MainWindow()
{

}

void MainWindow::Show()
{
	window_->show();
}

void MainWindow::CreateNewFormula()
{
	ClearSelected();
	ClearSelectedBackLight();
	CreateMainGlyph();
}

void MainWindow::CreateMainGlyph()
{
	delete mainGlyph_;

	mainGlyph_ = (new Graphic::Row());
	glyphs_.reset(new std::vector<Graphic::GlyphPtr>());

	mainGlyph_->Draw(scene_.get());
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
				if(Removing(parent, position))
					delete glyph;

				std::cerr << "Deleted." << std::endl;
			} catch(std::logic_error& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

}

void MainWindow::Create(Graphic::GlyphPtr newGlyph)
{
	if(selected_->GetGlyph() && newGlyph)
	{
		if(newGlyph->Parent())
		{
			Graphic::GlyphPtr parent = selected_->GetGlyph()->Parent();
			try
			{
				 size_t position = parent->GetPositionByPtr(selected_->GetGlyph());
				 Adding(parent, newGlyph, position + 1);
				 mainGlyph_->Draw(scene_.get());

				 FindGlyph(newGlyph->GetPosition());

			} catch(const std::logic_error &e)
			{
				 std::cerr << e.what() << std::endl;
			}
		}
	} else
		std::cerr << "MainWindow::Create(): !GetGlyph && newGlyph" << std::endl;
}

void MainWindow::ClickVariable()
{
	QDialog *create = new Dialog::CreateVariable(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}

void MainWindow::ClickBrackets()
{
	QDialog *create = new Dialog::CreateBrackets(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}

void MainWindow::ClickFunction()
{
	QDialog *create = new Dialog::CreateFunction(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}

void MainWindow::ClickFraction()
{
	QDialog *create = new Dialog::CreateFraction(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}

void MainWindow::ClickLeveled()
{
	QDialog *create = new Dialog::CreateLeveled(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}

void MainWindow::ClickRadix()
{
	if(selected_->GetGlyph())
	{
		Graphic::GlyphPtr glyph = new Graphic::Function("sqrt", selected_->GetGlyph()->Parent());
		Create(glyph);
	}
}

void MainWindow::ClickOperation()
{
	QDialog *create = new Dialog::CreateOperation(selected_->GetGlyph()->Parent(), this);
	create->setModal(true);
	create->show();
}


void MainWindow::ChangeSelected()
{
	ClearSelectedBackLight();

	QList<QListWidgetItem*> selected(selectedList_->selectedItems());

	if(!selected.empty())
	{
		std::map<QListWidgetItem*, Graphic::GlyphPtr>::const_iterator _find = selectedMap_.find(selected.front());

		if(_find != selectedMap_.end())
		{
			Graphic::GlyphPtr glyph = _find->second;

			Graphic::IteratorBacklightPtr iterator = new Graphic::IteratorBacklight(glyph);
			selected_ = iterator;

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
			QListWidgetItem *item = new QListWidgetItem((*_it)->Type());
			selectedList_->addItem(item);

			selectedMap_[item] = *_it;
		}

		//! Автовыделим первый глиф
		if(selectedList_->count())
		{
			selectedList_->item(0)->setSelected(true);
		}
	} else
	{
		selectedList_->clear();
		selectedMap_.clear();
	}
}

/**
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

	Adding(mainGlyph_, function, 0);
	Adding(function, var, 0);
	Adding(function, oper, 1);
	Adding(function, func2, 2);
	Adding(func2, var2, 0);

	mainGlyph_->Draw(scene_.get());
}
*/

void MainWindow::Adding(Graphic::GlyphPtr where, Graphic::GlyphPtr what, size_t position)
{
	 where->Add(what, position);
	 mainGlyph_->SetPosition(mainGlyph_->GetPosition());

	 ClearSelected();
	 ClearSelectedBackLight();
}

bool MainWindow::Removing(Graphic::GlyphPtr where, size_t position)
{
	bool deleted = where->Remove(position);
	mainGlyph_->SetPosition(mainGlyph_->GetPosition());

	ClearSelected();

	mainGlyph_->Draw(scene_.get());

	return deleted;
}

void MainWindow::ClearSelected()
{
	if(selectedList_)
		selectedList_->clear();

	selectedMap_.clear();
}

void MainWindow::ClearSelectedBackLight()
{
	delete selected_;
	selected_ = 0;
}

//! GUI

void MainWindow::CreateActions()
{
	//! Export as image
	export_.reset(new QAction(tr("&Export as image..."), this));
	export_->setShortcuts(QKeySequence::SaveAs);
	export_->setStatusTip(tr("Save formula as image file"));
	connect(export_.get(), SIGNAL(triggered()), this, SLOT(ExportAsImage()));

	//! Adding glyphs
	actionVariable_.reset(new QAction(tr("&Add variable"), this));
	actionVariable_->setShortcut(Qt::CTRL + Qt::Key_V);
	actionVariable_->setStatusTip(tr("Add variable after selected glyph"));
	connect(actionVariable_.get(), SIGNAL(triggered()), this, SLOT(ClickVariable()));

	actionFunction_.reset(new QAction(tr("&Add function"), this));
	actionFunction_->setShortcut(Qt::CTRL + Qt::Key_F);
	actionFunction_->setStatusTip(tr("Add function after selected glyph"));
	connect(actionFunction_.get(), SIGNAL(triggered()), this, SLOT(ClickFunction()));

	actionFraction_.reset(new QAction(tr("&Add fraction"), this));
	actionFraction_->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_F);
	actionFraction_->setStatusTip(tr("Add fraction after selected glyph"));
	connect(actionFraction_.get(), SIGNAL(triggered()), this, SLOT(ClickFraction()));

	actionLeveled_.reset(new QAction(tr("&Add leveled"), this));
	actionLeveled_->setShortcut(Qt::CTRL + Qt::Key_L);
	actionLeveled_->setStatusTip(tr("Add leveled after selected glyph"));
	connect(actionLeveled_.get(), SIGNAL(triggered()), this, SLOT(ClickLeveled()));

	actionRadix_.reset(new QAction(tr("&Add radix"), this));
	actionRadix_->setShortcut(Qt::CTRL + Qt::Key_R);
	actionRadix_->setStatusTip(tr("Add radix after selected glyph"));
	connect(actionRadix_.get(), SIGNAL(triggered()), this, SLOT(ClickRadix()));

	actionOperation_.reset(new QAction(tr("&Add operation"), this));
	actionOperation_->setShortcut(Qt::CTRL + Qt::Key_O);
	actionOperation_->setStatusTip(tr("Add operation after selected glyph"));
	connect(actionOperation_.get(), SIGNAL(triggered()), this, SLOT(ClickOperation()));

}

void MainWindow::CreateMenus()
{
	menuBar_.reset(new QMenuBar(this));
	menuBar_->setObjectName(tr("MenuBar"));
	this->setMenuBar(menuBar_.get());

	//! File
	fileMenu_.reset(menuBar_->addMenu(tr("&File")));
	fileMenu_->addAction(export_.get());

	//! Add
	addMenu_.reset(menuBar_->addMenu(tr("&Add")));
	addMenu_->addAction(actionVariable_.get());
	addMenu_->addAction(actionFunction_.get());
	addMenu_->addAction(actionFraction_.get());
	addMenu_->addAction(actionLeveled_.get());
	addMenu_->addAction(actionRadix_.get());
	addMenu_->addAction(actionOperation_.get());
}

//! Export

void MainWindow::ExportAsImage()
{
	QString fileName = QFileDialog::getSaveFileName(this,
													tr("Save Document"),
													QDir::currentPath(),
													tr("Images (*.png)"));

	if(!fileName.isNull())
	{
		QPixmap pixMap = QPixmap::grabWidget(view_.get());
		pixMap.save(fileName);
	} else
		std::cerr << "MainWindow::ExportAsImage(): bad file name. " << std::endl;
}
