#ifndef PODCAST_H
#define PODCAST_H



#include <QString>
#include <QSqlQueryModel>

class Podcast
{
public:
    Podcast();
    Podcast(int,QString,int,QString,QString,QString,QString,QString,QString);
    int getid();
    int getnmbdeparticipants();
    QString getscript();
    QString getduree();
    QString getdate();
    QString getheure();
    QString getsujet();
    QString getcategorie();
    QString getaudio();
    void setid(int);
    void setnmbdeparticipants(int);
    void setscript(QString);
    void setduree(QString);
    void setdate(QString);
    void setheure(QString);
    void setsujet(QString);
    void setcategorie(QString);
    void setaudio(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel * tri();
    QSqlQueryModel * tri_sujet();
    bool modifier();
    QSqlQueryModel * rechercher(int);
    QSqlQueryModel *rechercher_sujet(QString);
    QSqlQueryModel *rechercher_date(QString);
    QSqlQueryModel * triercategorie(QString);
    void genererPDFact();




private:
    int id;
    int nmbdeparticipants;
    QString script, duree, date, heure,sujet,categorie,audio;

};






#endif // PODCAST_H
