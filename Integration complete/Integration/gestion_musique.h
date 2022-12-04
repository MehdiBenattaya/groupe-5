#ifndef GESTION_MUSIQUE_H
#define GESTION_MUSIQUE_H



#include<QString>
#include<QSqlQueryModel>
#include<QTableView>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>




class GESTION_MUSIQUE
{
public:
    GESTION_MUSIQUE();
   GESTION_MUSIQUE(QString,QString,QString,QString,QString);
    QString gettitre();
    QString getnom();
    QString getnat();
    QString getgenre();
    QString getdescr();

    void settitre(QString);
    void setnom(QString);
    void setnat(QString);
    void setgenre(QString);
    void setdescr(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* tri_Titre();
    QSqlQueryModel* tri_Nom();
    QSqlQueryModel* tri_Genre();
    void clearTable(QTableView * table);
    void chercheTitre(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);
    bool supprimer(QString);
    bool modifier();
       QChartView * stat_type();


    private:
        QString titre,nom,nat,genre,descr;







};













#endif // GESTION_MUSIQUE_H
