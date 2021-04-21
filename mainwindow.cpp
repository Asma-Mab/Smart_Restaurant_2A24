#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produits.h"
#include <QMessageBox>
#include <QDialog>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SMART RESTAURANT");
    setWindowIcon(QIcon(":/53378.png"));
    QPixmap bg(":/black.jpg");
    ui->label_20->setPixmap(bg);
    ui->tableView_2->setModel(tmpPRODUITS.afficher());
     ui->tableView_2->setModel(tmpPRODUITS.afficher2());
      ui->tableView_2->setModel(tmpPRODUITS.afficher3());
    ui->tableView->setModel(tmpPROMOTIONS.afficher());
    ui->tableView->setModel(tmpPROMOTIONS.afficher2());
    ui->tableView->setModel(tmpPROMOTIONS.afficher3());
    ui->tableView_3->setModel(tmpPRODUITS.afficher());
    ui->tableView_3->setModel(tmpPRODUITS.rechercher(ch));
    ui->tableView_4->setModel(tmpPROMOTIONS.afficher());
    ui->tableView_4->setModel(tmpPROMOTIONS.rechercher(ch));
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AJOUTER_clicked()
{
sound->play();
    int id=ui->lineEdit_ideFRMTIONADD->text().toInt();
    QString nom=ui->lineEdit_NOMFRMTSADD->text();
    QString type=ui->lineEdit_DOMAINEADDFRMTS->text();
    QString prix=ui->lineEdit_depart_add->text();
    QString description=ui->description->text();
    PRODUITS f(id,nom,prix,type,description);
    bool test=f.ajouter();
    if(test)

    {
         ui->tableView_2->setModel(tmpPRODUITS.afficher());
            ui->tableView_3->setModel(tmpPRODUITS.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout PRODUITS"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout PRODUITS"),
                                 QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_VALIDERMOD_clicked()
{
    sound->play();
    int id=ui->lineEdit_IDMODFRMTS->text().toInt();
    QString nom=ui->lineEdit_NOUVNOMMOD->text();
    QString type=ui->lineEdit_NOUVDOMMOD->text();
    QString prix=ui->lineEdit_dep->text();
     QString description=ui->desc_mod->text();
    PRODUITS f(id,nom,prix,type,description);
    bool test=f.modifier(id,nom,prix,type,description);
    if(test)
    {
        ui->tableView_2->setModel(tmpPRODUITS.afficher());
           ui->tableView_3->setModel(tmpPRODUITS.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier PRODUITS"),
                                 QObject::tr("Modifier avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier PRODUITS"),
                                 QObject::tr("Modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_SUPPRIMERFRMTS_clicked()
{
    sound->play();
    int id=ui->lineEdit_IDSUPP->text().toInt();
    bool test=f.supprimer(id);
    if(test)
    {
           ui->tableView_3->setModel(tmpPRODUITS.afficher());
        ui->tableView_2->setModel(tmpPRODUITS.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer PRODUITS"),
                                 QObject::tr("supprimer avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("supprimer PRODUITS"),
                                 QObject::tr("suppression échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_add_teurs_clicked()
{
    sound->play();
    int id=ui->lineEdit_ID_ADD_teurs->text().toInt();
    QString type=ui->lineEdit_nom_add_teurs->text();
    QString dated=ui->lineEdit_dom_add_teurs->text();
    QString datef=ui->datef_add->text();
     QString pourcentage=ui->pourc_add->text();
    PROMOTIONS g(id,type,dated,datef,pourcentage);
    bool test=g.ajouter();
    if(test)

    {
         ui->tableView_4->setModel(tmpPROMOTIONS.afficher());
         ui->tableView->setModel(tmpPROMOTIONS.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout PROMOTIONS"),
                                 QObject::tr("ajout avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout PROMOTIONS"),
                                 QObject::tr("ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_mod_teurs_clicked()
{
    sound->play();
    int id=ui->lineEdit_id_mod_teur->text().toInt();
    QString type=ui->lineEdit_nom_mod_teurs->text();
    QString dated=ui->lineEdit_dom_mod_teurs->text();
     QString datef=ui->nvf_mod->text();
      QString pourcentage=ui->nvpmod->text();
    PROMOTIONS g(id,type,dated,datef,pourcentage);
    bool test=g.modifier(id,type,dated,datef,pourcentage);
    if(test)
    {
         ui->tableView_4->setModel(tmpPROMOTIONS.afficher());
        ui->tableView->setModel(tmpPROMOTIONS.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier promotions"),
                                 QObject::tr("Modifier avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier promotions"),
                                 QObject::tr("Modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pushButton_supp_teur_clicked()
{
    sound->play();
    int id=ui->lineEdit_id_supp_teurs->text().toInt();
    bool test=g.supprimer(id);
    if(test)
    {
         ui->tableView_4->setModel(tmpPROMOTIONS.afficher());
        ui->tableView->setModel(tmpPROMOTIONS.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer PROMOTIONS"),
                                 QObject::tr("supprimer avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("supprimer PROMOTIONS"),
                                 QObject::tr("suppression échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_rechercher_3_textChanged(const QString &ch)
{
    sound->play();
    if (ch=="")
    ui->tableView_3->setModel(f.afficher());
    else
    this->ui->tableView_3->setModel(f.rechercher(ch));


}
void MainWindow::on_rechercher_2_textChanged(const QString &ch)
{
    sound->play();
    if (ch=="")
    ui->tableView_4->setModel(g.afficher());
    else
    this->ui->tableView_4->setModel(g.rechercher(ch));

}
void MainWindow::on_radioButton_nom_clicked()
{
    sound->play();
    ui->tableView->setModel(tmpPROMOTIONS.afficher2());

}
void MainWindow::on_radioButton_cin_clicked()
{
    sound->play();
     ui->tableView->setModel(tmpPROMOTIONS.afficher());
}
void MainWindow::on_radioButton_pre_clicked()
{
    sound->play();
    ui->tableView->setModel(tmpPROMOTIONS.afficher3());
}
void MainWindow::on_radioButton_CODE_clicked()
{
       ui->tableView_2->setModel(tmpPRODUITS.afficher());
}
void MainWindow:: on_radioButton_NOM_clicked()
{
    sound->play();
     ui->tableView_2->setModel(tmpPRODUITS.afficher2());
}
void MainWindow:: on_radioButton_DOMAINE_clicked()
{
    sound->play();
     ui->tableView_2->setModel(tmpPRODUITS.afficher3());
}
void MainWindow:: on_radioButton_DEP_clicked()
{
    sound->play();
     ui->tableView_2->setModel(tmpPRODUITS.afficher4());
}
void MainWindow:: on_pdf_tions_clicked()
{
    sound->play();
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView_2->model()->rowCount();
                   const int columnCount =ui->tableView_2->model()->columnCount();

                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("FORMATION")
                           <<  "</head>\n"
                           "<body bgcolor=#ffffff link=#5000A0>\n"
                               "<img src='C:/Users/lenovo/Desktop/malthus/proj_c2a/image/53378.png' width='100' height='100'>\n"
                               "<h1>Liste des Produits </h1>"



                               "<table border=2 cellspacing=1 cellpadding=3>\n";


                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView_2->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView_2->isColumnHidden(column)) {
                                      QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
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


             //  QTextDocument document;
              // document.setHtml(html);
               QPrinter printer(QPrinter::PrinterResolution);
               printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setOutputFileName("Produits.pdf");
               document->print(&printer);
   }

void MainWindow::on_pdf_teurs_clicked()
{
    sound->play();
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView->model()->rowCount();
                   const int columnCount =ui->tableView->model()->columnCount();

                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("FORMATEUR")
                           <<  "</head>\n"
                           "<body bgcolor=#ffffff link=#5000A0>\n"
                               "<img src='C:/Users/lenovo/Desktop/malthus/proj_c2a/image/53378.png' width='100' height='100'>\n"
                               "<h1>Liste des promotions </h1>"



                               "<table border=2 cellspacing=1 cellpadding=3>\n";


                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView->isColumnHidden(column)) {
                                      QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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


             //  QTextDocument document;
              // document.setHtml(html);
               QPrinter printer(QPrinter::PrinterResolution);
               printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setOutputFileName("Formateurs.pdf");
               document->print(&printer);
}
