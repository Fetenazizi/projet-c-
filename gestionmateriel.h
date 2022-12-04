#ifndef GESTIONMATERIEL_H
#define GESTIONMATERIEL_H
#include <QMainWindow>
#include "materiel.h"
#include "employe.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <arduino.h>

QT_BEGIN_NAMESPACE
namespace Ui {class GestionMateriel; }
QT_END_NAMESPACE

class GestionMateriel : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionMateriel(QWidget *parent = nullptr);
    ~GestionMateriel();



    QSortFilterProxyModel *proxy;
    void setEmploye(employe e) ;
private slots:

    void on_on_pushButton_ajouter_clicked_clicked();

    void on_modifier_clicked();

    void on_pushButton_clicked();//pdf

    void on_pushButton_2_clicked();//recherche

    void on_pushButton_3_clicked();//supp

    void on_pb_trier_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButtonhomeMateriel_clicked();



private:

    Ui::GestionMateriel *ui;
      materiel mp;
      employe e;

 QByteArray data;

     Arduino A;

};
#endif // MAINWINDOW_H
