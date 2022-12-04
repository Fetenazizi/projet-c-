#ifndef EMPLOYE_H
#define EMPLOYE_H


#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>
#include<QMainWindow>




class employe
{
public:
    void setcin(int);
    void setprenom(QString);
    void setnom(QString);
    void setposte(QString);
    void setsalaire(int);
    void setdroit_conge(int);
    void setnb_heures(int);
    void setnb_heures_suppl(int);

    int get_cin();
    QString get_prenom();
    QString get_nom();
    QString get_poste();
    int get_salaire();
    int get_droit_conge();
    int get_nb_heures();
    int get_nb_heures_suppl();

    employe();
    employe(int, QString, QString,QString,int,int,int,int);
    int  getSalireByInterval(int debut , int fin) ;
    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer (int cin);
    employe getEmployeByCin(int cin) ;
    QSqlQueryModel* rechercher (QString aux);
    QSqlQueryModel* tri_poste();
    int reduction();
private:
    QString poste, nom ,prenom ;
    int cin, salaire,droit_conge,nb_heures,nb_heures_suppl;
};

#endif // EMPLOYE_H
