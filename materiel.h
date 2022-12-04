#ifndef MATERIEL_H
#define MATERIEL_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class materiel
{

public:
    void setcode(int );
    void settypedemateriel(QString );
    void setcouleur(QString );
    void setcategorie(QString );

    int get_code();
    QString get_typedemateriel();
    QString get_couleur();
    QString get_categorie();

    materiel();
    materiel(int,QString,QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * recherche(QString);

    QSqlQueryModel* tri();

private:
    QString typedemateriel,couleur,categorie;
    int code;

};

#endif // MATERIEL_H
