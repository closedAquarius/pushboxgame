#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class Music;
}

class Music : public QWidget
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = nullptr);
    ~Music();

private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_choose_clicked();

    void on_plus_clicked();

private:
    Ui::Music *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
};

#endif // MUSIC_H
