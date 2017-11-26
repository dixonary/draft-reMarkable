#include "mainview.h"

MainView::MainView()
{

}

void MainView::keyPressEvent(QKeyEvent* ke)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "mw" << ke->key() << "down";
    QQuickView::keyPressEvent(ke); // base class implementation
}

void MainView::mouseMoveEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mouseMoveEvent(me);
}

void MainView::mousePressEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mousePressEvent(me);
}

void MainView::mouseReleaseEvent(QMouseEvent* me)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << me->pos();
    QQuickView::mouseReleaseEvent(me);
}

void MainView::tabletEvent(QTabletEvent* te)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << te;
}

void MainView::touchEvent(QTouchEvent* te)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << te;
}
