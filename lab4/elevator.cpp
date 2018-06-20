#include "elevator.h"
#include "errors.h"
#include <stdio.h>
#include "delay.h"
#include <QDebug>


elevator::elevator()
{
    setState(ElevatorStateFree);

    connect(&cab, SIGNAL(arrived()), this, SLOT(cabinArrived()));
    //connect(&cab, SIGNAL(ready()), this, SLOT(cabinReady()));
    connect(this, SIGNAL(moveUp()), &cab, SLOT(moveUp()));
    connect(this, SIGNAL(moveDown()), &cab, SLOT(moveDown()));
    connect(this, SIGNAL(openDoors()), &cab, SLOT(openDoors()));

    connect(&cab, SIGNAL(stateTextChanged(QString)), this, SIGNAL(cabinStateTextChanged(QString)));
    connect(&cab, SIGNAL(doorsStateTextChanged(QString)), this, SIGNAL(doorsStateTextChanged(QString)));
}

void elevator::updateState()
{
    setState(state);
    cab.updateState();
}

void elevator::setState(ElevatorState state)
{
    this->state = state;

    QString stateText;

    switch (state) {
    case ElevatorStateBusy:
        stateText = "Занят";
        break;
    case ElevatorStateFree:
        stateText = "Свободен";
        break;
//    case ElevatorStateWaiting:
//        stateText = "Ожидает";
//        break;
    }

    qDebug() << "Лифт: " << stateText;

    emit stateTextChanged(stateText);
}

void elevator::floorButtonPressed(int floor)
{
    if (std::find(queue.begin(), queue.end(), floor) == queue.end()) {
        queue.push_back(floor);
    }

    if (state == ElevatorStateFree) {
        setState(ElevatorStateBusy);

        if (cab.currentFloor() == floor) {
            emit openDoors();
            return;
        }

        bool movingUp = cab.currentFloor() < floor;

        if (movingUp) {
            emit moveUp();
        } else {
            emit moveDown();
        }
    }
}

//void elevator::cabinReady()
//{
//    //setState(ElevatorStateWaiting);

//    queue.erase(std::remove(queue.begin(), queue.end(), cab.currentFloor()), queue.end());

//    if (queue.size() == 0) {
//        setState(ElevatorStateFree);
//    }
//}

void elevator::cabinArrived()
{
    emit floorChanged(cab.currentFloor());

    if (std::find(queue.begin(), queue.end(), cab.currentFloor()) != queue.end()) {
        delay.delayAsync(1000, [=](void) {
            emit openDoors();
            queue.erase(std::remove(queue.begin(), queue.end(), cab.currentFloor()), queue.end());
        });
    } else if (queue.size() == 0) {
        setState(ElevatorStateFree);
    } else {
        setState(ElevatorStateBusy);

        bool movingUp = cab.currentFloor() < queue.front();

        if (movingUp) {
            emit moveUp();
        } else {
            emit moveDown();
        }
    }
}
