#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hexstring.hpp"
#include "imageproc.hpp"

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <QtGui>
#include <QPixmap>
#include <QHBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QGridLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QAbstractButton>

#include <QFileDialog>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QGraphicsScene>
#include <list>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


typedef struct imageData{
    double value;
    cv::Mat img;
    QLabel* container;

    /*!
     * \brief imageData
     * \param _img
     * \param _cont
     * \param _val
     */
    imageData(cv::Mat _img, QLabel* _cont, double _val) : value(_val), img(_img), container(_cont)
    {
    }
}imageData;

namespace Ui {
    class MainWindow;
}

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFolder_clicked();

    void on_action_Open_Folder_triggered();

    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void swapWidgets(QWidget *widgetA, QWidget *widgetB);

    void analyze(Vec3b color);

    Vec3b setColor(QString color);

private:
    Ui::MainWindow *ui;
    //cv::Mat image[300];
    QLabel* container[300];
    list<imageData*> imageList;
};

/*
   Functions to convert between OpenCV's cv::Mat and Qt's QImage and QPixmap.

   Andy Maloney
   23 November 2013
   http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
 */

namespace ASM {
   inline QImage  cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }

   inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
   {
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
   }
}

#endif // MAINWINDOW_H
