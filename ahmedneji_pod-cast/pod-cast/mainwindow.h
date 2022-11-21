#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "podcast.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QMediaPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();



    void on_pushButton_supprimer_clicked();







    void on_pushButton_clicked();

    void on_pushButton_modifier_clicked();

    void on_tab_podcast_activated(const QModelIndex &index);

    void on_pushButton_rafraichir_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_tri_categorie_clicked();





    void on_pushButton_inserer_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_mute_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pause_clicked();

    void on_horizontalScrollBar_audio_valueChanged(int value);

    void on_pushButton_pdf_clicked();

    void on_pushButton_tri_sujet_clicked();

    void on_pushButton_recherche_sujet_clicked();

    void on_pushButton_recherche_date_clicked();

private:
    Ui::MainWindow *ui;
    Podcast P;
    QMediaPlayer *mMediaPlayer;

};
#endif // MAINWINDOW_H
