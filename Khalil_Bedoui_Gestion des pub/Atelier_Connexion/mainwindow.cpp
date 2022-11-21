#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pub.h"
#include "qrcode.h"
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QPixmap>
#include<QDirModel>
#include <QtSvg/QSvgRenderer>
#include <QFile>
#include <QFileDialog>
#include <fstream>
#include <QTextStream>
#include <QPainter>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

using qrcodegen::QrCode;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(100, 9999999, this));
    ui->tab_pub->setModel(p.afficher());

    ui->templcdNumber->display("--------");
    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;

    // Identify the port the arduino uno is on.
        bool arduino_is_available = false;
        QString arduino_uno_port_name;
        //
        //  For each available serial port
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id))
                {
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_uno_port_name = serialPortInfo.portName();
                }
            }
        }

        //Open and configure the arduino port if available

            if(arduino_is_available)
            {
                qDebug() << "Found the arduino port...\n";
                arduino->setPortName(arduino_uno_port_name);
                arduino->open(QSerialPort::ReadOnly);
                arduino->setBaudRate(QSerialPort::Baud9600);
                arduino->setDataBits(QSerialPort::Data8);
                arduino->setFlowControl(QSerialPort::NoFlowControl);
                arduino->setParity(QSerialPort::NoParity);
                arduino->setStopBits(QSerialPort::OneStop);
                QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
            }
            else
            {
                qDebug() << "Couldn't find the correct port for the arduino.\n";
                QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
            }

}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
            arduino->close();} //    Close the serial port if it's open.
    delete ui;
}




void MainWindow::readSerial()
{
        QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

        //  Check to see if there less than 3 tokens in buffer_split.
        //  If there are at least 3 then this means there were 2 commas,
        //  means there is a parsed temperature value as the second token (between 2 commas)
        if(buffer_split.length() < 3){
            // no parsed value yet so continue accumulating bytes from serial in the buffer.
            serialData = arduino->readAll();
            serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
            serialData.clear();
        }
        else
        {
            // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
            serialBuffer = "";
            qDebug() << buffer_split << "\n";
            parsed_data = buffer_split[1];
            temperature_value = (9/5.0) * (parsed_data.toDouble()) + 32; // convert to fahrenheit
            qDebug() << "Temperature: " << temperature_value << "\n";
            parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
            MainWindow::updateTemperature(parsed_data);
        }

}

void MainWindow::updateTemperature(QString sensor_reading)
    {
        //  update the value displayed on the lcdNumber
        ui->templcdNumber->display(sensor_reading);
    }






void MainWindow::on_pushButton_clicked()  //Ajout
{
    int id=ui->le_id->text().toInt();
    QString titre=ui->titre->text();
    QString description=ui->description->text();
    QString type=ui->type->currentText();
    QString date=ui->date->text();

    PUB p(id,titre,description,type,date);
    bool test=p.ajouter();
    QMessageBox msgBox;
    if(test)
    {
    msgBox.setText("Ajout avec succes.");
    ui->tab_pub->setModel(p.afficher());
    }
    else
        msgBox.setText("Echec de l'Ajout");
        msgBox.exec();
}


void MainWindow::on_id_supp_clicked() //SUPPRESSION
{
    PUB p;
    p.setid(ui->le_id_supp_2->text().toInt());
    bool test=p.supprimer(p.getid());

    QMessageBox msgBox;
    if(test)
    {
    msgBox.setText("Suppression avec succes.");
    ui->tab_pub->setModel(p.afficher());
    }
else
    msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_pb_update_clicked()  //UPDATE
{
    int id=ui->le_newid->text().toInt();
        QString titre= ui->le_newtitre->text();
        QString description=ui->le_newdescription->text();
        QString type=ui->le_newtype->currentText();
        QString date=ui->le_newdate->text();
        PUB p(id,titre,description,type,date);
        bool test=p.modifier();
        if (test)
         {
            ui->tab_pub->setModel(p.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

         }
         else
         {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}

}


void MainWindow::on_refresh_clicked()  //Refresh
{
    PUB p;
    ui->tab_pub->setModel(p.afficher());
}

void MainWindow::on_tab_pub_activated(const QModelIndex &index) //controle_de_saisie
{


    QString id=ui->tab_pub->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * FROM PUB1 WHERE ID='"+id+"' or TITRE='"+id+"' or DESCRIPTION='"+id+"' or TYPE='"+id+"' or DATE_P='"+id+"' or DESCRIPTION='"+id+"' " );

    if (qry.exec())
        {   while (qry.next())
                {
             ui->le_id_supp_2->setText(qry.value(0).toString());
                  ui->le_newid->setText(qry.value(0).toString());
                   ui->le_newtitre->setText(qry.value(1).toString());
                    ui->le_newdescription->setText(qry.value(2).toString());
                      ui->le_newdate->setText(qry.value(4).toString());
                }
        }
}


void MainWindow::on_type_2_activated() //Recherchertype
{
    PUB p;
    QString type ;
         type= ui->type_2->currentText();
    ui->tab_pub->setModel(p.Rechercher(type));

}

void MainWindow::on_pushButton_3_clicked()  //RECHERCHER_ID
{
    PUB p;
    int id ;
    id= ui->le_id_supp_2->text().toInt();
    ui->tab_pub->setModel(p.Rechercherid(id));
}





void MainWindow::on_titre_2_clicked()   //RechercherTITRE
{
    PUB p;
    QString titre ;
         titre= ui->titre_3->text();
    ui->tab_pub->setModel(p.Recherchertitre(titre));
}

void MainWindow::on_pushButton_5_clicked()  //tri_ID
{
    ui->tab_pub->setModel(p.tri());
}
void MainWindow::on_triDate_clicked()
{
    PUB p;
    ui->tab_pub->setModel(p.tridate());
}

void MainWindow::on_pushButton_7_clicked() //tri par ordre alpha :
{
    PUB p;
    ui->tab_pub->setModel(p.tri());
}



void MainWindow::on_commandLinkButton_clicked()     //PDF
{
    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tab_pub->model()->rowCount();
                    const int columnCount =ui->tab_pub->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Evenements</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_pub->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_pub->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tab_pub->isColumnHidden(column)) {
                                       QString data = ui->tab_pub->model()->data(ui->tab_pub->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);


            //QTextDocument document;
            //document.setHtml(html);
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("PDF.pdf");
            document->print(&printer);

}


void MainWindow::on_browseBtn_clicked()
{
    files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            files = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, files)
            fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

        ui->file->setText( fileListString );
}



void MainWindow::on_sendBtn_clicked()
{
    mail* smtp = new mail("bedoui.khalil@esprit.tn",ui->mail_pass->text(), "mail.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        if( !files.isEmpty() )
            smtp->sendMail("bedoui.khalil@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
        else
            smtp->sendMail("bedoui.khalil@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
    }
    void   MainWindow::mailSent(QString status)
    {

        if(status == "Message sent")
            QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
        ui->rcpt->clear();
        ui->subject->clear();
        ui->file->clear();
        ui->msg->clear();
        ui->mail_pass->clear();
}

void MainWindow::on_video_on_clicked() // PLAY VIDEO
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    //auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    //player->setMedia(QUrl::fromLocalFile(filename));
        player->setMedia(QUrl::fromLocalFile("C:/Users/Khalil/Downloads/313914711_5356186734504783_5519350197100489517_n.mp4"));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}

void MainWindow::on_pushButton_6_clicked() //STOP VIDEO
{
    player->stop();
    vw->close();
}



void MainWindow::on_pb_code_clicked()
{
    PUB p ;
        if(ui->tab_pub->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir une PUB du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {
                           p.setid(ui->le_id->text().toInt());
                           p.settitre(ui->titre->text());
                           p.setdescription(ui->description->text());
                           p.settype(ui->type->currentText());
                           p.setdate(ui->date->text());

                   // int idAnim=ui->tab_animaux->model()->data(ui->tab_animaux->model()->index(ui->tab_animaux->currentIndex().row(),0)).toInt();


                 QString  rawQr = "ID:%1 TITRE:%2 DESCRIPTION:%3 TYPE:%4 DATE_P:%5" ;
                 rawQr = rawQr.arg(  p.getid()).arg(  p.gettitre()).arg(  p.getdescription()).arg(  p.gettype()).arg(  p.getdate());
                 QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);


                  //  const QrCode qr = QrCode::encodeText(std::to_string(idAnim).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(140, 140) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->label_qrcode->setPixmap(pix);
               }
}


