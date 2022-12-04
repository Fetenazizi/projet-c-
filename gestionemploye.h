#ifndef GESTIONEMPLOYE_H
#define GESTIONEMPLOYE_H

#include "employe.h"
#include "conge.h"
#include "arduino.h"

#include <QMainWindow>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>


QT_BEGIN_NAMESPACE
namespace Ui { class GestionEmploye; }
QT_END_NAMESPACE

class GestionEmploye : public QMainWindow
{
    Q_OBJECT

public:
    GestionEmploye(QWidget *parent = nullptr);
    ~GestionEmploye();
void init_aff();
void setEmploye(employe e) ;

private slots:
      void on_B_ajouter_clicked();
      void on_B_supprimer_clicked();
      void on_B_modifier_clicked();

      void on_B_ajouter_conge_clicked() ;





      void on_dateEdit_debut_dateChanged(const QDate &date);


      void on_pushButton_chercher_clicked();

      void on_pushButton_pdf_clicked();

      void on_pushButton_trier_clicked();



void on_table_conge_activated(const QModelIndex &index);



void on_lineEdit_5_textChanged(const QString &arg1);

void on_pushButton_demanddereduction_clicked();

void on_pushButton_refuser_conge_clicked();

void on_pushButton_accepter_conge_clicked();

void on_pageee_currentChanged(int index);



void on_pb_verify_clicked();


void on_pushButtonHomeGestEmp_clicked();

private:
    Ui::GestionEmploye *ui;
    employe e;
    conge c , c2 ;
    int id_conge ;


    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire




};
#endif // GESTIONEMPLOYE_H
