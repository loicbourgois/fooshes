#include "view.hpp"

#include "scene.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <main_window.hpp>

View::View(MainWindow * mainWindow)
    : QGraphicsView(/*new QGraphicsScene(), */mainWindow),
      mainWindow(mainWindow)
{
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scale(1, -1);
    setSceneRect(-20000, -20000, 40000, 40000);
    centerOn(0,0);
}

View::~View()
{

}

void View::mousePressEvent(QMouseEvent * event)
{
    setDragMode(QGraphicsView::NoDrag);
    if (event->button() == Qt::MidButton )
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        QMouseEvent fake(event->type(), event->pos(), Qt::LeftButton, Qt::LeftButton, event->modifiers());
        QGraphicsView::mousePressEvent(&fake);
    }
    else
    {
        mainWindow->clickAt(mapToScene(event->pos()).x(), mapToScene(event->pos()).y(), Living::Type::FOOSH);
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    (void)event;
    setDragMode(QGraphicsView::NoDrag);
}


void View::wheelEvent(QWheelEvent *event)
{
    //if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->delta() > 0)
            scale(2,2);
        else
            scale(0.5,0.5);
        event->accept();
    }
    /*else
    {
        QGraphicsView::wheelEvent(event);
    }*/
}
