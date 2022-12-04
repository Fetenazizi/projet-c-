#include "log.h"
#include "ui_log.h"
#include "menu.h"
#include "employe.h"
#include "gestionemploye.h"
#include "iostream"
using namespace std;
Log::Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
}

Log::~Log()
{
    delete ui;
}

void Log::on_btn_log_clicked()
{


    employe e ;
    e = e.getEmployeByCin(ui->LE_cin->text().toInt()) ;
    if (e.get_nom() !="" )
    {

        Menu *m = new Menu ;
        m->setEmploye(e) ;
        m->show();
        this->hide() ;


    }
    else {
        {
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                  QObject::tr("Verifiez vos informations.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}
