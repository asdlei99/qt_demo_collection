#ifndef QSOUNDWGT_H
#define QSOUNDWGT_H

#include <QWidget>
#include <QSound>

namespace Ui {
class QSoundWgt;
}

class QSoundWgt : public QWidget
{
    Q_OBJECT

public:
    explicit QSoundWgt(QWidget *parent = 0);
    ~QSoundWgt();

    //初始化背景音乐
    void initSounds();
private slots:
    void on_bgmBtn_clicked();

    void on_passBtn_clicked();

    void on_playBtn_clicked();

    void on_recommendBtn_clicked();

    void on_zeorPartBtn_clicked();

    void on_onePartBtn_clicked();

    void on_twoPartBtn_clicked();

    void on_threePartBtn_clicked();

private:
    Ui::QSoundWgt *ui;

private:
    //管理背景音效 可重复播放
    QSound * bgmSound;
    //背景音效是否正在播放
    bool isBgmSoundActive =true;

};

#endif // QSOUNDWGT_H
