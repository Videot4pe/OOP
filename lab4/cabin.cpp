#include "cabin.h"
#include "errors.h"
#include <stdio.h>
#include "delay.h"
#include <QDebug>

cabin::cabin()
{
    st = CabinStateWaiting;
    nextState = CabinStateWaiting;
    floor = 1;

    connect(&door, SIGNAL(alreadyOpened()), this, SLOT(doorsOpened()));
    connect(&door, SIGNAL(alreadyClosed()), this, SLOT(doorsClosed()));

    connect(&door, SIGNAL(stateTextChanged(QString)), this, SIGNAL(doorsStateTextChanged(QString)));

    connect(this, SIGNAL(startOpening()), &door, SLOT(opening()));
    connect(this, SIGNAL(startClosing()), &door, SLOT(closing()));
}

void cabin::setState(CabinState state)
{
    st = state;

    QString stateText;

    switch (state) {
    case CabinStateGoingUp:
        stateText = "Едет вверх";
        break;
    case CabinStateGoingDown:
        stateText = "Едет вниз";
        break;
    case CabinStateWaiting:
        stateText = "Ожидает";
        break;
    case CabinStateOpening:
        stateText = "Открывается";
        break;
    case CabinStateClosing:
        stateText = "Закрывается";
        break;
    }

    qDebug() << "Кабина: " << stateText;

    emit stateTextChanged(stateText);
}

int cabin::currentFloor()
{
    return floor;
}

void cabin::updateState()
{
    setState(st);
    door.updateState();
}

void cabin::openDoors()
{
    nextState = CabinStateWaiting;
    setState(CabinStateWaiting);
    delay.delayAsync(1000, [=](void) {
        setState(CabinStateOpening);
        emit startOpening();
    });
}

void cabin::doorsOpened()
{
    setState(CabinStateWaiting);

    delay.delayAsync(2000, [=](void) {
        setState(CabinStateClosing);
        emit startClosing();
    });
}

void cabin::doorsClosed()
{
    setState(CabinStateWaiting);
    delay.delayAsync(500, [=](void) {
        setState(nextState);
            emit arrived();
    });
}

void cabin::moveUp()
{
    if (door.isOpen())
    {
        nextState = CabinStateGoingUp;
        setState(CabinStateClosing);
        emit startClosing();
        return;
    }
    delay.delayAsync(1000, [=](void) {
        setState(CabinStateGoingUp);

        delay.delayAsync(1000, [=](void) {
            floor++;

            emit arrived();
        });
    });
}

void cabin::moveDown()
{
    if (door.isOpen())
    {
        nextState = CabinStateGoingDown;
        setState(CabinStateClosing);
        emit startClosing();
        return;
    }

    delay.delayAsync(1000, [=](void) {
        setState(CabinStateGoingDown);

        delay.delayAsync(1000, [=](void) {
            floor--;

            emit arrived();
        });
    });
}
