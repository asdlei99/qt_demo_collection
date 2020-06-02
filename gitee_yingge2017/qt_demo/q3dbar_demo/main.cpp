#include <QGuiApplication>
#include <QtDataVisualization>
#include <qdebug.h>

using namespace QtDataVisualization;

int main(int argc,char **argv){
    QGuiApplication app(argc,argv);

    qDebug()<<"q3dbar main";

    Q3DBars bars;
    bars.setWidth(666);
    bars.setHeight(666);
    bars.setFlags(bars.flags() ^ Qt::FramelessWindowHint);
    bars.rowAxis()->setRange(0, 4);
    bars.columnAxis()->setRange(0, 4);

    for(int i = 0;i<5;i++){
        QBar3DSeries *series = new QBar3DSeries;
        QBarDataRow *data = new QBarDataRow;
        *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
        series->dataProxy()->addRow(data);
        bars.addSeries(series);
    }

    bars.show();

    return app.exec();

}
