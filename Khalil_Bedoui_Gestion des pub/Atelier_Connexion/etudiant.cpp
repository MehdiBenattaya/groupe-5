 #include "etudiant.h"

Etudiant::Etudiant()
{
    id=0; nom=" "; prenom="";
}

Etudiant::Etudiant(int id,QString nom,QString prenom)
{
    this->id=id; this->nom=nom; this->prenom=prenom;}
    int Etudiant::getid(){return id;}
    QString Etudiant::getnom(){return nom;}
    QString Etudiant::getprenom(){return prenom;}
    void Etudiant::setid(int id){this->id=id;}
    void Etudiant::setnom(QString nom){this->nom=nom;}
    void Etudiant::setprenom(QString prenom){this->prenom=prenom;}

bool Etudiant::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("insert into etudiant (id, nom, prenom)""values (:id, :nom, :prenom");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);

    return query.exec();
}
QSqlQueryModel * Etudiant::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from etudiant");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));

    return model;
}
bool Etudiant::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from etudiant where ID= :id");
    query.bindValue(":id",res);

    return query.exec();
}

