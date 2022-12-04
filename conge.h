#ifndef CONGE_H
#define CONGE_H

#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QDate>
#include<QMessageBox>
#include<QMainWindow>
class conge
{
public:

    void setcin(int);
    void setstatus(QString);
    int get_cin();
    QString get_status();
    QDate get_debut() ;
    QDate get_fin() ;
    int get_id() ;

    conge();
    conge(int,QDate,QDate,QString) ;
    conge(int,QDate,QDate,QString,int) ;

    bool ajouter(int difference);
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer (int id);
    int solde(int cin) ;
    bool modifierById(int id, QString status, int difference) ;
    QSqlQueryModel * afficherCongeByCin(int cin) ;
private :
    int cin ,id ;
    QString status;
    QDate debut , fin ;
};

#endif // CONGE_H
