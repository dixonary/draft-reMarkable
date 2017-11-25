#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    void handleClick();

signals:

public slots:
};

#endif // BACKEND_H
