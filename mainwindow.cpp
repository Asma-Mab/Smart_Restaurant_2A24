#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients.h"
#include "commande.h"
#include <QMessageBox>
#include <iostream>
#include <QMessageBox>
#include  <QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QValidator>
#include <QIntValidator>
#include <QRegExp>
#include "smtp.h"
#include "smtp.cpp"
#include <QAbstractSocket>
#include <QSslSocket>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowTitle("~~Smart Restaurant~~");


    ui->CIN->setValidator (new QIntValidator(0,99999999, this));
    ui->cinsupp->setValidator (new QIntValidator(0,99999999, this));
    ui->ref->setValidator (new QIntValidator(0,99999999, this));
    ui->refsupp->setValidator (new QIntValidator(0,99999999, this));

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    ui->table_clients->setModel(C.afficher());
    ui->table_commande->setModel(Co.afficher());
    }




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    int CIN=ui->CIN->text().toInt();
    int num=ui->num->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adresse=ui->adresse->text();
    QString email=ui->email->text();


    clients C(CIN, num, nom, prenom, adresse, email);
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    ui->table_clients->setModel(C.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}



void MainWindow::on_pushButton_clicked()
{
    int numero=ui->numero->text().toInt();
    int ref=ui->ref->text().toInt();
    int qte=ui->qte->text().toInt();
    int PrixUnit =ui->prixUnitaire->text().toInt();
    int montant=ui->montant->text().toInt();


    commande Co (numero, ref, qte, PrixUnit, montant);
    bool test1=Co.ajouter_commande();
    QMessageBox msgBox;
    if(test1)
      {
      msgBox.setText("ajout avec succée");
      ui->table_commande->setModel(Co.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


void MainWindow::on_pushButton_5_clicked()
{
    commande Co;
    Co.set_ref(ui->refsupp->text().toInt());
    bool test=Co.supprimer_commande(Co.get_ref());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succée");
    ui->table_commande->setModel(Co.afficher());}
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_pushButton_4_clicked()
{

        QMessageBox msgBox;
        clients C1;
        C1.setcin(ui->cinsupp->text().toInt());
        bool test=C1.supprimer(C1.getcin());
        if (test){
            ui->cinsupp->clear();
            ui->table_clients->setModel(C.afficher());
                msgBox.setText("clients supprimé");
                msgBox.exec();
               }
    }



void MainWindow::on_pushButton_11_clicked()
{
    clients C;
    QSqlQuery query;
    int cin=ui->cinmodif->text().toInt();
    QString cin_string=QString::number(cin);
   if(C.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM CLIENTS WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {
       ui->nummodif->setText(query.value(5).toString());
       ui->nommodif->setText(query.value(2).toString());
       ui->prenommodif->setText(query.value(3).toString());
       ui->adressemodif->setText(query.value(4).toString());
       ui->emailmodif->setText(query.value(1).toString());

    }
   }
}

void MainWindow::on_pushButton_3_clicked()
{
    clients C;
    QMessageBox msg;
    C.setcin(ui->cinmodif->text().toInt());
    C.setnum(ui->nummodif->text().toInt());
    C.setnom(ui->nommodif->text());
    C.setprenom(ui->prenommodif->text());
    C.setadresse(ui->adressemodif->text());
    C.setemail(ui->emailmodif->text());

    bool test=C.modifier(C.getcin());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_clients->setModel(C.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

void MainWindow::on_pushButton_8_clicked()
{

  QMessageBox msgBox ;

QSqlQueryModel *model = new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by CIN ASC");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
         ui->table_clients->setModel(model);
         //ui->table_clients->setModel(C.afficher());
         ui->table_clients->show();
         msgBox.setText("Tri avec succès.");
         msgBox.exec();
}

void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM CLIENTS order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
             ui->table_clients->setModel(model);
             ui->table_clients->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void MainWindow::on_pushButton_10_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM CLIENTS order by numero ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));

             ui->table_clients->setModel(model);
             ui->table_clients->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void MainWindow::on_pushButton_7_clicked()
{
    clients C;
        if (ui->comboBox_3->currentText()=="Rechercher par CIN")
        {
            int cin=ui->lineEdit->text().toInt();
            if (C.recherche_cin(cin))
            {
                ui->table_clients->setModel(C.afficher_cin(cin));
            }
        }
        else if(ui->comboBox_3->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit->text();
            if (C.recherche_nom(nom))
            {
                ui->table_clients->setModel(C.afficher_nom(nom));
            }

        }
        else if(ui->comboBox_3->currentText()=="Rechercher par numero")
        {
            int num=ui->lineEdit->text().toInt();
            if(C.recherche_num(num))
            {
                ui->table_clients->setModel(C.afficher_num(num));
            }
        }
}

void MainWindow::on_pushButton_13_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->table_clients->model()->rowCount();
                  const int columnCount = ui->table_clients->model()->columnCount();

                  out <<  "<html>\n"
                      "<head>\n"
                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      <<  QString("<title>%1</title>\n").arg("strTitle")
                      <<  "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"

                     //     "<align='right'> " << datefich << "</align>"
                      "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                  // headers
                  out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->table_clients->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->table_clients->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->table_clients->isColumnHidden(column)) {
                              QString data = ui->table_clients->model()->data(ui->table_clients->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table> </center>\n"
                      "</body>\n"
                      "</html>\n";

            QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
              if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

             QPrinter printer (QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);

             QTextDocument doc;
              doc.setHtml(strStream);
              doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
              doc.print(&printer);
}



void MainWindow::on_pushButton_12_clicked()
{
    commande C1;
    QSqlQuery query;
    int numero=ui->numeromodif->text().toInt();
    QString num=QString::number(numero);
   if(C1.recherche_numc(numero))
   {
       query.prepare("SELECT * FROM COMMANDE WHERE NUMERO like :numero");
       query.bindValue(0,num);
       query.exec();
       while(query.next())
   {
       //ui->numeromodif->setText(query.value(1).toString());
       ui->refmodif->setText(query.value(1).toString());
       ui->quantitemodif->setValue(query.value(2).toString().toInt());
       ui->PrixUnitmodif->setText(query.value(3).toString());
       ui->montantmodif->setText(query.value(4).toString());

    }
   }
}



void MainWindow::on_pushButton_6_clicked()
{
    commande C;
    QMessageBox msg;
    C.set_numero(ui->numeromodif->text().toInt());
    C.set_ref(ui->refmodif->text().toInt());
    C.set_qte(ui->quantitemodif->text().toInt());
    C.set_prix_unit(ui->PrixUnitmodif->text().toInt());
    C.set_montant(ui->montantmodif->text().toInt());

    bool test=C.modifier_commande(C.get_numero());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_commande->setModel(Co.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}




void MainWindow::on_pushButton_14_clicked()
{
    commande C;
        if (ui->comboBox->currentText()=="Recherche par numero")
        {
            int numero=ui->lineEdit_2->text().toInt();
            if (C.recherche_numc(numero))
            {
                ui->table_commande->setModel(Co.afficher_numero(numero));
            }
        }
        else if(ui->comboBox->currentText()=="Recherche par reference")
        {
            int ref=ui->lineEdit_2->text().toInt();
            if (C.recherche_ref(ref))
            {
                ui->table_commande->setModel(Co.afficher_ref(ref));
            }

        }
        else if(ui->comboBox->currentText()=="Recherche par montant")
        {
            int montant=ui->lineEdit_2->text().toInt();
            if(C.recherche_montant(montant))
            {
                ui->table_commande->setModel(Co.afficher_montant(montant));
            }
        }
}



void MainWindow::on_pushButton_15_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM COMMANDE order by REF ASC");
           model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
           model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
           model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
           model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
           model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
           ui->table_commande->setModel(model);
           //ui->table_clients->setModel(C.afficher());
           ui->table_commande->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();
}

void MainWindow::on_pushButton_16_clicked()
{

    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM COMMANDE order by NUMERO ASC");
             model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
             model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
             model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
             model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
             model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
             ui->table_commande->setModel(model);
             ui->table_commande->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void MainWindow::on_pushButton_17_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM COMMANDE order by MONTANT ASC");
             model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
             model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
             model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
             model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
             model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
             ui->table_commande->setModel(model);
             ui->table_commande->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}





void MainWindow::on_pushButton_18_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;

}




void MainWindow::browse()
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

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->text(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->text());
}


void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
