#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

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
#include "GraphicSystem/Fraction.h"
#include "GraphicSystem/IteratorBacklight.h"

//! STL
#include <vector>

//! TEMP
#include <iostream>

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	GraphicsScene(QObject* parent = 0) : QGraphicsScene(parent)
	{

	}
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		QPoint position = event->scenePos().toPoint();
		std::cerr << "X: " << position.x();
		std::cerr << " Y: " << position.y();
		std::cerr << std::endl;

		emit clickOver(position);
	}

signals:
	void clickOver(QPoint point);
};

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

public slots:
	void FindGlyph(QPoint point);
	
private:
	//! SHARED PTR ЖЕ :) Нужно хранить!
	std::vector<Graphic::GlyphPtr> glyphs_;

	//! Row
	Graphic::GlyphPtr mainGlyph_;

	//! Для теста.
	std::vector<Graphic::IteratorBacklightPtr> backlights_;

	boost::shared_ptr<GraphicsScene> scene_;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
