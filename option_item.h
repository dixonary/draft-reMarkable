#ifndef OPTION_ITEM_H
#define OPTION_ITEM_H
#include <QObject>

class OptionItem : public QObject {
    Q_OBJECT
public:

    Q_PROPERTY(QString name MEMBER _name NOTIFY nameChanged)
    Q_PROPERTY(QString desc MEMBER _desc NOTIFY descChanged)
    Q_PROPERTY(QString call MEMBER _call NOTIFY callChanged)
    Q_PROPERTY(QString term MEMBER _term NOTIFY termChanged)

    bool ok();

    Q_INVOKABLE void execute();
signals:
    void nameChanged();
    void descChanged();
    void callChanged();
    void termChanged();

private:
    QString _name;
    QString _desc;
    QString _call;
    QString _term;
};

#endif // OPTION_ITEM_H
