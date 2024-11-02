#include "music.h"
#include "ui_music.h"
#include <QFileDialog>
#include <QMessageBox>

Music::Music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);
    this->setWindowTitle("music");

    QPixmap music;
    music.load(":/image/musicback.png");
    music=music.scaled(ui->label->geometry().size());
    ui->label->setPixmap(music);
    ui->label->lower();
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    // 设置播放列表
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile("D:/programstudy/Qt/pushbox/music/music1.mp3")));
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile("D:/programstudy/Qt/pushbox/music/music2.mp3")));
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile("D:/programstudy/Qt/pushbox/music/music3.mp3")));
    player->setPlaylist(playlist);
    player->setVolume(100);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    // 开始播放s
    player->play();
    ui->btn1->setEnabled(false);
    ui->btn2->setEnabled(true);
    ui->plus->setEnabled(false);

    ui->volume->setRange(0, 100);
    connect(ui->volume, &QSlider::valueChanged,
                         [=](int volume) {
            player->setVolume(volume);
        });
}

Music::~Music()
{
    delete ui;
}

void Music::on_btn1_clicked()
{
    player->play();
    ui->btn1->setEnabled(false);
    ui->btn2->setEnabled(true);
}

void Music::on_btn2_clicked()
{
    player->stop();
    ui->btn1->setEnabled(true);
    ui->btn2->setEnabled(false);
}

void Music::on_choose_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(nullptr,
                                                        "选择MP3文件",
                                                        "",
                                                        "MP3 Files (*.mp3)");
    if(!file_path.isEmpty())
    {
        ui->lineEdit->setText(file_path);
        ui->plus->setEnabled(true);
    }
}

void Music::on_plus_clicked()
{
    QString file_path=ui->lineEdit->text();
    for(int i=0;i<file_path.length();i++)
    {
        if(file_path[i]=='\\')
        {
            file_path[i]='/';
        }
    }
    playlist->insertMedia(0,QMediaContent(QUrl::fromLocalFile(file_path)));
    QMessageBox::information(this,"提示","您已添加成功");
    ui->plus->setEnabled(false);
}
