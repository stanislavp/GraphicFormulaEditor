#pragma once

//! Qt
#include <QDialog>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

//! Graphics
#include "../GraphicSystem/Function.h"

//! Own
#include "../MainWindow.h"

namespace Dialog
{

class CreateFunction : public QDialog
{
	Q_OBJECT

public:
	CreateFunction(Graphic::GlyphPtr glyphParent, MainWindow *parent = 0);

signals:
	void CreateOver(Graphic::GlyphPtr glyph);

private slots:
	void Create();

private:
	Graphic::GlyphPtr parent_;

	QLineEdit *text_;
	QLabel *hint_;
	QPushButton *ok_;
	QPushButton *cancel_;

	QHBoxLayout *hlayout_;
	QHBoxLayout *buttonLayout_;
	QVBoxLayout *vlayout_;
};


}
