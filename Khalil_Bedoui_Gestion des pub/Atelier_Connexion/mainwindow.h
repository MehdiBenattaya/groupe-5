#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Pub.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots :

    void on_pushButton_clicked();

    void on_id_supp_clicked();

    void on_pb_update_clicked();

    void on_type_2_activated();

    void on_refresh_clicked();

    void on_tab_pub_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    PUB p;
};

#endif // MAINWINDOW_H
