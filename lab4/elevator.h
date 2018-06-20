#ifndef elevator_H
#define elevator_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>
#include <QQueue>
#include <QLabel>

#include "cabin.h"
#include "delay.h"


using namespace std;

class elevator : public QObject
{
    Q_OBJECT
    enum ElevatorState
    {
        ElevatorStateBusy,
        ElevatorStateFree,
    };
public:
    elevator();

    void updateState();

private:
    void setState(ElevatorState state);
    cabin cab;
    std::vector<int> queue;
    ElevatorState state;
    Delay delay;

public slots:
    void floorButtonPressed(int floor);
    //void cabinReady();
    void cabinArrived();
signals:
    void moveUp();
    void moveDown();
    void openDoors();
    void stateTextChanged(QString stateText);
    void cabinStateTextChanged(QString stateText);
    void doorsStateTextChanged(QString stateText);
    void floorChanged(int floor);
};

#endif // elevator_H
