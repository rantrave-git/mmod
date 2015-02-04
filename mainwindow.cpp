#include "mainwindow.h"
#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    populateScene();

    menu_splitter = new QSplitter;

    menu_splitter->setOrientation(Qt::Vertical);
    //QSplitter *vSplitter = new QSplitter;
    //vSplitter->setOrientation(Qt::Vertical);
    //vSplitter->addWidget(menu_splitter);

    Viewport *view = new Viewport(ViewportMetaData());
    view->view()->setScene(scene);
    menu_splitter->addWidget(view);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(menu_splitter);
    setLayout(layout);

    setWindowTitle(tr("MMod"));
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;


}
