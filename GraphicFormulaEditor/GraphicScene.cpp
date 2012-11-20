#include "GraphicScene.h"

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QPoint position = event->scenePos().toPoint();

	emit clickOver(position);
}

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent)
{

}
