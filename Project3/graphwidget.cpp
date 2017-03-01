#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <QKeyEvent>
#include <QPointF>

//! [0]
GraphWidget::GraphWidget(vector<city> plottedCities, QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-400, -400, 800, 800);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    setMinimumSize(1000, 1000);
    setWindowTitle(tr("Traveling Salesman"));
//! [0]

//! [1]
    vector<Node> plottedNodes;
    Node* populateNode = new Node(this);
    int i;
                      ////////////////////////////////////////////////////////////////////////// initialize nodes
    for (i = 0; i < plottedCities.size(); i++) {
        populateNode->setPos(plottedCities[i].x, plottedCities[i].y);
        populateNode->id = plottedCities[i].id;
        plottedNodes.push_back(*populateNode);
        std::cout << "converted a city to a node\n";
    }

    Node *node1 = new Node(this);
    Node *node2 = new Node(this);
    Node *node3 = new Node(this);
    Node *node4 = new Node(this);
    Node *node5 = new Node(this);
    Node *node6 = new Node(this);
    Node *node7 = new Node(this);
    Node *node8 = new Node(this);
    Node *node9 = new Node(this);
    Node *node10 = new Node(this);
    Node *node11 = new Node(this);
    Node *node12 = new Node(this);
    Node *node13 = new Node(this);
    Node *node14 = new Node(this);
    Node *node15 = new Node(this);
    Node *node16 = new Node(this);
    Node *node17 = new Node(this);
    Node *node18 = new Node(this);
    Node *node19 = new Node(this);
    Node *node20 = new Node(this);
    Node *node21 = new Node(this);
    Node *node22 = new Node(this);
    Node *node23 = new Node(this);
    Node *node24 = new Node(this);
    Node *node25 = new Node(this);
    Node *node26 = new Node(this);
    Node *node27 = new Node(this);
    Node *node28 = new Node(this);
    Node* node29 = new Node(this);
    Node *node30 = new Node(this);
    node1->setPos(plottedCities[0].x, plottedCities[0].y);
    node2->setPos(plottedCities[1].x, plottedCities[1].y);
    node3->setPos(plottedCities[2].x, plottedCities[2].y);
    node4->setPos(plottedCities[3].x, plottedCities[3].y);
    node5->setPos(plottedCities[4].x, plottedCities[4].y);
    node6->setPos(plottedCities[5].x, plottedCities[5].y);
    node7->setPos(plottedCities[6].x, plottedCities[6].y);
    node8->setPos(plottedCities[7].x, plottedCities[7].y);
    node9->setPos(plottedCities[8].x, plottedCities[8].y);
    node10->setPos(plottedCities[9].x, plottedCities[9].y);
    node11->setPos(plottedCities[10].x, plottedCities[10].y);
    node12->setPos(plottedCities[11].x, plottedCities[11].y);
    node13->setPos(plottedCities[12].x, plottedCities[12].y);
    node14->setPos(plottedCities[13].x, plottedCities[13].y);
    node15->setPos(plottedCities[14].x, plottedCities[14].y);
    node16->setPos(plottedCities[15].x, plottedCities[15].y);
    node17->setPos(plottedCities[16].x, plottedCities[16].y);
    node18->setPos(plottedCities[17].x, plottedCities[17].y);
    node19->setPos(plottedCities[18].x, plottedCities[18].y);
    node20->setPos(plottedCities[19].x, plottedCities[19].y);
    node21->setPos(plottedCities[20].x, plottedCities[20].y);
    node22->setPos(plottedCities[21].x, plottedCities[21].y);
    node23->setPos(plottedCities[22].x, plottedCities[22].y);
    node24->setPos(plottedCities[23].x, plottedCities[23].y);
    node25->setPos(plottedCities[24].x, plottedCities[24].y);
    node26->setPos(plottedCities[25].x, plottedCities[25].y);
    node27->setPos(plottedCities[26].x, plottedCities[26].y);
    node28->setPos(plottedCities[27].x, plottedCities[27].y);
    node29->setPos(plottedCities[28].x, plottedCities[28].y);
    node30->setPos(plottedCities[29].x, plottedCities[29].y);
    //Node* test = new Node(this);
    //test->setPos(87.951292, 2.658162);
   // scene->addItem(test);

    for (i = 0; i < plottedNodes.size(); i++) {
        scene->addItem(&plottedNodes[i]);
        cout << "added city " << plottedNodes[i].id << " to the scene\n";
    }
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(node5);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
    scene->addItem(node10);
    scene->addItem(node11);
    scene->addItem(node12);
    scene->addItem(node13);
    scene->addItem(node14);
    scene->addItem(node15);
    scene->addItem(node16);
    scene->addItem(node17);
    scene->addItem(node18);
    scene->addItem(node19);
    scene->addItem(node20);
    scene->addItem(node21);
    scene->addItem(node22);
    scene->addItem(node23);
    scene->addItem(node24);
    scene->addItem(node25);
    scene->addItem(node26);
    scene->addItem(node27);
    scene->addItem(node28);
    scene->addItem(node29);
    scene->addItem(node30);
    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node3, node4));
    scene->addItem(new Edge(node4, node5));
    scene->addItem(new Edge(node5, node6));
    scene->addItem(new Edge(node6, node7));
    scene->addItem(new Edge(node7, node8));
    scene->addItem(new Edge(node8, node9));
    scene->addItem(new Edge(node9, node10));
    scene->addItem(new Edge(node10, node11));
    scene->addItem(new Edge(node11, node12));
    scene->addItem(new Edge(node12, node13));
    scene->addItem(new Edge(node13, node14));
    scene->addItem(new Edge(node14, node15));
    scene->addItem(new Edge(node15, node16));
    scene->addItem(new Edge(node16, node17));
    scene->addItem(new Edge(node17, node18));
    scene->addItem(new Edge(node18, node19));
    scene->addItem(new Edge(node19, node20));
    scene->addItem(new Edge(node20, node21));
    scene->addItem(new Edge(node21, node22));
    scene->addItem(new Edge(node22, node23));
    scene->addItem(new Edge(node23, node24));
    scene->addItem(new Edge(node24, node25));
    scene->addItem(new Edge(node25, node26));
    scene->addItem(new Edge(node26, node27));
    scene->addItem(new Edge(node27, node28));
    scene->addItem(new Edge(node28, node29));
    scene->addItem(new Edge(node29, node30));

    /*node1->setPos(-50, -50);    // set position here!
    node2->setPos(0, -50);
    node3->setPos(50, -50);
    node4->setPos(-50, 0);
    centerNode->setPos(0, 0);
    node6->setPos(50, 0);
    node7->setPos(-50, 50);
    node8->setPos(0, 50);
    node9->setPos(50, 50);*/
}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#ifndef QT_NO_WHEELEVENT
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Traveling Salesman Greedy "));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(8);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
