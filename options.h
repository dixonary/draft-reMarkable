#pragma once

#include <QObject>
#include "option_item.h"

class Options : public QObject
{
    Q_OBJECT

public:
    explicit Options(QObject *parent = 0):QObject(parent){}
    QList<QObject*> GetOptions();
    Q_INVOKABLE QString getVersion();
};
