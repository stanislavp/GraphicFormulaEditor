#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QListWidget>
#include <QListWidgetItem>

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
#include "GraphicSystem/Level.h"
#include "GraphicSystem/IteratorBacklight.h"

//! STL
#include <vector>
#include <map>

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
	void __try2__();

public slots:
	void FindGlyph(QPoint point);
	void ChangeSelected();
	
private:

        // Куда запилить не знал, пихнул сюда для проверки как обновляются позиции.
        // Примерно так и должно быть. Как правильно указывать глифу родителя можно подумать.
        // Хз как ты там ищешь, может оттуда сможешь.
        // Можно прямо из функици добавления указывать как вариант.

        void adding(Graphic::GlyphPtr where, Graphic::GlyphPtr what, size_t position);

	//! SHARED PTR ЖЕ :) Нужно хранить!
	boost::shared_ptr<std::vector<Graphic::GlyphPtr> > glyphs_;

	//! Row
	Graphic::GlyphPtr mainGlyph_;

	//! Для выбранных глифоф
	std::map<QListWidgetItem*, Graphic::GlyphPtr> selectedMap_;

	//! Для теста.
	std::vector<Graphic::IteratorBacklightPtr> backlights_;

	boost::shared_ptr<GraphicsScene> scene_;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
