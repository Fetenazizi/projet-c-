#include "gestionmateriel.h"
#include "ui_gestionmateriel.h"
#include "materiel.h"
#include "menu.h"
#include <QMessageBox>
#include<QIntValidator>
#include<QSortFilterProxyModel>
#include <QMessageBox>
#include<QPainter>
#include<QImage>
#include <QPdfWriter>
#include<QDesktopServices>
#include <QUrl>
#include<QPieSeries>
#include<QChartView>
#include<QtCharts>



GestionMateriel::GestionMateriel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionMateriel)
{
    ui->setupUi(this);
    ui->lineEdit_code->setValidator(new QIntValidator(0,9999,this));

 //   ui->setupUi(this);
    ui->tableView->setModel(mp.afficher());
    QPieSeries *series=new QPieSeries() ;
         series->append(" plus que 5",10);
         series->append(" plus que 10",15);
         series->append(" plus que 15",25);
         series->append(" plus que 20",50);


            QPieSlice  *slize =series->slices().at(1);

            slize->setExploded(true);


            QChart *chart=new  QChart ();
            chart ->addSeries(series);
            chart->setTitle("materiels plus utilisees");
            QChartView * chartview = new QChartView (chart);
            chartview->setParent(ui->horizontalFrame);
int ret=A.connect_arduino();
switch(ret){
  case(0):qDebug()<<"arduino is available and connected to:"<< A.getarduino_port_name();
    break;
   case(1):qDebug()<<"arduino is available and not connected to:"<< A.getarduino_port_name();
     break;
   case(-1):qDebug()<<"arduino is not available";

}

}

GestionMateriel::~GestionMateriel()
{
    delete ui;
}


void GestionMateriel::on_on_pushButton_ajouter_clicked_clicked()
    {
  int code=ui->lineEdit_code->text().toInt();
    QString typedemateriel=ui->lineEdit_type->text();
    QString couleur=ui->lineEdit_couleur->text();
    QString categorie=ui->lineEdit_categorie->text();

    materiel m(code,typedemateriel,couleur,categorie);
    bool test=m.ajouter();
    if(test)
    {
        ui->tableView->setModel(mp.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr ("ajout effectue\n""Click Cancel to exit."),QMessageBox::Cancel);
         ui->tableView->setModel(mp.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                              QObject::tr ("ajout non effectué.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void GestionMateriel::on_pushButton_3_clicked()
{
    int code=ui->lineEdit->text().toInt();
    bool test=mp.supprimer(code);
    if (test)
    {
        ui->tableView->setModel(mp.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr ("suppression effectue\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not OK"),QObject::tr ("suppression non effectué.\n""Click Cancel to exit."),QMessageBox::Cancel);

}



void GestionMateriel::on_modifier_clicked()
{
    int code=ui->lineEdit_code->text().toInt();
           QString typedemateriel=ui->lineEdit_type->text();
           QString couleur=ui->lineEdit_couleur->text();
           QString  categorie=ui->lineEdit_categorie->text();


           materiel m (code,typedemateriel,couleur,categorie);

           bool test=m.modifier();

           if(test)
           {
               ui->tableView->setModel(mp.afficher());
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




void GestionMateriel::on_pushButton_2_clicked()//recherche
{


       QString aux=ui->lineEdit->text();
       ui->tableView->setModel(mp.recherche(aux));


 }
void GestionMateriel::setEmploye(employe e)
{
    this->e = e ;
}

void GestionMateriel::on_pushButton_clicked()//pdf
{

    QPdfWriter pdf("Liste.pdf");

                        QPainter painter(&pdf);

                        int i = 4000;
                        painter.setPen(Qt::red);
                        painter.setFont(QFont("Helvetica", 30));
                        painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/nourhammemi/OneDrive/Bureau/ProjetCpp/Entite_/employe.png"));
                        painter.drawText(3000,1500,"LISTE DE MATERIELS");
                        painter.setPen(Qt::red);
                        painter.setFont(QFont("Helvetica ulta light", 50));
                        painter.drawRect(2700,200,6300,2600);
                        painter.drawRect(0,3000,9600,500);
                        painter.setPen(Qt::black);
                        painter.setFont(QFont("Helvetica", 9));
                        painter.drawText(300,3300,"code");
                        painter.drawText(2300,3300,"type de materiel");
                        painter.drawText(4300,3300,"couleur");
                        painter.drawText(6000,3300,"categorie");

                        QSqlQuery query;
                        query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
                        time_t tt;
                        struct tm* ti;
                        time(&tt);
                        ti=localtime(&tt);
                        asctime(ti);
                        painter.drawText(500,300, asctime(ti));
                        query.prepare("select * from materiel");
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






void GestionMateriel::on_pb_trier_clicked()
{

         ui->tableView->setModel(mp.tri());

}


void GestionMateriel::on_pushButton_4_clicked()
{
  A.write_to_arduino(("0"));
}

void GestionMateriel::on_pushButton_5_clicked()
{
   A.write_to_arduino(("1"));
}

void GestionMateriel::on_pushButton_6_clicked()
{
    int nbr= ui->nbr_voitures->text().toInt();

    if (nbr>30)
    {
        A.write_to_arduino(("1"));
    }
    else if (nbr>=30)
    {
        A.write_to_arduino(("0"));
    }

}

void GestionMateriel::on_pushButtonhomeMateriel_clicked()
{
    Menu *m = new Menu ;
    m->setEmploye(e) ;
    m->show() ;
    this->hide() ;
}

