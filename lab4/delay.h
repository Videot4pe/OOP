#ifndef DELAY_H
#define DELAY_H
#include <QTime>
#include <QTimer>
#include <QCoreApplication>

class Delay : public QObject
{
    Q_OBJECT
public:
    Delay();
    void delayAsync(int msec, std::function<void(void)> callback);
};
#endif // DELAY_H
