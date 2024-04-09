#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clock = new Clock(this);
    ui->widget->layout()->addWidget(clock);
    connect(clock, SIGNAL(alarm()), this, SLOT(notificate()));
    connect(ui->set_alarm_btn, SIGNAL(clicked()), this, SLOT(setAlarm()));
    this->setWindowTitle(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    ui->trayCheckBox->setChecked(settings.value(SETTINGS_TRAY, false).toBool());


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("Tray Program" "\n"
                         "Работа со сворачиванием программы трей");

    QMenu * menu = new QMenu(this);
    QAction * viewWindow = new QAction(("Развернуть окно"), this);
    QAction * quitAction = new QAction(("Выход"), this);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewWindow);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAlarm() {
    QTime timeAlarm = this->ui->alarm_edit->time();
    this->clock->setAlarm(timeAlarm);
    this->ui->alam_status_label->setText("Будильник установлен в " + timeAlarm.toString("hh:mm:ss"));
}

void MainWindow::notificate() {
    this->ui->notifications_label->setText(
                this->ui->notifications_label->text() + "Будильник сработал\n"
   );
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(this->isVisible() && ui->trayCheckBox->isChecked()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        trayIcon->showMessage("Tray Program",
                              ("Приложение свернуто в трей. Для того чтобы, "
                                     "развернуть окно приложения, щелкните по иконке приложения в трее"),
                              icon,
                              2000);
    }
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        /* Событие игнорируется в том случае, если чекбокс не отмечен
         * */
        if(ui->trayCheckBox->isChecked()){
            /* иначе, если окно видимо, то оно скрывается,
             * и наоборот, если скрыто, то разворачивается на экран
             * */
            if(!this->isVisible()){
                this->show();
            } else {
                this->hide();
            }
        }
        break;
    default:
        break;
    }
}
void MainWindow::on_saveButton_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    /* Сохранение информации о включённости функции сворачивания
     * в трей производится в соответствии с состоянием чекбокса.
     * */
    if(ui->trayCheckBox->isChecked()){
        settings.setValue(SETTINGS_TRAY, true);
    } else {
        settings.setValue(SETTINGS_TRAY, false);
    }
    settings.sync();

    /* Диалоговое сообщение, которое сигнализирует об успешности
     * сохранения настроек
     * */
    QMessageBox::information(this,
                             ("Сохранение настроек"),
                             ("Сохранение настроек выполнено успешно"));
}
