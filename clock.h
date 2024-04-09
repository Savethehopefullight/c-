#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>


class Clock : public QLCDNumber
{
    Q_OBJECT

public:

    Clock(QWidget *parent = nullptr);
    void start();
    void stop();
    //get_time();
    void setAlarm(QTime);

private slots:

    void on_timer();

signals:
    void alarm();

private:

    QTime currentTime;
    QTimer *timer;
    QTime timeAlarm;
};

#endif // CLOCK_H
