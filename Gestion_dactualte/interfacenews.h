#ifndef INTERFACENEWS_H
#define INTERFACENEWS_H

#include <QDialog>
#include "actualite.h"
#include <QFileDialog>
#include <QImage>


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

private:
    Ui::interfacenews *ui;
    Actualite  A;
};

#endif // INTERFACENEWS_H
