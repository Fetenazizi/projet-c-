#include "menu.h"
#include "ui_menu.h"
#include "gestionemploye.h"
#include "gestionmateriel.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

void Menu::setEmploye(employe e) {
    this->e = e ;

}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_pushButto_GestionEmp_clicked()
{
    GestionEmploye *w = new GestionEmploye ;
    w->setEmploye(e) ;
    w->show();
    this->hide() ;
}

void Menu::on_pushButton_GestionMAt_clicked()
{
    GestionMateriel *m = new GestionMateriel ;

     m->setEmploye(e) ;
     m->show() ;
    this->hide() ;
}
