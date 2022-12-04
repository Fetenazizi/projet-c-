#include "conge.h"
#include "conge.h"
#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>
#include<iostream>
using namespace std;
conge::conge()
{
}

conge::conge(int cin , QDate debut , QDate fin , QString status)
{
    this->cin=cin;
    this->debut=debut ;
    this->fin =fin ;
    this->status=status ;
}

conge::conge(int cin , QDate debut , QDate fin , QString status, int id)
{
    this->cin=cin;
    this->debut=debut ;
    this->fin =fin ;
    this->status=status ;
    this->id = id ;
}

QSqlQueryModel * conge::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from conge");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("detbut"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("fin"));
    model->setHeaderData( 3,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData( 4,Qt::Horizontal,QObject::tr("status"));
    return model;
}

QSqlQueryModel * conge::afficherCongeByCin(int cin)
{

    QSqlQueryModel * model=new QSqlQueryModel();


    QSqlQuery query;
    QString res=QString::number(cin);



    model->setQuery("select date_depart,date_fin,status from conge where cin = "+res);

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("debut"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("fin"));

    model->setHeaderData( 2,Qt::Horizontal,QObject::tr("status"));
    return model;
}


int conge::solde(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);


    query.prepare("select droit_conge from employe where cin = :cin");

    query.bindValue(":cin", res);
    query.exec() ;
    int solde ;
    while (query.next()) {

        solde = query.value(0).toInt();



    }
    return solde ;
}


bool conge::ajouter (int difference)
{




    if ( debut.daysTo(fin) <= 0 )
    { QMessageBox::critical(nullptr, QObject::tr("not OK"),
                            QObject::tr("Date Fin > Date debut .\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false ;}
    if ( difference < 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("Solde de conge insufisant.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false ;
    } else {




        QSqlQuery query;
        QString res=QString::number(cin);
        QString res1= this->debut.toString("yyyy-MM-dd");
        QString res2=this->fin.toString("yyyy-MM-dd");

        query.prepare("INSERT INTO conge (cin,date_depart,date_fin,status) VALUES (:cin, TO_DATE(:date_debut, 'YYYY-MM-DD'), TO_DATE(:date_fin, 'YYYY-MM-DD'),:status)");

        query.bindValue(":cin", res);

        query.bindValue(":date_debut", res1);
        query.bindValue(":date_fin", res2);
        query.bindValue(":status","attente");
        query.exec() ;
        QString res3=QString::number(difference);
        query.prepare("update employe SET droit_conge= :droit where cin = :cinn") ;
        query.bindValue(":cinn", res);
        query.bindValue(":droit" , res3 ) ;

        return query.exec();



    }
}





bool conge::supprimer (int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from conge where id= :id");
    query.bindValue(":id",res);

    return query.exec();
}

bool conge::modifier()
{
    QSqlQuery query;
    QString res=QString::number(cin);
    QString res1= this->debut.toString("yyyy-MM-dd");
    QString res2=this->fin.toString("yyyy-MM-dd");


    query.prepare("Update conge Set CIN='"+res+"', DEBUT='"+res1+"', FIN='"+res2+"' where CIN='"+res+"' ");

    return query.exec();
}


bool conge::modifierById(int id, QString status ,int difference)
{
    QSqlQuery query;
    QString res=QString::number(id);

    QString res3=QString::number(difference);

    if (difference > 0)
    {
        QString res2=QString::number(id);
        query.prepare("Update employe SET droit_conge= :droit where cin = :cinn") ;
        query.bindValue(":cinn", cin);
        query.bindValue(":droit" , res3 ) ;
        cout<< query.executedQuery().toStdString()<<" / "<<difference  << " / " << cin <<endl ;
        query.exec();

    }

    query.prepare("Update conge Set status='"+status+"'where ID='"+res+"' ");


    return query.exec();

}


int conge::get_cin(){
    return this->cin ;
}

QDate conge::get_fin()
{
    return this->fin ;
}

QDate conge::get_debut()
{
    return this->debut ;
}

int conge::get_id()
{return this->id ; }
QString conge::      get_status()
{
    return this->status ;

}



