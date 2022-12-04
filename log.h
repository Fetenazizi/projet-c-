#ifndef LOG_H
#define LOG_H

#include <QDialog>

namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = nullptr);
    ~Log();

private slots:
    void on_btn_log_clicked();

private:
    Ui::Log *ui;
};

#endif // LOG_H
