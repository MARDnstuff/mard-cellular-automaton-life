#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include <QDebug>
#include <iostream>


class GameThread : public QThread{

    Q_OBJECT

public:

    GameThread(QObject *parent = nullptr);

    ~GameThread();

    void setAbort(bool opc);

protected:
    void run() override;

signals:
    void done();


private:

    QMutex mutex; //similar to syncronized of java
    QWaitCondition condition;
    bool abort = false;
    bool restart = false;




};

#endif // GAMETHREAD_H
