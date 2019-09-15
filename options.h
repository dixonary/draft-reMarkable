#pragma once

#include <QObject>
#include <QQuickWindow>
#include <QQuickItem>
#include <stdlib.h>
#ifdef RM
#include <epframebuffer.h>
#endif

class OptionItem : public QObject {
    Q_OBJECT
public:

    Q_PROPERTY(QString name MEMBER _name NOTIFY nameChanged)
    Q_PROPERTY(QString desc MEMBER _desc NOTIFY descChanged)
    Q_PROPERTY(QString call MEMBER _call NOTIFY callChanged)
    Q_PROPERTY(QString term MEMBER _term NOTIFY termChanged)

    bool ok() {
        return ! (_name.isEmpty() && _call.isEmpty());
    }

    Q_INVOKABLE void update(QQuickWindow *w){
         w->contentItem()->update();

    }

    Q_INVOKABLE void execute(){
       system(_call.toUtf8());

#ifdef RM

        //EPFrameBuffer::setForceFull(true);
        //EPFrameBuffer::clearScreen();
        //EPFrameBuffer::sendUpdate(EPFrameBuffer::framebuffer()->rect(), EPFrameBuffer::Grayscale, EPFrameBuffer::FullUpdate, true);
#endif
    }
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

class Options
{
public:
    Options();
    QList<QObject*> GetOptions();
private:
    bool read_directory(const std::string name, std::vector<std::string>& files);
    void error(std::string text);
    void createOption(OptionItem &option, int index);

};
