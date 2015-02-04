
#include "viewport.h"

#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <qmath.h>


void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            view->zoomIn(6);
        else
            view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

Viewport::Viewport(const ViewportMetaData &name, QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Plain | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);

    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    //QSize iconSize(size, size);

    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    //zoomSliderLayout->addWidget(zoomInIcon);
    zoomSliderLayout->addWidget(zoomSlider);
    //zoomSliderLayout->addWidget(zoomOutIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel("Some text...");
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);
    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);
    openGlButton = new QToolButton;
    openGlButton->setText(tr("OpenGL"));
    openGlButton->setCheckable(true);
#ifndef QT_NO_OPENGL
    openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
    openGlButton->setEnabled(false);
#endif
    printButton = new QToolButton;

    printButton->setText("Print");
    //printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

    QButtonGroup *pointerModeGroup = new QButtonGroup;
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);

    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addStretch();
    labelLayout->addWidget(antialiasButton);
    labelLayout->addWidget(openGlButton);
    labelLayout->addWidget(printButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addWidget(resetButton, 0, 1);
    setLayout(topLayout);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
    connect(openGlButton, SIGNAL(toggled(bool)), this, SLOT(toggleOpenGL()));
    connect(printButton, SIGNAL(clicked()), this, SLOT(print()));

    setupMatrix();
}


QGraphicsView *Viewport::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void Viewport::resetView()
{
    zoomSlider->setValue(250);
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void Viewport::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void Viewport::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);

    graphicsView->setMatrix(matrix);
    setResetButtonEnabled();
}

void Viewport::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void Viewport::toggleOpenGL()
{
#ifndef QT_NO_OPENGL
    graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void Viewport::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void Viewport::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
#endif
}

void Viewport::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void Viewport::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}


