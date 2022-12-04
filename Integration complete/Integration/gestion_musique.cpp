#include "gestion_musique.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

GESTION_MUSIQUE::GESTION_MUSIQUE()
{
titre="";nom="";nat="";genre="";descr="";





}


GESTION_MUSIQUE::GESTION_MUSIQUE(QString titre,QString nom,QString nat,QString genre,QString descr)
{this->titre=titre; this->nom=nom; this->nat=nat;this->genre=genre ; this->descr=descr;}
QString GESTION_MUSIQUE::gettitre(){return titre;}
QString GESTION_MUSIQUE::getnom(){return nom;}
QString GESTION_MUSIQUE::getnat(){return nat;}
QString GESTION_MUSIQUE::getgenre(){return genre;}
QString GESTION_MUSIQUE::getdescr(){return descr;}
void GESTION_MUSIQUE::settitre(QString titre){this->titre=titre;}
void GESTION_MUSIQUE::setnom(QString nom){this->nom=nom;}
void GESTION_MUSIQUE::setnat(QString nat){this->nat=nat;}
void GESTION_MUSIQUE::setgenre(QString genre){this->genre=genre;}
void GESTION_MUSIQUE::setdescr(QString descr){this->descr=descr;}
bool GESTION_MUSIQUE::ajouter()
{
    bool test=false;
    QSqlQuery query;
         query.prepare("INSERT INTO GESTION_MUSIQUE (TITRE,NOM,NATIONALITE,GENRE,DESCRIPTION) "
                       "VALUES (:titre, :nom, :nat,:genre  ,:descr)");
         query.bindValue(":titre", titre);
         query.bindValue(":nom", nom);
         query.bindValue(":nat", nat);
         query.bindValue(":genre", genre);
         query.bindValue(":descr", descr);
         return query.exec();
         return test;

}
bool GESTION_MUSIQUE::supprimer(QString titre)
{
QSqlQuery query;
 query.prepare("DELETE FROM GESTION_MUSIQUE WHERE titre=:titre");
  query.bindValue(":titre", titre);
 return query.exec();
}

QSqlQueryModel* GESTION_MUSIQUE::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM GESTION_MUSIQUE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("nationalité"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));


    return model;
}
QSqlQueryModel * GESTION_MUSIQUE::tri_Nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from GESTION_MUSIQUE order by nom");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nationalité"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
    return model;
}
QSqlQueryModel * GESTION_MUSIQUE::tri_Genre()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from GESTION_MUSIQUE order by genre");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nationalité"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
    return model;
}
QSqlQueryModel * GESTION_MUSIQUE::tri_Titre()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from GESTION_MUSIQUE order by titre");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nationalité"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
    return model;
}
void GESTION_MUSIQUE::chercheTitre(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from GESTION_MUSIQUE where regexp_like(titre,:titre);");
   query->bindValue(":titre",x);
   if(x==0)
   {
       query->prepare("select * from GESTION_MUSIQUE;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void GESTION_MUSIQUE::chercheNom(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from GESTION_MUSIQUE where regexp_like(nom,:nom);");
   query->bindValue(":nom",x);
   if(x==0)
   {
       query->prepare("select * from GESTION_MUSIQUE;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void GESTION_MUSIQUE::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}





QChartView *GESTION_MUSIQUE::stat_type()
{
    int rap=0;
    int rock=0;
    int house=0;

       // descr;
    QSqlQuery query;
    query.prepare("select * from GESTION_MUSIQUE WHERE genre='rap'");
    query.exec();

    while(query.next())
        rap++;

    query.prepare("select * from GESTION_MUSIQUE WHERE genre='rock'");
    query.exec();

    while(query.next())
       rock++;

    query.prepare("select * from GESTION_MUSIQUE WHERE genre='house'");
    query.exec();

    while(query.next())
        house++;


    qDebug() << rap << rock << house;

    QPieSeries *series = new QPieSeries();
        series->append("rap",rap);
        series->append("rock", rock);
        series->append("house", house);


        QPieSlice *slice = series->slices().at(0);
        slice->setExploded(true);
        slice->setColor("#f55d11");
        QPieSlice *slice2 = series->slices().at(1);
        slice2->setColor("#ff8b52");
       QPieSlice *slice3 = series->slices().at(2);
        slice3->setColor("#e6a88a");
        QPieSlice *slice4 = series->slices().at(3);
        slice4->setColor("#4360f0");

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistique des genres");

        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
chartView->chart()->legend()->hide();
        return chartView;




}











bool GESTION_MUSIQUE::modifier()
{
    bool test=false;


    QSqlQuery query;
         query.prepare("UPDATE GESTION_MUSIQUE set TITRE='"+titre+"', NOM='"+nom+"', NATIONALITE='"+nat+"', GENRE='"+genre+"', DESCRIPTION='"+descr+"' where TITRE='"+titre+"'");
        return query.exec();

        return test;
}













