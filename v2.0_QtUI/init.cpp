#include"struct.h"
extern city cities[CITY_NUM];
int get_city_no_vehicle_data(string c){
	int i;
	for (i = 0; i < total_city; i++){
        if (c == cities[i].city_name) break;
	}
	if (i != total_city) return i; 
	else {
		cout<<"****ERROR CITY NAME IN THE VEHICLE DATA****\n";
		return -1;
	}
}

void read_vehicle(ifstream & in_data, int type){
	string c;  
	int i;
	vehicle temp;
	while (in_data>>c){
		i = get_city_no_vehicle_data(c);
		if (i==-1) continue;
		temp.type = type;
		in_data.ignore(1); 
		in_data >> c;
		temp.dst_city_no = get_city_no_vehicle_data(c);
		if (temp.dst_city_no==-1) continue;
		in_data.ignore(1); 
		in_data >> temp.start_time.hour;
		in_data.ignore(1);
		in_data >> temp.start_time.minute;
		in_data.ignore(1); 
		in_data >> temp.time_spent.hour;
		in_data.ignore(1);
		in_data>>temp.time_spent.minute;
		cities[i].my_vehicle.push_back(temp);
        //cout<<cities[i].city_name<<" "<<cities[temp.dst_city_no].city_name<<" "<<temp.start_time.hour<<":"<<temp.start_time.minute;
	}
}

void init(){
    ifstream city_data;
	string c;
    int n = 0;
    city_data.open("city.data");
    if (!city_data.is_open()) {
        printf("ERROR\n");
        return;
    }
    while(city_data>>cities[n].city_name){
		city_data>>cities[n].city_risk_no;
        city_data>>cities[n].posx;
        city_data>>cities[n].posy;
		n++;
	}
    city_data.close();
    ifstream plane_data;
    plane_data.open("plane.data");
	read_vehicle(plane_data, 0);
	plane_data.close();
    ifstream train_data;
    train_data.open("train.data");
	read_vehicle(train_data, 1);
	train_data.close();
    ifstream car_data;
    car_data.open("car.data");
	read_vehicle(car_data, 2);	
	car_data.close();
    return;
}
