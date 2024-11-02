#ifndef CUSTOM_H
#define CUSTOM_H

#include <QWidget>

namespace Ui {
class Custom;
}

class Custom : public QWidget
{
    Q_OBJECT

public:
    explicit Custom(QWidget *parent = nullptr);
    ~Custom();
    void setmap(int(*map)[8]);
    void cleartext();

private slots:
    void on_create_clicked();

    void on_toclevel_clicked();

signals:
    void create();
    void toclevel();

public:
    Ui::Custom *ui;
};

#endif // CUSTOM_H
