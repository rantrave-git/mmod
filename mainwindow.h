#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewport.h"

#include <QWidget>
//#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private:
    void setupMatrix();
    void populateScene();

    //Viewport *viewport;
    QGraphicsScene *scene;
    QSplitter *menu_splitter;
};

#endif // MAINWINDOW_H
