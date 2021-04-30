<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clients.h"
#include "commande.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

   // void on_pushButton_5_clicked();



    void on_pushButton_5_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    clients C;
    commande C1;
};

#endif // MAINWINDOW_H
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "poste.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_ajouter_clicked();

    void on_rechercher_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_recherchemodif_clicked();

    void on_tricin_clicked();

    void on_trinom_clicked();

    void on_trinum_clicked();

    void on_pdf_clicked();

    void on_imprimer_clicked();

    void on_trisalaire_clicked();

    void on_trinbheures_clicked();

    void on_trimatricule_clicked();

    void on_browseBtn_clicked();

    void on_sendBtn_clicked();

    void on_recherchermatricule_clicked();

    void on_modifier2_clicked();

    void on_supprimer2_clicked();

private:
    Ui::MainWindow *ui;
    employe E;
    poste P;
    QStringList files;
};
#endif // MAINWINDOW_H
>>>>>>> d2af1979e479e0def15bf13fc7db15f4007ed023
