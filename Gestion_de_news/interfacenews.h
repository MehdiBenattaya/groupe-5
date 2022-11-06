#ifndef INTERFACENEWS_H
#define INTERFACENEWS_H

#include <QDialog>

namespace Ui {
class InterfaceNews;
}

class InterfaceNews : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceNews(QWidget *parent = nullptr);
    ~InterfaceNews();

private:
    Ui::InterfaceNews *ui;
};

#endif // INTERFACENEWS_H
