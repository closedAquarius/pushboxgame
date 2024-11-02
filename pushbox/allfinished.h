#ifndef ALLFINISHED_H
#define ALLFINISHED_H

#include <QWidget>
#include <QTime>

namespace Ui {
class AllFinished;
}

class AllFinished : public QWidget
{
    Q_OBJECT

public:
    explicit AllFinished(QWidget *parent = nullptr);
    ~AllFinished();
    void setText(int step,QTime *timeRecord);

private slots:
    void on_back_clicked();

    void on_again_clicked();

signals:
    void backtogamelevel();
    void level1again();

private:
    Ui::AllFinished *ui;
};

#endif // ALLFINISHED_H
