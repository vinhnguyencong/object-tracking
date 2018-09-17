#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void detector(QString videoPath);

private slots:
    void on_browseVideoPushButton_pressed();

    void on_playVideoPushButton_pressed();

    void on_trackingObj_1_PushButton_pressed();

    void on_trackingObj_2_PushButton_pressed();

    void on_trackingObj_3_PushButton_pressed();

    void on_trackingObj_4_PushButton_pressed();

    void on_trackingObj_5_PushButton_pressed();

    void on_thresholdHorizontalSlider_valueChanged(int value);

private:
    Ui::Widget *ui;

//protected:
//    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
