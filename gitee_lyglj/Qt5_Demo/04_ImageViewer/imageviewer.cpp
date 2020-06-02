#include "imageviewer.h"
#include "ui_imageviewer.h"

#include <QDebug>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>

#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#include <QPainter>
#endif

ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::on_action_exit_triggered()
{
    this->close ();
}

void ImageViewer::on_action_Open_triggered()
{
    qDebug() << "open()";
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),QDir::currentPath());
    if(!fileName.isEmpty())
    {
        QImage image(fileName);
        if(image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));

            return;
        }

        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        ui->action_Print->setEnabled(true);
        ui->action_fitToWindow->setEnabled(true);
        updateActions ();

        if(!ui->action_fitToWindow->isChecked())
        {
            imageLabel->adjustSize();
        }
    }
}

void ImageViewer::on_action_ZoomIn_triggered()
{
    scaleImage (1.25);
}

void ImageViewer::on_action_ZoomOut_triggered()
{
    scaleImage (0.8);
}

void ImageViewer::on_action_NormalSize_triggered()
{
    imageLabel->adjustSize ();
    scaleFactor = 1.0;
}


void ImageViewer::updateActions ()
{
    ui->action_ZoomIn->setEnabled (!ui->action_fitToWindow->isChecked ());
    ui->action_ZoomOut->setEnabled (!ui->action_fitToWindow->isChecked ());
    ui->action_NormalSize->setEnabled (!ui->action_fitToWindow->isChecked ());
}

void ImageViewer::scaleImage (double factor)
{
    Q_ASSERT(imageLabel->pixmap ());
    scaleFactor *= factor;
    imageLabel->resize (scaleFactor * imageLabel->pixmap ()->size ());

    adjustScrollBar (scrollArea->horizontalScrollBar (), factor);
    adjustScrollBar (scrollArea->verticalScrollBar (), factor);

    ui->action_ZoomIn->setEnabled (scaleFactor < 3.0);
    ui->action_ZoomOut->setEnabled (scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar (QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue (int(factor * scrollBar->value ()
                             + ((factor - 1) * scrollBar->pageStep ()/2)));
}


void ImageViewer::on_action_fitToWindow_triggered()
{
    bool fitToWindow = ui->action_fitToWindow->isChecked ();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
    {
        on_action_NormalSize_triggered();
    }
    updateActions();
}

void ImageViewer::on_action_Print_triggered()
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void ImageViewer::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<b>Image Viewer</b> example."));
}

void ImageViewer::on_action_AboutQt_triggered()
{
    qApp->aboutQt ();
}
