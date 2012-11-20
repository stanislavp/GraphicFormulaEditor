#pragma once

//! QT
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPoint>

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	GraphicsScene(QObject* parent = 0);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

signals:
	void clickOver(QPoint point);
};
