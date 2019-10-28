#pragma once

#include <QObject>
#include "option_item.h"

class Options : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QList<QObject*> getOptions();
    Q_INVOKABLE QString getVersion();
};
