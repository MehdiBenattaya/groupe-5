#ifndef INTERFACENEWS_H
#define INTERFACENEWS_H

#include <QDialog>
#include "actualite.h"
#include <QFileDialog>
#include <QImage>
//----------
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

namespace Ui {
class interfacenews;
}

class interfacenews : public QDialog
{
    Q_OBJECT

public:
    explicit interfacenews(QWidget *parent = nullptr);
    ~interfacenews();

private slots:


    void on_pushButton_clicked();

    void on_rafraichir_clicked();

    void on_bouton_supp_clicked();

    void on_listView_activated(const QModelIndex &index);

    void on_bouton_modif_2_clicked();

    void on_saisir_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_categoriechercher_activated();

    void on_trier_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_2_clicked();

    void on_histbouton_clicked();

    void on_histbouton_2_clicked();



    void on_graphebouton_clicked();


    QChartView *  total (int a,  int b, int c, int d, int e, int f, int  g,  int h);


    void on_trier_2_clicked();

    void on_trier_3_clicked();

    void on_pushButton_8_clicked();

    void clearLayout(QLayout *layout);

private:
    Ui::interfacenews *ui;
    Actualite  A;
};

#endif // INTERFACENEWS_H
