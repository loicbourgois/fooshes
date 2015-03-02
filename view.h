#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class Scene;
class MainWindow;

class View : public QGraphicsView
{
public:
    View(MainWindow *mainWindow);
    ~View();
private:
    void mousePressEvent ( QMouseEvent * event );
    void wheelEvent(QWheelEvent *event);
private:
    MainWindow * mainWindow;
};

#endif // VIEW_H
