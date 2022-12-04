#include "materiel.h"
#include <QString>
#include <QSqlQuery>
#include<QObject>
#include<QtDebug>

materiel::materiel()
{
    code=0;
    typedemateriel=" ";
    couleur=" ";
    categorie=" ";
}

materiel::materiel(int code,QString typedemateriel,QString couleur,QString categorie)
{
this->code=code;
this->typedemateriel=typedemateriel;
this->couleur=couleur;
this->categorie=categorie;
}
    int materiel::get_code(){return code;}
    QString materiel::get_typedemateriel(){return typedemateriel;}
    QString materiel::get_couleur(){return couleur;}
    QString materiel::get_categorie(){return categorie;}
    void materiel::setcode(int code){this->code=code;}
    void materiel::settypedemateriel(QString typedemateriel){this->typedemateriel=typedemateriel;}
    void materiel::setcouleur(QString couleur){this->couleur=couleur;}
    void materiel::setcategorie(QString categorie){this->categorie=categorie;}




bool materiel::ajouter()
{
  QSqlQuery query;

  QString code_string=QString::number(code);

  query.prepare("INSERT INTO MATERIEL (CODE,TYPEDEMATERIEL,COULEUR,CATEGORIE)" "values(:code, :typedemateriel, :couleur, :categorie)");

  query.bindValue(":code", code_string);
  query.bindValue(":typedemateriel", typedemateriel);
  query.bindValue(":couleur", couleur);
  query.bindValue(":categorie", categorie);

  return  query.exec();
}

 QSqlQueryModel * materiel ::afficher()
 {
     QSqlQueryModel *model=new QSqlQueryModel();

     model->setQuery("select * from materiel");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("Code"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Typedemateriel"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Couleur"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Categorie"));

     return model;

 }


bool materiel::supprimer(int code)
{

    QSqlQuery query;
    QString code_string=QString::number(code);

    query.prepare("Delete from materiel where CODE=:cod");
    query.bindValue(":cod",code);
    return  query.exec();

}




bool materiel::modifier()
{
    QSqlQuery query;
    QString code_string=QString::number(code);

 query.prepare("Update MATERIEL Set CODE='"+code_string+"', TYPEDEMATERIEL='"+typedemateriel+"', COULEUR='"+couleur+"', CATEGORIE='"+categorie+"' where CODE='"+code_string+"' ");

 return query.exec();
}

QSqlQueryModel* materiel ::recherche (QString aux)

{
    QSqlQuery query;

    QSqlQueryModel* model = new QSqlQueryModel();




    model->setQuery("select * from materiel where ((code||typedemateriel||couleur||categorie) LIKE '%" +aux+ "%')");

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("typedemateriel"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("couleur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie"));



    return model;

}
QSqlQueryModel * materiel::tri()
  {
      QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("select * from  materiel ORDER BY CODE");

      model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("typedemateriel"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("couleur"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie"));

 return model;
  }

