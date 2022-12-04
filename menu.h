#ifndef MENU_H
#define MENU_H

#include"employe.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
  void  setEmploye(employe e) ;
    ~Menu();

private slots:
  void on_pushButto_GestionEmp_clicked();

  void on_pushButton_GestionMAt_clicked();

private:
    Ui::Menu *ui;
    employe e ;
};
#endif // MENU_H
