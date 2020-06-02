#include "qsoundwgt.h"
#include "ui_qsoundwgt.h"

QSoundWgt::QSoundWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSoundWgt)
{
    ui->setupUi(this);
    this->initSounds();
}


QSoundWgt::~QSoundWgt()
{
    delete ui;
}
//初始化音效
void QSoundWgt::initSounds()
{
    QString filename(":/src/bgm.wav");
    bgmSound=new QSound(filename,this);
    bgmSound->play();
    bgmSound->setLoops(-1);
}

void QSoundWgt::on_bgmBtn_clicked()
{
    //如果是播放状态 则停止播放，如果是未播放状态就开始播放 并无限循环
    if(isBgmSoundActive){
        bgmSound->stop();
        delete bgmSound;
    }else{
        initSounds();
    }
    isBgmSoundActive =!isBgmSoundActive;
}

void QSoundWgt::on_passBtn_clicked()
{
    QSound::play(":/src/pass.wav");
}
void QSoundWgt::on_onePartBtn_clicked()
{
    QSound::play(":/src/Rob1.wav");
}

void QSoundWgt::on_twoPartBtn_clicked()
{
    QSound::play(":/src/Rob2.wav");
}

void QSoundWgt::on_threePartBtn_clicked()
{
    QSound::play(":/src/Rob3.wav");
}

void QSoundWgt::on_playBtn_clicked()
{
    //QSound::play(":/src/play.wav");
}

void QSoundWgt::on_recommendBtn_clicked()
{
    //QSound::play(":/src/recommend.wav");
}

void QSoundWgt::on_zeorPartBtn_clicked()
{
    //QSound::play(":/src/zeorPart.wav");
}

