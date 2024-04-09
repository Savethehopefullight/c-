#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>
#include <QTime>
#include "clock.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QSettings>
#include <QMessageBox>
#define ORGANIZATION_NAME "NSTU"
#define ORGANIZATION_DOMAIN "www.nstu.ru"
#define APPLICATION_NAME "QSettings Program"
#define SETTINGS_TRAY "settings/tray"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



protected:

    void closeEvent(QCloseEvent * event);


private slots:
    void notificate();
    void setAlarm();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    Clock *clock;
    QTimer *timer;
    QSystemTrayIcon * trayIcon;
};
#endif // MAINWINDOW_H
