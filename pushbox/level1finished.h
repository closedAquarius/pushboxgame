#ifndef LEVEL1FINISHED_H
#define LEVEL1FINISHED_H

#include <QWidget>
#include <QTime>

namespace Ui {
class Level1Finished;
}

class Level1Finished : public QWidget
{
    Q_OBJECT

public:
    explicit Level1Finished(int a,QWidget *parent = nullptr);
    ~Level1Finished();
    void setText(int step,QTime *timeRecord);
    void setbtn();

private slots:
    void on_btnback_clicked();
    void on_btnagain_clicked();

    void on_btnnextlevel_clicked();

signals:
    void backtogamelevel();
    void level1again();
    void level1next();
private:
    Ui::Level1Finished *ui;
};

#endif // LEVEL1FINISHED_H
