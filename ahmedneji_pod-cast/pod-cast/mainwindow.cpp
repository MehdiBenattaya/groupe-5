#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "podcast.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QTextDocument>
//#include <QDateTime>
#include <QTextStream>
#include <QBuffer>
#include <QByteArray>
#include <QIntValidator>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_podcast->setModel(P.afficher());
    mMediaPlayer = new QMediaPlayer(this);

    connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos){
        ui->progressBar_audio->setValue(pos);
    });

    connect(mMediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 dur){
        ui->progressBar_audio->setMaximum(dur);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    int nmbdeparticipants=ui->lineEdit_nmbdeparticipants->text().toInt();
    QString script=ui->lineEdit_script->text();
    QString duree=ui->lineEdit_duree->text();
    QString date=ui->lineEdit_date->text();
    QString heure=ui->lineEdit_heure->text();
    QString sujet=ui->lineEdit_sujet->text();
    QString categorie=ui->comboBox_categorie->currentText();
    QString audio=ui->lineEdit_path->text();
Podcast P(id, sujet, nmbdeparticipants, script, duree, date, heure,categorie,audio);
bool test=P.ajouter();

QMessageBox msgBox;

if(test)
{msgBox.setText("ajout avec succes.");
ui->tab_podcast->setModel(P.afficher());
}

else
    msgBox.setText("echec de l'ajout");
    msgBox.exec();


}



void MainWindow::on_pushButton_supprimer_clicked()
{
    Podcast P1; P1.setid(ui->lineEdit_id_supp->text().toInt());
    bool test=P1.supprimer(P1.getid());

    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succes.");
    ui->tab_podcast->setModel(P.afficher());
    }


    else
        msgBox.setText("echec de suppression");
        msgBox.exec();


}








void MainWindow::on_pushButton_clicked()
{
 ui->tab_podcast->setModel(P.tri());
}
void MainWindow::on_pushButton_tri_sujet_clicked()
{
 ui->tab_podcast->setModel(P.tri_sujet());
}
void MainWindow::on_pushButton_tri_categorie_clicked()
{
    Podcast P2;
    QString categorie ;
         categorie= ui->comboBox_categorie_tri->currentText();

        ui->tab_podcast->setModel(P2.triercategorie(categorie));
}
void MainWindow::on_pushButton_modifier_clicked()
{
    Podcast P1;
       P1.setid(ui->lineEdit_id_supp->text().toInt());

       int id= ui->lineEdit_id1->text().toInt();
       int nmbdeparticipants= ui->lineEdit_nmbdeparticipants1->text().toInt();
       QString script= ui->lineEdit_script1->text();

       QString duree= ui->lineEdit_duree1->text(); // this is only vlaid if u visually design the window and placed dateEdit
       QString date = ui->lineEdit_date1->text();

       QString heure= ui->lineEdit_heure1->text();

       QString categorie= ui->comboBox_categorie_1->currentText();

       QString sujet= ui->lineEdit_sujet1->text();

       QString audio= ui->lineEdit_path_1->text();




       Podcast P( id, sujet, nmbdeparticipants, script, duree, date, heure, categorie,audio);

       bool test=P.modifier();
       if (test)
       { QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modification effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not OK"), QObject::tr("modification non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);



}

void MainWindow::on_tab_podcast_activated(const QModelIndex &index)
{
    int id=ui->tab_podcast->model()->data(index).toInt();




    QString id_string= QString::number(id);


    QSqlQuery qry;
    qry.prepare("select * FROM PODCAST WHERE IDPOD='"+id_string+"' or SUJET='"+id_string+"' or PARTICIPANT='"+id_string+"' or SCRIPT='"+id_string+"' or DUREE='"+id_string+"' or DATEPOD='"+id_string+"' or HEURE='"+id_string+"' or CATEGORIEPOD='"+id_string+"' or AUDIO='"+id_string+"' " );


    if (qry.exec())
        {   while (qry.next())
                {
             ui->lineEdit_id_supp->setText(qry.value(0).toString());



                  ui->lineEdit_id1->setText(qry.value(0).toString());
                   ui->lineEdit_sujet1->setText(qry.value(1).toString());
                    ui->lineEdit_nmbdeparticipants1->setText(qry.value(2).toString());

                   /* QString date_string = qry.value(3).toString();
                     QDate Date = QDate::fromString(date_string);
                      ui->le_date_2->setDisplayFormat(date_string);*/

                      ui->lineEdit_script1->setText(qry.value(3).toString());
                 ui->lineEdit_duree1->setText(qry.value(4).toString());
                 ui->lineEdit_date1->setText(qry.value(5).toString());
                 ui->lineEdit_heure1->setText(qry.value(6).toString());

                 //QSqlQueryModel *modal=new QSqlQueryModel();
                 //modal    ->setQuery (qry);
                 //ui->comboBox_categorie_1->findText(qry.value(7).toString());

                 mMediaPlayer->setMedia(QUrl::fromLocalFile(qry.value(8).toString()));
                 mMediaPlayer->setVolume(ui->horizontalScrollBar_audio->value());
                 on_pushButton_play_clicked();






                }
        }
}

void MainWindow::on_pushButton_rafraichir_clicked()
{
    Podcast P;
    ui->tab_podcast->setModel(P.afficher());
}

void MainWindow::on_pushButton_rechercher_clicked()
{
    Podcast P1;
        int id ;
             id= ui->lineEdit_rechercher->text().toInt();
        ui->tab_podcast->setModel(P1.rechercher(id));
}

void MainWindow::on_pushButton_recherche_sujet_clicked()
{
    Podcast P1;
        QString sujet;
            sujet= ui->lineEdit_recherche_sujet->text();
            ui->tab_podcast->setModel(P1.rechercher_sujet(sujet));
}

void MainWindow::on_pushButton_recherche_date_clicked()
{
    Podcast P1;
        QString date;
            date= ui->lineEdit_recherche_date->text();
            ui->tab_podcast->setModel(P1.rechercher_date(date));
}





void MainWindow::on_pushButton_inserer_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this, "Inserer");
  if (filename.isEmpty()){
      return;
  }
  mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
  mMediaPlayer->setVolume(ui->horizontalScrollBar_audio->value());
  on_pushButton_play_clicked();
  ui->lineEdit_path->setText(filename);
}

void MainWindow::on_pushButton_play_clicked()
{
    mMediaPlayer->play();
}

void MainWindow::on_pushButton_mute_clicked()
{
    if (ui->pushButton_mute->text() == "Mute"){
        mMediaPlayer->setMuted(true);
        ui->pushButton_mute->setText("Unmute");
     } else {
        mMediaPlayer->setMuted(false);
        ui->pushButton_mute->setText("Mute");
    }
}

void MainWindow::on_pushButton_stop_clicked()
{
mMediaPlayer->stop();
}

void MainWindow::on_pushButton_pause_clicked()
{
mMediaPlayer->pause();
}

void MainWindow::on_horizontalScrollBar_audio_valueChanged(int value)
{
mMediaPlayer->setVolume(value);
}

void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
                strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                    if (QFileInfo(strStream).suffix().isEmpty())
                        { strStream.append(".pdf"); }

                    QPrinter printer(QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setPaperSize(QPrinter::A4);
                    printer.setOutputFileName(strStream);

                          QTextStream out(&strStream);

                          const int rowCount = ui->tab_podcast->model()->rowCount();
                          const int columnCount = ui->tab_podcast->model()->columnCount();
                          QString TT = QDateTime::currentDateTime().toString();
                          out <<"<html>\n"
                                "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              << "<title>ERP - COMmANDE LIST<title>\n "
                              << "</head>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                                 "<h1 style=\"text-align: center;\"><strong> ***LISTE DES PODCASTS *** </strong></h1>"

                              "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                                "</br> </br>";
                          // headers
                          out << "<thead><tr bgcolor=#d6e5ff>";
                          for (int column = 0; column < columnCount; column++)
                              if (!ui->tab_podcast->isColumnHidden(column))
                                  out << QString("<th>%1</th>").arg(ui->tab_podcast->model()->headerData(column, Qt::Horizontal).toString());
                          out << "</tr></thead>\n";

                          // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++)
                            {
                                  if (!ui->tab_podcast->isColumnHidden(column)) {
                                      QString data =ui->tab_podcast->model()->data(ui->tab_podcast->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //
                                  }
                              }
                              out << "</tr>\n";
                          }
                          out <<  "</table>\n"
                              "</body>\n"
                              "</html>\n";

                          QTextDocument document;
                          document.setHtml(strStream);
                          document.print(&printer);

}








