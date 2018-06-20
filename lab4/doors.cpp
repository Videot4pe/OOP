#include "doors.h"
#include "errors.h"
#include "delay.h"

#include <QDebug>


doors::doors()
{
    setState(DoorStateClosed);
    connect(this, SIGNAL(open()), this, SLOT(opened()));
    connect(this, SIGNAL(close()), this, SLOT(closed()));
}

bool doors::isOpen()
{
    return st == DoorStateOpen;
}

void doors::updateState()
{
    setState(st);
}

void doors::setState(DoorState state)
{
    st = state;

    QString stateText;

    switch (state) {
    case DoorStateOpen:
        stateText = "Открыты";
        break;
    case DoorStateClosed:
        stateText = "Закрыты";
        break;
    case DoorStateOpening:
        stateText = "Открываются";
        break;
    case DoorStateClosing:
        stateText = "Закрываются";
        break;
    }

    qDebug() << "Двери: " << stateText;

    emit stateTextChanged(stateText);
}

void doors::opening()
{
    if ((st == DoorStateOpen) || (st == DoorStateOpening) || (st == DoorStateClosing))
        return;

    setState(DoorStateOpening);
    delay.delayAsync(1000, [=](void) {
        emit open();
    });

}

void doors::closing()
{
    if ((st == DoorStateClosed) || (st == DoorStateClosing))
        return;

    setState(DoorStateClosing);
    delay.delayAsync(1000, [=](void) {
        emit close();
    });
}

void doors::opened()
{
        setState(DoorStateOpen);
        emit alreadyOpened();
}

void doors::closed()
{
        setState(DoorStateClosed);
        emit alreadyClosed();
}
