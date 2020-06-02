/**
 * @file convert.cpp
 * @brief cv::Mat 与 QImage 之间的转换函数
 */
#include "convert.h"

#include "opencv2/imgproc/imgproc.hpp"

QImage cvMat2QImage(const cv::Mat& mat, bool clone, bool rb_swap)
{
    qDebug("type(%d) size(%d, %d)", mat.type(), mat.cols, mat.rows);
    const uchar *pSrc = (const uchar*)mat.data;
    if(mat.type() == CV_8UC1) {
        // 8-bits unsigned, NO. OF CHANNELS = 1
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(pSrc, mat.cols, mat.rows, QImage::Format_Grayscale8);
        if(clone) {
            return image.copy();
        }
        return image;
#else
        QImage image(pSrc, mat.cols, mat.rows, QImage::Format_Indexed8);
        QVector<QRgb> grayTable;
        for(int i = 0; i < 256; i++) {
            grayTable.push_back(qRgb(i,i,i));
        }
        image.setColorTable(grayTable);
        return image;
#endif
    } else if(mat.type() == CV_8UC3) {
        // 8-bits unsigned, NO. OF CHANNELS = 3
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        if(clone) {
            if(rb_swap) {
                return image.rgbSwapped();
            }
            return image.copy();
        } else {
            if(rb_swap) {
                cv::cvtColor(mat, mat, CV_BGR2RGB);
            }
            return image;
        }
    } else if(mat.type() == CV_8UC4) {
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        if(clone) {
            return image.copy();
        }
        return image;
    } else {
        qWarning("ERROR: Mat could not be converted to QImage.\n");
        return QImage();
    }
}

cv::Mat QImage2cvMat(QImage &image, bool clone, bool rb_swap)
{
    cv::Mat mat;
    switch(image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
        if(clone) {
            mat = mat.clone();
        }
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine());
        if(clone) {
            mat = mat.clone();
        }
        if(rb_swap) {
            cv::cvtColor(mat, mat, CV_BGR2RGB);
        }
        break;
    case QImage::Format_Indexed8:
//    case QImage::Format_Grayscale8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void *)image.bits(), image.bytesPerLine());
        if(clone) {
            mat = mat.clone();
        }
        break;
    }
    return mat;
}
