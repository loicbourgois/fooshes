#include "view.h"

#include "scene.h"
#include <QDebug>
#include <QMouseEvent>
#include <main_window.h>

View::View(MainWindow * mainWindow)
    : QGraphicsView(/*new QGraphicsScene(), */mainWindow),
    mainWindow(mainWindow)
{
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scale(1, -1);
    setSceneRect(-2000, -2000, 4000, 4000);
    centerOn(0,0);
}

View::~View()
{

}

void View::mousePressEvent(QMouseEvent * event)
{
    if (event->modifiers() & Qt::ControlModifier)
        mainWindow->clickAt(mapToScene(event->pos()).x(), mapToScene(event->pos()).y(), Living::Type::FOOD);
    else
        mainWindow->clickAt(mapToScene(event->pos()).x(), mapToScene(event->pos()).y(), Living::Type::FOOSH);
}


void View::wheelEvent(QWheelEvent *event)
{
    //if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->delta() > 0)
            this->scale(2,2);
        else
            this->scale(0.5,0.5);
        event->accept();
    }
    //else
    {
        //QGraphicsView::wheelEvent(event);
    }
}
