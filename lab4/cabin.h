#ifndef cabin_H
#define cabin_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>
#include <QQueue>
#include <QLabel>

#include "doors.h"
#include "delay.h"


class cabin : public QObject
{
    Q_OBJECT
    enum CabinState
    {
        CabinStateGoingUp,
        CabinStateGoingDown,
        CabinStateWaiting,
        CabinStateOpening,
        CabinStateClosing
    };
public:
    cabin();
    int currentFloor();
    void updateState();

private:
    void setState(CabinState state);
    doors door;
    CabinState st;
    CabinState nextState;
    int floor;
    Delay delay;

public slots:
    void moveUp();
    void moveDown();
    void openDoors();
    void doorsOpened();
    void doorsClosed();

signals:
    void startOpening();
    void startClosing();
    void ready();
    void arrived();
    void stateTextChanged(QString stateText);
    void doorsStateTextChanged(QString stateText);
};

#endif // cabin_H
