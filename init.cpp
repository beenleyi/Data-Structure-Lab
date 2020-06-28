#include"struct.h"
#include<vector>
#include<iostream>
#include <string>
#include<fstream>
using namespace std; 
extern city cities[20];

void read_vehicle(ifstream & in_data,int n){
	string c;  
	int i;
	vehicle temp;
	while (in_data>>c){
		for (i = 0; i < n; i++){
			if (cities[i].city_name == c) break;
		}
		if (i == n) {
			printf("There is a wrong city_name in the vehicle data\n");
			continue;
		}
		temp.type = 1;
		in_data.ignore(1); 
		in_data >> temp.dst_city;
		in_data.ignore(1); 
		in_data >> temp.start_time.year;
		in_data.ignore(1); 
		in_data >> temp.start_time.month;
		in_data.ignore(1); 
		in_data >> temp.start_time.day;
		in_data >> temp.start_time.hour;
		in_data.ignore(6);
		in_data >> temp.end_time.year;
		in_data.ignore(1); 
		in_data >> temp.end_time.month;
		in_data.ignore(1); 
		in_data >> temp.end_time.day;
		in_data >> temp.end_time.hour;
		in_data.ignore(6);		
		cities[i].my_vehicle.push_back(temp);
		cout<<cities[i].city_name<<temp.dst_city;
		printf("%d-%d-%d ", temp.start_time.year, temp.start_time.month, temp.start_time.day);
		printf("%d:00:00\n", temp.start_time.hour);
		printf("%d-%d-%d ", temp.end_time.year, temp.end_time.month, temp.end_time.day);
		printf("%d:00:00\n",temp.end_time.hour);
	}
}

int init(){
	ifstream city_data;
	string c;
	int n = 0, risk_num, i;
	city_data.open("city.data");
	while(city_data>>cities[n].city_name){
		city_data>>cities[n].city_risk;
		n++;
	}
	city_data.close();
	ifstream plane_data;
	plane_data.open("plane.data");
	read_vehicle(plane_data, n);
	plane_data.close();
	ifstream train_data;
	train_data.open("train.data");
	read_vehicle(train_data, n);
	train_data.close();
	ifstream car_data;
	car_data.open("car.data");
	read_vehicle(car_data, n);	
	car_data.close();
	return n;
}