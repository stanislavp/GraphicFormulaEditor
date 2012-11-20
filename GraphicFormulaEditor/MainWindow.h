#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

//! Own
#include "GraphicScene.h"

//! QT
#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGraphicsView>
#include <QPushButton>

#include <QAction>
#include <QMenu>
#include <QMenuBar>

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

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void Show();

	void __try2__();

public slots:
	void FindGlyph(QPoint point);
	void ChangeSelected();

	void CreateNewFormula();
	void DeleteGlyph();
	void ClickVariable();
	void ClickFunction();
	void ClickFraction();
	void ClickLeveled();
	void ClickRadix();
	void ClickOperation();
	void ClickBrackets();

	//! Create
	void Create(Graphic::GlyphPtr newGlyph);
	
private:

	//! Добавление к глифу потомка
	void Adding(Graphic::GlyphPtr where, Graphic::GlyphPtr what, size_t position);

	//! Удаление по позиции
	bool Removing(Graphic::GlyphPtr where, size_t position);

	//! Utils
	void ClearSelected();
	void ClearSelectedBackLight();

	bool CheckSelected() const;
	bool CheckGlyph(Graphic::GlyphPtr glyph) const;

	//! GUI Initialize
	void CreateActions();
	void CreateMenus();

private slots:

	//! Export
	void ExportAsImage();

	//! Engine
	void CreateMainGlyph();

private:

	//! Row
	Graphic::GlyphPtr mainGlyph_;

	//! Текущий выделенный
	Graphic::IteratorBacklightPtr selected_;

	//! Для выбранных глифоф
	std::map<QListWidgetItem*, Graphic::GlyphPtr> selectedMap_;

	/**  GUI */

	//! Widgets
	boost::shared_ptr<QWidget> window_;
	boost::shared_ptr<QGraphicsView> view_;
	boost::shared_ptr<GraphicsScene> scene_;
	boost::shared_ptr<QListWidget> selectedList_;

	//! Buttons
	boost::shared_ptr<QPushButton> delete_;
	boost::shared_ptr<QPushButton> create_;
	boost::shared_ptr<QPushButton> brackets_;
	boost::shared_ptr<QPushButton> variable_;
	boost::shared_ptr<QPushButton> function_;
	boost::shared_ptr<QPushButton> fraction_;
	boost::shared_ptr<QPushButton> leveled_;
	boost::shared_ptr<QPushButton> radix_;
	boost::shared_ptr<QPushButton> operation_;

	//! Layouts
	boost::shared_ptr<QHBoxLayout> menuLayout_;
	boost::shared_ptr<QHBoxLayout> hlayout_;
	boost::shared_ptr<QHBoxLayout> buttonsLayout_;
	boost::shared_ptr<QVBoxLayout> vlayout_;

	//! Menu bars
	boost::shared_ptr<QMenuBar> menuBar_;

	//! Menus
	boost::shared_ptr<QMenu> fileMenu_;

	boost::shared_ptr<QMenu> addMenu_;

	//! Actions
	boost::shared_ptr<QAction> export_;

	boost::shared_ptr<QAction> actionVariable_;
	boost::shared_ptr<QAction> actionFunction_;
	boost::shared_ptr<QAction> actionFraction_;
	boost::shared_ptr<QAction> actionLeveled_;
	boost::shared_ptr<QAction> actionRadix_;
	boost::shared_ptr<QAction> actionOperation_;
};

#endif // MAINWINDOW_H
