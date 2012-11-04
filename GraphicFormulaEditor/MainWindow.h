#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! QT
#include <QGraphicsScene>

//! Boost
#include <boost/shared_ptr.hpp>

//! __Graphic
#include "GraphicSystem/Glyph.h"
#include "GraphicSystem/Variable.h"
#include "GraphicSystem/Row.h"
#include "GraphicSystem/Operation.h"
#include "GraphicSystem/Space.h"
#include "GraphicSystem/BracketsPair.h"
#include "GraphicSystem/Function.h"

//! STL
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void __try__();
	
private:
	//! SHARED PTR ЖЕ :) Нужно хранить!
	std::vector<Graphic::GlyphPtr> glyphs_;
	boost::shared_ptr<QGraphicsScene> scene_;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
