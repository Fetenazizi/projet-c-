

#include "gestionemploye.h"
#include "ui_gestionemploye.h"
#include "employe.h"
#include "arduino.h"
#include "menu.h"

#include "connection.h"
#include <QMessageBox>
#include<iostream>
#include<QPainter>
#include<QImage>
#include <QPdfWriter>
#include<QDesktopServices>
#include <QUrl>
using namespace std ;



GestionEmploye::GestionEmploye(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::GestionEmploye)
{


    ui->setupUi(this);
    ui->table_employe->setModel(e.afficher());
    //  ui->dateEdit_fin->setDate(QDate::currentDate()) ;
    ui->dateEdit_debut->setDate(QDate::currentDate()) ;
    ui->dateEdit_debut->setMinimumDate(QDate::currentDate()) ;
    ui->table_conge->setModel(c.afficher());

    QPieSeries *series=new QPieSeries() ;
    series->append("moins 500",e.getSalireByInterval(0,500));
    series->append("500-1000",e.getSalireByInterval(500,1000));
    series->append("1000-2000",e.getSalireByInterval(1000,2000));
    series->append("2000 ou supp",e.getSalireByInterval(2000,5000000));

    QPieSlice  *slize =series->slices().at(1);
    slize->setExploded(true);
    //    slize->seT


    QChart *chart=new  QChart ();
    chart ->addSeries(series);
    chart->setTitle("salaires");
    QChartView * chartview = new QChartView (chart);
    chartview->setParent(ui->horizontalFrame);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).







}

GestionEmploye::~GestionEmploye()
{
    delete ui;
}

void GestionEmploye::init_aff()
{
    ui->table_employe->setModel(e.afficher());


}

void  GestionEmploye:: setEmploye(employe e) {
    this->e = e ;

    if (e.get_poste()!="admin")
    {ui->pageee->removeTab(0) ;
        ui->pageee->removeTab(0) ;
        ui->pageee->removeTab(0) ;
        ui->pageee->removeTab(0) ;

    }

    ui->lineEdit_cin_conge->setText(QString::number(e.get_cin()));
    ui->lblConge->setText(QString::number(e.get_droit_conge())) ;

    ui->tab_consulter_cong->setModel(c.afficherCongeByCin(e.get_cin()));

    ui->dateEdit_fin->setDate(QDate::currentDate().addDays(e.get_droit_conge())) ;

    ui->dateEdit_fin->setDateRange(QDate::currentDate(),QDate::currentDate().addDays(e.get_droit_conge())) ;

}
void GestionEmploye::on_B_ajouter_clicked()


{
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString poste=ui->lineEdit_poste->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    int droit_conge=ui->lineEdit_droit_conge->text().toInt();
    int nb_heures= ui->lineEdit_nbr_heures->text().toInt() ;
    int nb_heures_suppl= ui->lineEdit_nbr_heures_supp->text().toInt() ;


    employe e(cin,nom,prenom,poste,salaire,droit_conge,nb_heures,nb_heures_suppl);

    bool test=e.ajouter();

    if(test)
    {
        ui->table_employe->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}



void GestionEmploye::on_B_supprimer_clicked()
{
    int cin=ui->lineEdit_supprimer->text().toInt();

    bool test=e.supprimer(cin);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->table_employe->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void GestionEmploye::on_B_modifier_clicked()
{

    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString  poste=ui->lineEdit_poste->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    int droit_conge=ui->lineEdit_droit_conge->text().toInt();
    int nb_heures=ui->lineEdit_nbr_heures->text().toInt();
    int nb_heures_suppl=ui->lineEdit_nbr_heures_supp->text().toInt();


    employe e(cin,nom,prenom,poste,salaire,droit_conge,nb_heures,nb_heures_suppl);

    bool test=e.modifier();

    if(test)
    {
        ui->table_employe->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }


}
void GestionEmploye::on_B_ajouter_conge_clicked()


{
    int cin=ui->lineEdit_cin_conge->text().toInt();
    QDate debut=ui->dateEdit_debut->date();
    QDate fin=ui->dateEdit_fin->date() ;

    conge c(cin,debut,fin,"En attente") ;

    int difference = c.solde(cin) - debut.daysTo(fin)  ;

    bool test=c.ajouter(difference);

    if(test)
    {

        e.setdroit_conge(difference) ;
        ui->dateEdit_fin->setDate(QDate::currentDate().addDays(e.get_droit_conge())) ;
        ui->dateEdit_fin->setDateRange(QDate::currentDate(),QDate::currentDate().addDays(e.get_droit_conge())) ;
        ui->dateEdit_debut->setDate(QDate::currentDate()) ;

        ui->table_conge->setModel(c.afficher());
        ui->tab_consulter_cong->setModel(c.afficherCongeByCin(e.get_cin())) ;
        ui->table_conge->setModel(c.afficher());
        ui->lblConge->setText(QString ::number(e.get_droit_conge())) ;
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}







void GestionEmploye::on_dateEdit_debut_dateChanged(const QDate &date)
{
    ui->dateEdit_fin->setDate(date.addDays(e.get_droit_conge())) ;
    ui->dateEdit_fin->setDateRange(date,date.addDays(e.get_droit_conge())) ;

    //int temp = ( date.year() - QDate::currentDate().year())* 30 ;
    int temp = e.get_droit_conge() ;

    /*     if ( date.year() - QDate::currentDate().year()>0 )
     {
            temp = 30 ; }
*/
    ui->lblConge->setText(QString::number(temp)) ;

}


void GestionEmploye::on_pushButton_pdf_clicked()
{

    QPdfWriter pdf("Liste.pdf");

    QPainter painter(&pdf);

    int i = 4000;
    painter.setPen(Qt::darkGray);
    painter.setFont(QFont("Helvetica", 30));

    painter.drawText(3000,1500,"LISTE DES EMPLOYES");
    painter.setPen(Qt::darkGray);
    painter.setFont(QFont("Helvetica", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Helvetica", 9));
    painter.drawText(300,3300,"CIN");
    painter.drawText(2300,3300,"nom");
    painter.drawText(4300,3300,"prenom");
    painter.drawText(6000,3300,"poste");

    QSqlQuery query;

    query.prepare("select * from employe");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());

        i = i +500;
    }

    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}



void GestionEmploye::on_pushButton_trier_clicked()
{
    ui->table_employe->setModel(e.tri_poste()) ;




}

void GestionEmploye::on_pushButton_chercher_clicked()
{

    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString  poste=ui->lineEdit_poste->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    int droit_conge=ui->lineEdit_droit_conge->text().toInt();
    int nb_heures=ui->lineEdit_nbr_heures->text().toInt();
    int nb_heures_suppl=ui->lineEdit_nbr_heures_supp->text().toInt();


    employe e(cin,nom,prenom,poste,salaire,droit_conge,nb_heures,nb_heures_suppl);


}


void GestionEmploye::on_pushButton_refuser_conge_clicked()
{




    int difference = c2.solde(c2.get_cin()) + c2.get_debut().daysTo(c2.get_fin())  ;

    bool test=c2.modifierById(c2.get_id(),"refuse",difference);

    if(test)
    {

        ui->pushButton_accepter_conge->setEnabled(true) ;
        ui->pushButton_refuser_conge->setEnabled(false) ;



        ui->table_conge->setModel(c.afficher());
        ui->tab_consulter_cong->setModel(c.afficherCongeByCin(e.get_cin())) ;

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}





void GestionEmploye::on_pushButton_accepter_conge_clicked()
{
    //  conge c ;
    int difference ;
    if (c2.get_status()=="refuse")
    {  difference = c2.solde(c2.get_cin()) - c2.get_debut().daysTo(c2.get_fin())  ; }
    else
    {difference = 0 ;}

    bool test=c2.modifierById(c2.get_id(),"accepte",difference);

    if(test)
    {
        ui->table_conge->setModel(c.afficher());
        ui->tab_consulter_cong->setModel(c.afficherCongeByCin(e.get_cin())) ;

        ui->pushButton_accepter_conge->setEnabled(false) ;
        ui->pushButton_refuser_conge->setEnabled(true) ;

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void GestionEmploye::on_table_conge_activated(const QModelIndex &index)
{


    int id_conge = ui->table_conge->model()->data(ui->table_conge->model()->index(index.row() ,3)).toInt() ;
    QDate debut = QDate(  ui->table_conge->model()->data(ui->table_conge->model()->index(index.row() ,1)).toDate() );
    QDate fin = QDate(  ui->table_conge->model()->data(ui->table_conge->model()->index(index.row() ,2)).toDate() );
    int cin = ui->table_conge->model()->data(ui->table_conge->model()->index(index.row() ,0)).toInt() ;
    QString status = ui->table_conge->model()->data(ui->table_conge->model()->index(index.row() ,4)).toString() ;
    c2 =  conge (cin,debut,fin,status,id_conge) ;


    if (status=="refuse")
    {
        ui->pushButton_accepter_conge->setEnabled(true) ;


        ui->pushButton_refuser_conge->setEnabled(false) ;
    }
    else if ( status == "accepte")
    {
        ui->pushButton_accepter_conge->setEnabled(false) ;
        ui->pushButton_refuser_conge->setEnabled(true) ;
    }else
    {
        ui->pushButton_accepter_conge->setEnabled(true) ;
        ui->pushButton_refuser_conge->setEnabled(true) ;
    }





}


void GestionEmploye::on_lineEdit_5_textChanged(const QString &arg1)
{

    ui->table_employe->setModel(e.rechercher(arg1));

}

void GestionEmploye::on_pushButton_demanddereduction_clicked()
{

    int test=e.reduction();

    QString t;
    if (test>0)
    { t = " tu as droit à droit " ;
        t.append(QString::number(test)).append(" % de réduction \n tu as ") ;
        A.write_to_arduino(("1"));

    }
    else
    { t = " tu n'as pas droit à une réduction \n tu n'as que " ;
     A.write_to_arduino(("0"));
    }

    t.append(QString::number(e.get_nb_heures()+e.get_nb_heures_suppl())).append( " heures valables ") ;
    QMessageBox msgBox;
    msgBox.setText(t);
    msgBox.exec();

    /* ui->table_conge->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr(), QMessageBox::Cancel);
    */
}





void GestionEmploye::on_pageee_currentChanged(int index)
{
    int temp = c.solde(e.get_cin()) ;
    ui->lblConge->setText(QString::number(temp));
    ui->table_employe->setModel(e.afficher());
    ui->tab_consulter_cong->setModel(c.afficherCongeByCin(e.get_cin())) ;
    ui->table_conge->setModel(c.afficher());

    e.setdroit_conge(c.solde(e.get_cin())) ;
}

void GestionEmploye::on_pb_verify_clicked()
{

             A.write_to_arduino(("1"));

}


void GestionEmploye::on_pushButtonHomeGestEmp_clicked()
{
    Menu *m = new Menu ;
    m->setEmploye(e) ;
    m->show() ;
    this->hide() ;
}
