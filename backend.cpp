#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{

}

void Backend::handleClick()
{
    qDebug() << "click handler";
}
