#include"struct.h"
extern city cities[CITY_NUM];
void get_my_time(my_time & cur_time){
    time_t rawtime;
    struct tm * ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    cur_time.year = ptminfo->tm_year + 1900;
    cur_time.month = ptminfo->tm_mon + 1 ;
    cur_time.day = ptminfo->tm_mday;
    cur_time.hour = ptminfo->tm_hour;
    cur_time.minute=0;
    return;
}

void add_time(my_time & _start, int _add){
            int temp_hour;
            temp_hour = _start.hour + _add;
            _start.hour=(temp_hour)%24;
            switch(_start.month){
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                _start.month = _start.month+(_start.day + temp_hour / 24)/31;
                _start.day = (_start.day + temp_hour / 24)%31;
                break;
                case 4:
                case 6:
                case 9:
                case 11:
                _start.month = _start.month+(_start.day + temp_hour / 24)/30;
                _start.day = (_start.day + temp_hour / 24)%30;
                break;
                case 2:
                _start.month = _start.month+(_start.day + temp_hour / 24)/29;
                _start.day = (_start.day+temp_hour/24)%29;
                break;
            }
}
