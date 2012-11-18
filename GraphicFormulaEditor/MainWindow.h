#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <QListWidget>
#include <QListWidgetItem>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGraphicsView>
#include <QPushButton>

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

//! Iterator
#include "Iterators/GlyphIterator.h"

//! STL
#include <vector>
#include <map>
#include <stdexcept>

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

class MainWindow : public QWidget // : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void Show();

	void __try__();
	void __try2__();

public slots:
	void FindGlyph(QPoint point);
	void ChangeSelected();

	void AddGlyph();
	void DeleteGlyph();
	void ClickVariable();
	void ClickFunction();
	void ClickFraction();
	void ClickLeveled();
	void ClickRadix();

	//! Create
	void Create(Graphic::GlyphPtr newGlyph);
	
private:

	// Добавление к глифу потомка

        void adding(Graphic::GlyphPtr where, Graphic::GlyphPtr what, size_t position);

	// Удаление по позиции

	void removing(Graphic::GlyphPtr where, size_t position);

	//! SHARED PTR ЖЕ :) Нужно хранить!
	boost::shared_ptr<std::vector<Graphic::GlyphPtr> > glyphs_;

	//! Row
	Graphic::GlyphPtr mainGlyph_;

	//! Текущий выделенный
	Graphic::IteratorBacklightPtr selected_;

	//! Для выбранных глифоф
	std::map<QListWidgetItem*, Graphic::GlyphPtr> selectedMap_;

	//! Для теста.
	std::vector<Graphic::IteratorBacklightPtr> backlights_;

	//! GUI
	boost::shared_ptr<QWidget> window_;
	boost::shared_ptr<QGraphicsView> view_;
	boost::shared_ptr<GraphicsScene> scene_;
	boost::shared_ptr<QListWidget> selectedList_;

	boost::shared_ptr<QPushButton> delete_;
	boost::shared_ptr<QPushButton> add_;
	boost::shared_ptr<QPushButton> variable_;
	boost::shared_ptr<QPushButton> function_;
	boost::shared_ptr<QPushButton> fraction_;
	boost::shared_ptr<QPushButton> leveled_;
	boost::shared_ptr<QPushButton> radix_;

	boost::shared_ptr<QHBoxLayout> hlayout_;
	boost::shared_ptr<QHBoxLayout> buttonsLayout_;
	boost::shared_ptr<QVBoxLayout> vlayout_;
};

#endif // MAINWINDOW_H
