#ifndef INTERFACENEWS_H
#define INTERFACENEWS_H
#include "employe.h"
#include <QDialog>
#include "pub.h"
#include "actualite.h"
#include <QFileDialog>
#include <QImage>
//----------
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

//**************

//#include <QMainWindow>
//#include "Pub.h"
#include "mail.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
//#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QByteArray>

#include "arduino.h"
#include "QMainWindow"

#include "arduino.h"
#include "QMainWindow"
#include "podcast.h"

//***zgolli
#include"gestion_musique.h"











namespace Ui {
class interfacenews;
}

class interfacenews : public QDialog
{
    Q_OBJECT

public:
    explicit interfacenews(QWidget *parent = nullptr);
    ~interfacenews();

    //mailing :
        void sendMail();
        void mailSent(QString);

        void browse();




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

    void on_pushButton_3_clicked();

    void on_id_supp_clicked();

    void on_pb_update_clicked();

    void on_refresh_clicked();

    void on_tab_pub_activated(const QModelIndex &index);

    void on_type_2_activated();

    void on_pushButton_5_clicked();

    void on_titre_2_clicked();

    void on_pushButton_6_clicked();

    void on_triDate_clicked();

    void on_pushButton_9_clicked();

    void on_commandLinkButton_clicked();


    void on_EXCEL_clicked();



    void on_browseBtn_clicked();

    void on_sendBtn_clicked();






    void on_pb_code_clicked();
   /*ichrak*/



    void on_pushButton_ajout_ich_clicked();

    void on_pushButton_annuler_ich_clicked();

    void on_pb_supprimer_ich_clicked();

    void on_pushButton_modif_ich_clicked();

    void on_pb_recherche_ich_clicked();

    void on_pushButton_trierid_ich_clicked();

    void on_pushButton_triernom_ich_clicked();

    void on_pushButton_triersalaire_ich_clicked();

    void on_pushButton_excel_ich_clicked();

    void on_pushButton_pdf_ich_clicked();


    void on_TableView_ich_doubleClicked(const QModelIndex &index);

   // void on_btnLogin_4_clicked();

    //void on_pb_deconnexion_clicked();

    void on_pushButton_stat_ich_clicked();











    //************ahmed


   void on_pb_ajouter_clicked();



    void on_pushButton_supprimer_clicked();







    void on_pushButton_14_clicked();

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









    void on_pb_ajouter_3_clicked();

    void on_pb_supp_2_clicked();

    void on_psuh_recherche_clicked();





    //aziz


    void on_push_TriNom_clicked();

    void on_push_TriTitre_clicked();

    void on_psuh_TriGenre_clicked();




    void update_nb();




    void on_pushButton_25_clicked();

private:
    Ui::interfacenews *ui;
    Actualite  A;
    Employe E;
    QMessageBox msgBox;

        QStringList files;
     PUB p;


     QByteArray data; // variable contenant les données reçues

 QByteArray id;

     Arduino AA; // objet temporaire


     QMediaPlayer *mMediaPlayer;
         Podcast P;

             GESTION_MUSIQUE m;//zgolli

};


#endif // INTERFACENEWS_H