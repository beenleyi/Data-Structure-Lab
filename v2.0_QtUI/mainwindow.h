#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qdebug.h>
#include <QMainWindow>
#include <qradiobutton.h>
#include <qstring.h>
#include "struct.h"
#include <qtextstream.h>
#include <qpixmap.h>
#include <qpointer>
#include <qpainter.h>
#include <qrect.h>
#include <qgraphicsview.h>
#include <qtimer.h>
#include <windows.h>
#include <time.h>
#include <qgraphicsitem.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_departure_QComboBox_currentIndexChanged(int index);

    void on_destination_QComboBox_currentIndexChanged(int index);

    void on_isTimeLimited_radioButton_pressed();

    void on_findRoute_pushButton_clicked(bool checked);

    void on_simulation_pushButton_clicked(bool checked);

    void on_stopSimulation_pushBotton_clicked(bool checked);

    void changeTime();

    void changeVehicleStatus();

    void on_limitedTime_lineEdit_editingFinished();

    void on_slower_pushButton_clicked();

    void on_faster_PushButton_clicked();

    void find_route();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    request user_request;//记录用户需求
    route_info best_route;//记录最佳路径
    QGraphicsScene *scene;
    my_time simu_time;//记录当前模拟时间
    QGraphicsPixmapItem *vehicle_item;
    QGraphicsPixmapItem * waiting_item;
    QGraphicsPixmapItem *finish_item;
    QPixmap map_png;
    QPixmap waiting_png;
    QPixmap plane_png;
    QPixmap train_png;
    QPixmap car_png;
    QPixmap vehicle_png;
    QPixmap finish_png;
    route *now_route;//记录当前模拟路径
    int wait_time_last;//记录当前剩余的等待时间
    int vehicle_time_last;//记录乘坐当前交通工具的剩余时间
    QTimer *time_timer;//定时器，管理模拟时间的变化
    QTimer *status_timer;//定时器，管理交通工具显示的变化
    double height_diff;//当前点到点路线中每个TIME_SCALE需要增加的高度
    double width_diff;//当前点到点路线中每个TIME_SCALE需要增加的宽度
    int cur_progress;//当前点到点路线中交通工具的进度
    string vehicle_name;
    int SECPERHOUR;
};

#endif // MAINWINDOW_H
