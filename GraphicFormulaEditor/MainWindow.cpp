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
	buttonsLayout_->addWidget(add_.get());
	buttonsLayout_->addWidget(variable_.get());
	buttonsLayout_->addWidget(function_.get());
	buttonsLayout_->addWidget(fraction_.get());
	buttonsLayout_->addWidget(leveled_.get());
	buttonsLayout_->addWidget(radix_.get());
	buttonsLayout_->addWidget(operation_.get());

	vlayout_->addLayout(menuLayout_.get());
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
	connect(operation_.get(), SIGNAL(clicked()), this, SLOT(ClickOperation()));
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

	if(selected_)
	{
		// пихаем после выделенного глифа
		Graphic::GlyphPtr glyph = selected_->GetGlyph();

		if(glyph->Parent())
		{
			Graphic::GlyphPtr parent = glyph->Parent();

			try
			{
				 size_t position = parent->GetPositionByPtr(glyph);
				 adding(parent, new Graphic::Variable(parent, "pi"), position + 1);
				 mainGlyph_->Draw(scene_.get());
			} catch(const std::logic_error &e) {
				 std::cerr << e.what() << std::endl;
			}
		}
		delete selected_;
	} else
	{
		 // пихаем в конец
		adding(mainGlyph_, new Graphic::Variable(mainGlyph_, "pi") , 0);
		mainGlyph_->Draw(scene_.get());
	}

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
				if(removing(parent, position))
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
				 adding(parent, newGlyph, position + 1);
				 mainGlyph_->Draw(scene_.get());

				 FindGlyph(newGlyph->GetPosition());

			} catch(const std::logic_error &e)
			{
				 std::cerr << e.what() << std::endl;
			}
		}
	}
}

void MainWindow::ClickVariable()
{
	QDialog *create = new Dialog::CreateVariable(selected_->GetGlyph()->Parent(), this);
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

	 ClearSelected();
	 ClearSelectedBackLight();
}

bool MainWindow::removing(Graphic::GlyphPtr where, size_t position)
{
	bool deleted = where->Remove(position);
	mainGlyph_->SetPosition(mainGlyph_->GetPosition());

	ClearSelected();

	return deleted;
}

void MainWindow::ClearSelected()
{
	if(selectedList_)
		selectedList_->clear();
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
}

void MainWindow::CreateMenus()
{
	menuBar_.reset(new QMenuBar(this));
	menuBar_->setObjectName(tr("MenuBar"));
	this->setMenuBar(menuBar_.get());

	//! File
	fileMenu_.reset(menuBar_->addMenu(tr("&File")));
	fileMenu_->addAction(export_.get());
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
	}
}
