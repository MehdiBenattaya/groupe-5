#ifndef PODCAST_H
#define PODCAST_H
#include <QString>
#include <QSqlQueryModel>

class Podcast
{
public:
    Podcast();
    Podcast(int,QString,int,QString,QString,QString,QString);
    int getid();
    int getnmbdeparticipants();
    QString getscript();
    QString getduree();
    QString getdate();
    QString getheure();
    QString getsujet();
    void setid(int);
    void setnmbdeparticipants(int);
    void setscript(QString);
    void setduree(QString);
    void setdate(QString);
    void setheure(QString);
    void setsujet(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);





private:
    int id;
    int nmbdeparticipants;
    QString script, duree, date, heure,sujet;

};

#endif // PODCAST_H
