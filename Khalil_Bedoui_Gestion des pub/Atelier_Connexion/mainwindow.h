#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Pub.h"
#include "mail.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //mailing :
        void sendMail();
        void mailSent(QString);
        void browse();

private slots :

    void on_pushButton_clicked();

    void on_id_supp_clicked();

    void on_pb_update_clicked();

    void on_type_2_activated();

    void on_refresh_clicked();

    void on_tab_pub_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_commandLinkButton_clicked();

    void on_titre_2_clicked();

    void on_pushButton_5_clicked();

    void on_browseBtn_clicked();

    void on_sendBtn_clicked();

    void on_video_on_clicked();

    void on_pushButton_6_clicked();

    void on_triDate_clicked();

    void on_pushButton_7_clicked();

    void on_pb_code_clicked();


    void readSerial();
    void updateTemperature(QString sensor_reading);
private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QStringList files;
    PUB p;
    QSerialPort *arduino;
        static const quint16 arduino_uno_vendor_id = 9025;
        static const quint16 arduino_uno_product_id = 67;
        QByteArray serialData;
        QString serialBuffer;
        QString parsed_data;
        double temperature_value;
};

#endif // MAINWINDOW_H
