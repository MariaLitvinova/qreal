#include "umlPortHandler.h"
#include "nodeElement.h"

<<<<<<< HEAD
UmlPortHandler::UmlPortHandler(NodeElement *node) : mNode(node), mBelongsToHorizontalBorders(true)
=======
UmlPortHandler::UmlPortHandler(NodeElement * const node)
	: mNode(node), mBelongsToHorizontalBorders(true)
>>>>>>> 87a7862b9757ea165e888c4de23fdb8495ebdb3b
{
}

void UmlPortHandler::handleMoveEvent(bool const leftPressed, QPointF &pos, QPointF const scenePos
		, NodeElement *&parentNode)
{
	if (!mNode)
		return;

<<<<<<< HEAD
	if (leftPressed) {
		if (pos == QPointF(0,0))
			pos = mNode->pos();
		QGraphicsItem* item = NULL;
		QGraphicsScene* sc = mNode->scene();
		item = sc->items(scenePos).value(1);
		NodeElement* actionItem = dynamic_cast<NodeElement*>(item);
		QPointF posInItem = QPointF(0,0);
		if (actionItem && ((actionItem == parentNode) || (!parentNode))) {
			if (actionItem->canHavePorts()) {
				posInItem = actionItem->mapFromScene(scenePos);
				QList<double> list = actionItem->borderValues();
				double xHor = list[0];
				double yHor = list[1];
				double xVert = list[2];
				double yVert = list[3];
=======
	QGraphicsItem* const item = mNode->scene()->items(scenePos).value(1);
	NodeElement* const actionItem = dynamic_cast<NodeElement * const>(item);
	BorderChecker const actionItemBorderChecker(actionItem);
	QPointF posInItem = QPointF(0, 0);
	if (actionItem && ((actionItem == parentNode) || (!parentNode))) {
		if (actionItem->canHavePorts()) {
			posInItem = actionItem->mapFromScene(scenePos);
>>>>>>> 87a7862b9757ea165e888c4de23fdb8495ebdb3b

				if (actionItem->checkLowerBorder(posInItem, xHor, yHor)
					|| actionItem->checkUpperBorder(posInItem, xHor, yHor)
					|| actionItem->checkRightBorder(posInItem, xVert, yVert)
					|| actionItem->checkLeftBorder(posInItem, xVert, yVert))
				{
					mNode->setParentItem(actionItem);
					parentNode = actionItem;
					pos = mNode->pos();
					mBelongsToHorizontalBorders = (actionItem->checkLowerBorder(posInItem, xHor, yHor)
							|| actionItem->checkUpperBorder(posInItem, xHor, yHor));
				}
				else
					handleHorizontalBorders(actionItem, parentNode, pos, posInItem);
			}
		}
		else
		{
			if ((parentNode) && (parentNode->canHavePorts()))
			{
				mNode->setPos(pos);
				if (parentNode)
				{
					posInItem = parentNode->mapFromScene(scenePos);
					handleHorizontalBorders(parentNode, parentNode, pos, posInItem);
				}
			}
		}
	}
}

<<<<<<< HEAD
void UmlPortHandler::handleHorizontalBorders(NodeElement *tmpNode, NodeElement *parentNode, QPointF &pos, QPointF &posInItem) const
{
	QList<double> list = tmpNode->borderValues();

	double xHor = list[0];
	double yHor = list[1];
	double xVert = list[2];
	double yVert = list[3];
	if (mBelongsToHorizontalBorders)
	{
		if (parentNode->checkNoBorderY(posInItem, xHor, yHor))
			pos = QPointF(posInItem.x(), pos.y());
	}
	else
	{
		if (parentNode->checkNoBorderX(posInItem, xVert, yVert))
			pos = QPointF(pos.x(), posInItem.y());
=======
void UmlPortHandler::handleHorizontalBorders(
		const NodeElement * const tmpNode, const NodeElement * const parentNode
		, QPointF const &pos, QPointF const &posInItem) const
{
	QPointF newPos = pos;
	BorderChecker const parentNodeBorderChecker(parentNode);
	if (mBelongsToHorizontalBorders) {
		// tmpNode->borderValues()[0] == xHor of tmpNode. (mXHor field of BorderChecker(tmpNode))
		if (parentNodeBorderChecker.checkNoBorderY(posInItem, tmpNode->borderValues()[0])) {
			newPos.setX(posInItem.x());
		}
	} else {
		// tmpNode->borderValues()[3] == yVert of tmpNode. (mYVert field of BorderChecker(tmpNode))
		if (parentNodeBorderChecker.checkNoBorderX(posInItem, tmpNode->borderValues()[3])) {
			newPos.setY(posInItem.y());
		}
>>>>>>> 87a7862b9757ea165e888c4de23fdb8495ebdb3b
	}
	mNode->setPos(pos);
}
