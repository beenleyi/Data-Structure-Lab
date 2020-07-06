#include "mainwindow.h"
#include "ui_mainwindow.h"

city cities[CITY_NUM];
extern void init();
extern void find_route();
extern void log_input(const request &);
extern void log_output(const route_info &, int);
extern void add_time(my_time &, int);
extern void get_my_time(my_time &);
extern void log_simulation(const route_info & best_route,int dst_city_no);
extern void trace_back(route_ptr cur_ptr, const request & user_request, double risk_v, int time_v, route_info & best_route,route_ptr &head);

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //初始化
    ui->setupUi(this);
    ui->now_dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:00");
    ui->Simu_dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:00");
    ui->now_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->Simu_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->now_dateTimeEdit->setReadOnly(true);
    ui->bestRoute_plainTextEdit->setReadOnly(true);
    ui->simulation_pushButton->setEnabled(false);
    ui->stopSimulation_pushBotton->setEnabled(false);
    ui->limitedTime_lineEdit->setEnabled(false);
    ui->limitedTime_lineEdit->setMaxLength(9);
    init();
    //用户需求初始化
    user_request.travel_type=0;
    user_request.dept_city_no=-1;
    user_request.dst_city_no=-1;
    map_png=QPixmap(":/new/img/resource/map.png");
    waiting_png=QPixmap(":/new/img/resource/waiting.png");
    plane_png=QPixmap(":/new/img/resource/plane.png");
    train_png=QPixmap(":/new/img/resource/train.png");
    car_png=QPixmap(":/new/img/resource/car.png");
    finish_png = QPixmap(":/new/img/resource/finish.png");
    //展示地图
    scene = new QGraphicsScene;
    scene->addPixmap(map_png);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    //定时器设定
    time_timer=new QTimer;
    status_timer=new QTimer;
    connect(time_timer,SIGNAL(timeout()),this,SLOT(changeTime()));
    connect(status_timer,SIGNAL(timeout()),this,SLOT(changeVehicleStatus()));
    //速度初始化
    SECPERHOUR=2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_isTimeLimited_radioButton_pressed()
{
    if (ui->isTimeLimited_radioButton->isChecked()){
        user_request.travel_type=0;
        ui->limitedTime_lineEdit->setEnabled(false);
    }
    else {
        user_request.travel_type=1;
        ui->limitedTime_lineEdit->setEnabled(true);
    }
    return;
}

void MainWindow::on_departure_QComboBox_currentIndexChanged(int index)
{
    user_request.dept_city_no=index-1;
    return;
}

void MainWindow::on_destination_QComboBox_currentIndexChanged(int index)
{
    user_request.dst_city_no=index-1;
    return;
}


void MainWindow::on_findRoute_pushButton_clicked(bool checked)
{
    ui->faster_PushButton->setEnabled(true);
    ui->slower_pushButton->setEnabled(true);
    //错误提示
    if(user_request.dept_city_no==-1){
        ui->bestRoute_plainTextEdit->setPlainText("****ERROR****\nPlease input the departure city!");
        return;
    }
    if(user_request.dst_city_no==-1){
        ui->bestRoute_plainTextEdit->appendPlainText("****ERROR****\nPlease input the destination city!");
        return;
    }
    if (user_request.dst_city_no==user_request.dept_city_no){
        ui->bestRoute_plainTextEdit->appendPlainText("****ERROR****\nYour departure city and destination city is the same!");
        return;
    }
    if (user_request.travel_type==1&&user_request.limited_time==0){
        ui->bestRoute_plainTextEdit->appendPlainText("****ERROR****\nPlease set the limited time!");
        return;
    }
    log_input(user_request);
    find_route();
    log_output(best_route, user_request.dst_city_no);
    if (best_route.detail_route->next_ptr==NULL) {
        ui->bestRoute_plainTextEdit->appendPlainText("****ERROR****\n Can NOT find one route which meet your require!");
        ui->simulation_pushButton->setEnabled(false);
        return;
    }
    log_simulation(best_route,user_request.dst_city_no);
    //不能找到合适的路径
    //输出最佳路径
    QString s,s1;
    ui->bestRoute_plainTextEdit->clear();
    ui->statusBar->clearMessage();
    s.append("Your best route is");
    ui->bestRoute_plainTextEdit->appendPlainText(s);
    route_ptr i;
    int next_city_no;
    my_time temp_time;
    i = best_route.detail_route->next_ptr;
    while(i){
        if(i->next_ptr) next_city_no=i->next_ptr->city_no;else next_city_no=user_request.dst_city_no;
        s1.append(QString::asprintf("%s--->%s by ",cities[i->city_no].city_name.c_str(),cities[next_city_no].city_name.c_str()));
        if (i->vehicle == 0) s1.append("plane") ;
        else if (i->vehicle == 1) s1.append("train");
        else s1.append( "car");
        s1.append( ", start time: ");
        temp_time = i->arrival_time;
        add_time(temp_time, i->wait_time);
        s1.append(QString::asprintf("%d-%02d-%02d %02d:%02d",temp_time.year,temp_time.month,temp_time.day,temp_time.hour,temp_time.minute));
        s1.append(", arrival time:  ");
        add_time(temp_time, i->vehicle_time);
        s1.append(QString::asprintf("%d-%02d-%02d %02d:%02d",temp_time.year,temp_time.month,temp_time.day,temp_time.hour,temp_time.minute));
        i=i->next_ptr;
        ui->bestRoute_plainTextEdit->appendPlainText(s1);
        s1.clear();
    }
    ui->bestRoute_plainTextEdit->appendPlainText(QString::asprintf("The total time is %dh.",best_route.total_time));
    ui->bestRoute_plainTextEdit->appendPlainText(QString::asprintf("The total risk is %.2f.",best_route.total_risk));
    ui->simulation_pushButton->setEnabled(true);
    return;
}

void MainWindow::on_simulation_pushButton_clicked(bool checked)
{
    ui->departure_QComboBox->setEnabled(false);
    ui->destination_QComboBox->setEnabled(false);
    ui->findRoute_pushButton->setEnabled(false);
    ui->simulation_pushButton->setEnabled(false);
    ui->isTimeLimited_radioButton->setEnabled(false);
    ui->limitedTime_lineEdit->setEnabled(false);
    ui->stopSimulation_pushBotton->setEnabled(true);
    ui->faster_PushButton->setEnabled(false);
    ui->slower_pushButton->setEnabled(false);
    ui->Simu_dateTimeEdit->setReadOnly(true);
    ui->lineEdit->setEnabled(false);
    scene->clear();
    scene->addPixmap(map_png);
    now_route=best_route.detail_route->next_ptr;
    wait_time_last=now_route->wait_time;
    vehicle_time_last=now_route->vehicle_time;
    waiting_item=scene->addPixmap(waiting_png);
    waiting_item->setOffset(cities[now_route->city_no].posx-waiting_png.width()/2,cities[now_route->city_no].posy-waiting_png.height()/2);
    ui->statusBar->showMessage(QString::asprintf("You are waiting at %s, %dh last",cities[now_route->city_no].city_name.c_str(),wait_time_last));
    status_timer->start(wait_time_last * SECPERHOUR * 1000);
    time_timer->start(SECPERHOUR*1000);
    ui->graphicsView->show();
}

void MainWindow::on_stopSimulation_pushBotton_clicked(bool checked)
{
    ui->departure_QComboBox->setEnabled(true);
    ui->destination_QComboBox->setEnabled(true);
    ui->findRoute_pushButton->setEnabled(true);
    ui->simulation_pushButton->setEnabled(true);
    ui->isTimeLimited_radioButton->setEnabled(true);
    ui->limitedTime_lineEdit->setEnabled(true);
    ui->stopSimulation_pushBotton->setEnabled(false);
    if (wait_time_last) ui->departure_QComboBox->setCurrentIndex(now_route->city_no+1);
    else if (now_route->next_ptr) ui->departure_QComboBox->setCurrentIndex(now_route->next_ptr->city_no+1);
    else ui->departure_QComboBox->setCurrentIndex(user_request.dst_city_no+1);
    ui->faster_PushButton->setEnabled(true);
    ui->slower_pushButton->setEnabled(true);
    ui->now_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->Simu_dateTimeEdit->setReadOnly(false);
    ui->lineEdit->setEnabled(true);
    time_timer->stop();
    status_timer->stop();
}

void MainWindow::changeVehicleStatus(){
    if (vehicle_time_last>0){
        scene->clear();
        scene->addPixmap(map_png);
        ui->graphicsView->show();
        cur_progress+=1;
        vehicle_item=scene->addPixmap(vehicle_png);
        vehicle_item->setOffset(cities[now_route->city_no].posx-vehicle_png.width()/2+width_diff*cur_progress,cities[now_route->city_no].posy-vehicle_png.height()/2+height_diff*cur_progress);
        ui->graphicsView->show();
        status_timer->start(TIME_SCALE);
    }
}

void MainWindow::changeTime(){
    if (wait_time_last>0) wait_time_last-=1;
    else vehicle_time_last-=1;
    int next_city_no;
    if(now_route->next_ptr) next_city_no = now_route->next_ptr->city_no;
        else next_city_no = user_request.dst_city_no;
    //状态改变：从等待到交通工具出发
    if(wait_time_last == 0 && vehicle_time_last == now_route->vehicle_time){
        if(now_route->vehicle==0){
            vehicle_png=plane_png;
            vehicle_name="plane";
        }else if(now_route->vehicle==1){
            vehicle_png=train_png;
            vehicle_name="train";
        }else{
            vehicle_png=car_png;
            vehicle_name="car";
        }
        scene->clear();
        scene->addPixmap(map_png);
        cur_progress=0;//当前模拟进度为0
        vehicle_item=scene->addPixmap(vehicle_png);
        vehicle_item->setOffset(cities[now_route->city_no].posx-vehicle_png.width()/2,cities[now_route->city_no].posy-vehicle_png.height()/2);
        ui->graphicsView->show();
        height_diff=(double(cities[next_city_no].posy-cities[now_route->city_no].posy))/now_route->vehicle_time/(SECPERHOUR*1000/TIME_SCALE);
        width_diff=(double(cities[next_city_no].posx-cities[now_route->city_no].posx))/now_route->vehicle_time/(SECPERHOUR*1000/TIME_SCALE);
        status_timer->start(TIME_SCALE);
        time_timer->start(SECPERHOUR * 1000);   
        ui->Simu_dateTimeEdit->setDateTime(ui->Simu_dateTimeEdit->dateTime().addSecs(3600));
        ui->statusBar->showMessage(QString::asprintf("You are travelling by %s from %s to %s, %dh last",vehicle_name.c_str(),cities[now_route->city_no].city_name.c_str(),cities[next_city_no].city_name.c_str(),vehicle_time_last));
    }
    //状态改变：当前交通工具到达下一站
    else if(vehicle_time_last <= 0){
        if (now_route->next_ptr){//如果还不是终点站
            now_route=now_route->next_ptr;
            wait_time_last=now_route->wait_time;
            vehicle_time_last=now_route->vehicle_time;
            scene->clear();
            scene->addPixmap(map_png);
            waiting_item=scene->addPixmap(waiting_png);
            waiting_item->setOffset(cities[now_route->city_no].posx-waiting_png.width()/2,cities[now_route->city_no].posy-waiting_png.height()/2);
            ui->graphicsView->show();
            status_timer->start(wait_time_last*SECPERHOUR*1000);
            time_timer->start(SECPERHOUR * 1000);
            ui->Simu_dateTimeEdit->setDateTime(ui->Simu_dateTimeEdit->dateTime().addSecs(3600));
            ui->statusBar->showMessage(QString::asprintf("You are waiting at %s, %dh last",cities[now_route->city_no].city_name.c_str(),wait_time_last));
        }else{//已经到达终点站
            status_timer->stop();
            time_timer->stop();
            scene->clear();
            scene->addPixmap(map_png);
            finish_item= scene->addPixmap(finish_png);
            finish_item->setOffset(cities[user_request.dst_city_no].posx-finish_png.width()/2,cities[user_request.dst_city_no].posy-finish_png.height()/2);
            ui->graphicsView->show();
            ui->Simu_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
            ui->stopSimulation_pushBotton->setEnabled(false);
            ui->limitedTime_lineEdit->setEnabled(false);
            ui->departure_QComboBox->setEnabled(true);
            ui->destination_QComboBox->setEnabled(true);
            ui->findRoute_pushButton->setEnabled(true);
            ui->isTimeLimited_radioButton->setEnabled(true);
            ui->Simu_dateTimeEdit->setReadOnly(false);
            ui->faster_PushButton->setEnabled(true);
            ui->slower_pushButton->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            ui->now_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
            cur_progress=0;
            ui->statusBar->showMessage(QString::asprintf("You have arrived at %s!!!", cities[user_request.dst_city_no].city_name.c_str()));
        }
    }else{
        time_timer->start(SECPERHOUR*1000);
        if (wait_time_last)
            ui->statusBar->showMessage(QString::asprintf("You are waiting at %s, %dh last",cities[now_route->city_no].city_name.c_str(),wait_time_last));
        else ui->statusBar->showMessage(QString::asprintf("You are travelling by %s from %s to %s, %dh last",vehicle_name.c_str(),cities[now_route->city_no].city_name.c_str(),cities[next_city_no].city_name.c_str(),vehicle_time_last));
        ui->Simu_dateTimeEdit->setDateTime(ui->Simu_dateTimeEdit->dateTime().addSecs(3600));
    }
    return;
}

void MainWindow::on_limitedTime_lineEdit_editingFinished()
{
    user_request.limited_time=ui->limitedTime_lineEdit->text().toInt();
    return;
}


void MainWindow::on_slower_pushButton_clicked()
{
    SECPERHOUR+=1;
    ui->statusBar->showMessage(QString::asprintf("Set %d secs for 1 hour in simulation",SECPERHOUR));
}

void MainWindow::on_faster_PushButton_clicked()
{
    SECPERHOUR-=1;
    if (SECPERHOUR==0) {
        ui->bestRoute_plainTextEdit->appendPlainText("****ERROR****\nCan NOT set 0 sec per hour in simulation!");
        SECPERHOUR=1;
    }
    ui->statusBar->showMessage(QString::asprintf("Set %d secs for 1 hour in simulation",SECPERHOUR));
}

void MainWindow::find_route(){
    best_route.total_risk = INF;
    best_route.total_time = INF;
    route_ptr best_head,head;
    best_head = new route;
    best_route.detail_route = best_head;
    best_head->next_ptr=NULL;
    head = new route;
    head->city_no = user_request.dept_city_no;
    head->next_ptr=NULL;
    head->arrival_time.year=ui->Simu_dateTimeEdit->dateTime().date().year();
    head->arrival_time.month=ui->Simu_dateTimeEdit->dateTime().date().month();
    head->arrival_time.day=ui->Simu_dateTimeEdit->dateTime().date().day();
    head->arrival_time.hour=ui->Simu_dateTimeEdit->dateTime().time().hour();
    head->arrival_time.minute=0;
    //printf("It's nearly %d-%d-%d %d:00 now.\n", head->arrival_time.year, head->arrival_time.month, head->arrival_time.day, head->arrival_time.hour);
    //printf("%d->%d",user_request.dept_city_no,user_request.dst_city_no);
    trace_back(head, user_request, 0, 0, best_route,head);
}

void MainWindow::on_lineEdit_editingFinished()
{
    user_request.id=ui->lineEdit->text().toStdString();
}
