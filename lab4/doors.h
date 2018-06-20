#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include "delay.h"

class doors : public QObject
{
    Q_OBJECT
    enum DoorState
    {
        DoorStateOpen,
        DoorStateClosed,
        DoorStateOpening,
        DoorStateClosing
    };

public:
    doors();
    bool isOpen();
    void updateState();

private:
    void setState(DoorState state);

    DoorState st;
    Delay delay;

public slots:
  void opening();
  void closing();
  void opened();
  void closed();

signals:
  void open();
  void close();
  void alreadyOpened();
  void alreadyClosed();
  void stateTextChanged(QString stateText);
};

#endif // DOORS_H
