#ifndef VIEWPORT
#define VIEWPORT

#include <QFrame>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class Viewport;

class GraphicsView : public QGraphicsView{
    Q_OBJECT
public:
    GraphicsView(Viewport *v) : QGraphicsView(), view(v) { }

protected:
//#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
//#endif

private:
    Viewport *view;
};

class ViewportMetaData{
public:
    ViewportMetaData() {}
    ViewportMetaData(const ViewportMetaData&) {}
};

class Viewport : public QFrame{
    Q_OBJECT
public:
    explicit Viewport(const ViewportMetaData& data, QWidget *parent = 0);
    QGraphicsView *view() const;
public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void toggleOpenGL();
    void toggleAntialiasing();
    void print();

private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *openGlButton;
    QToolButton *antialiasButton;
    QToolButton *printButton;
    QToolButton *resetButton;
    QSlider *zoomSlider;
};

#endif // VIEWPORT

