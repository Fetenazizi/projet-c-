#include "employe.h"
#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<iostream>
#include <QSqlQueryModel>

using namespace std;

employe::employe(int cin , QString nom , QString prenom , QString poste ,  int salaire, int droit_conge,int nb_heures, int nb_heures_suppl)
{
    this->cin=cin;
    this->prenom=prenom;
    this->nom=nom;
    this->poste=poste;
    this->salaire=salaire;
    this->droit_conge=droit_conge;
    this->nb_heures=nb_heures;
    this->nb_heures_suppl=nb_heures_suppl;

}

employe::employe()
{

}
QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("poste"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("droit_conge"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("nb_heures"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("nb_heures_suppl"));

    return model;
}
int employe::   getSalireByInterval(int debut , int fin)
{

    QSqlQuery query;
    QString res=QString::number(cin);


    query.prepare(" select COUNT(*)  from  employe where salaire > :debut and salaire <:fin");

    query.bindValue(":debut", debut);
    query.bindValue(":fin", fin);
    query.exec() ;

    while (query.next()) {
        return query.value(0).toInt();
    }
}



employe employe::getEmployeByCin(int cin)
{

    QSqlQuery query;
    QString res=QString::number(cin);
    employe e ;

    query.prepare("select * from employe where cin = :cin");

    query.bindValue(":cin", res);
    query.exec() ;

    while (query.next()) {

        int cin = query.value(0).toInt();
        QString nom  = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString poste = query.value(3).toString() ;
        int salaire = query.value(4).toInt();
        int droit_conge = query.value(5).toInt();
        int nb_heures = query.value(6).toInt();
        int nb_heures_suppl = query.value(7).toInt() ;

        employe e ( cin , nom , prenom , poste , salaire, droit_conge, nb_heures,  nb_heures_suppl) ;
        return e ;

    }

    return e ;
}

bool employe::ajouter ()
{
    QSqlQuery query;
    QString res=QString::number(cin);
    QString res1=QString::number(salaire);
    QString res2=QString::number(droit_conge);
    QString res3=QString::number(nb_heures);
    QString res4=QString::number(nb_heures_suppl);




    query.prepare("INSERT INTO employe (cin,nom,prenom,poste,salaire,droit_conge,nb_heures,nb_heures_suppl) VALUES (:cin, :nom, :prenom, :poste, :salaire, :droit_conge,:nb_heures,:nb_heures_suppl)");

    query.bindValue(":cin", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", res1);
    query.bindValue(":droit_conge", res2);
    query.bindValue(":nb_heures", res3);
    query.bindValue(":nb_heures_suppl", res4);




    return query.exec();
}





bool employe::supprimer (int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);

    query.prepare("Delete from employe where cin= :cin");
    query.bindValue(":cin",res);

    return query.exec();
}
bool employe::modifier()
{
    QSqlQuery query;
    QString res=QString::number(cin);
    QString res1=QString::number(salaire);
    QString res2=QString::number(droit_conge);
    QString res3=QString::number(nb_heures);
    QString res4=QString::number(nb_heures_suppl);



    query.prepare("Update EMPLOYE Set CIN='"+res+"', NOM='"+nom+"', PRENOM='"+prenom+"', POSTE='"+poste+"',SALAIRE='"+res1+"', DROIT_CONGE='"+res2+"', nb_heures='"+res3+"' ,nb_heures_suppl='"+res4+"' where CIN='"+res+"' ");

    return query.exec();
}

QSqlQueryModel *employe::tri_poste()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  employe ORDER BY poste asc");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));

    return model;
}


QSqlQueryModel* employe ::rechercher (QString aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;



    model->setQuery("select * from employe where ((cin||nom||prenom||poste||salaire||droit_conge||nb_heures||nb_heures_suppl) LIKE '%"+aux+"%')");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("droit_conge"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heures"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("nb_heures_suppl"));



    return model;

}

int employe::reduction()
{

    int x=(nb_heures + nb_heures_suppl);


    if (x>120 && x<180)
    {   return 30 ;   }
    else  if (x>=180)
    { return 50; }
    else
    {return 0 ;}

}


void employe::setcin(int cin){ this->cin=cin; }
void employe::setprenom(QString prenom){ this->prenom=prenom; }
void employe::setnom(QString nom){ this->nom=nom; }
void employe::setposte(QString poste){ this->poste=poste; }
void employe::setsalaire(int salaire){ this->salaire=salaire; }
void employe::setdroit_conge(int droit_conge){ this->droit_conge=droit_conge; }
void employe::setnb_heures(int nb_heures ){ this->nb_heures=nb_heures; }
void employe::setnb_heures_suppl(int nb_heures_suppl){ this->nb_heures_suppl=nb_heures_suppl; }

int  employe::get_salaire(){return salaire ;}
int  employe::get_droit_conge(){return droit_conge;}
int  employe::get_cin(){return cin ;}
QString employe::get_prenom(){return prenom ;}
QString employe::get_nom(){return nom ;}
QString employe::get_poste(){return poste ;}
int employe::get_nb_heures(){return nb_heures ;}
int employe::get_nb_heures_suppl(){return nb_heures_suppl;}




