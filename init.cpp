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
	in_data.close();
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
	vehicle temp;
	ifstream plane_data;
	plane_data.open("plane.data");
	while (plane_data>>c){
		for (i = 0; i < n; i++){
			if (cities[i].city_name == c) break;
		}
		if (i == n) {
			printf("There is a wrong city_name in the vehicle data\n");
			continue;
		}
		temp.type = 1;
		plane_data.ignore(1); 
		plane_data >> temp.dst_city;
		plane_data.ignore(1); 
		plane_data >> temp.start_time.year;
		plane_data.ignore(1); 
		plane_data >> temp.start_time.month;
		plane_data.ignore(1); 
		plane_data >> temp.start_time.day;
		plane_data >> temp.start_time.hour;
		plane_data.ignore(6);
		plane_data >> temp.end_time.year;
		plane_data.ignore(1); 
		plane_data >> temp.end_time.month;
		plane_data.ignore(1); 
		plane_data >> temp.end_time.day;
		plane_data >> temp.end_time.hour;
		plane_data.ignore(6);		
		cities[i].my_vehicle.push_back(temp);
		cout<<cities[i].city_name<<temp.dst_city;
		printf("%d-%d-%d ", temp.start_time.year, temp.start_time.month, temp.start_time.day);
		printf("%d:00:00\n", temp.start_time.hour);
		printf("%d-%d-%d ", temp.end_time.year, temp.end_time.month, temp.end_time.day);
		printf("%d:00:00\n",temp.end_time.hour);
	}
	plane_data.close();	
	ifstream train_data;
	train_data.open("train_data");
	while (train_data>>c){
		for (i = 0; i < n; i++){
			if (cities[i].city_name == c) break;
		}
		if (i == n) {
			printf("There is a wrong city_name in the vehicle data\n");
			continue;
		}
		temp.type = 1;
		train_data.ignore(1); 
		train_data >> temp.dst_city;
		train_data.ignore(1); 
		train_data >> temp.start_time.year;
		train_data.ignore(1); 
		train_data >> temp.start_time.month;
		train_data.ignore(1); 
		train_data >> temp.start_time.day;
		train_data >> temp.start_time.hour;
		train_data.ignore(6);
		train_data >> temp.end_time.year;
		train_data.ignore(1); 
		train_data >> temp.end_time.month;
		train_data.ignore(1); 
		train_data >> temp.end_time.day;
		train_data >> temp.end_time.hour;
		train_data.ignore(6);		
		cities[i].my_vehicle.push_back(temp);
		cout<<cities[i].city_name<<temp.dst_city;
		printf("%d-%d-%d ", temp.start_time.year, temp.start_time.month, temp.start_time.day);
		printf("%d:00:00\n", temp.start_time.hour);
		printf("%d-%d-%d ", temp.end_time.year, temp.end_time.month, temp.end_time.day);
		printf("%d:00:00\n",temp.end_time.hour);
	}
	ifstream car_data;
	car_data.open("car_data");
	while (car_data>>c){
		for (i = 0; i < n; i++){
			if (cities[i].city_name == c) break;
		}
		if (i == n) {
			printf("There is a wrong city_name in the vehicle data\n");
			continue;
		}
		temp.type = 1;
		car_data.ignore(1); 
		car_data >> temp.dst_city;
		car_data.ignore(1); 
		car_data >> temp.start_time.year;
		car_data.ignore(1); 
		car_data >> temp.start_time.month;
		car_data.ignore(1); 
		car_data >> temp.start_time.day;
		car_data >> temp.start_time.hour;
		car_data.ignore(6);
		car_data >> temp.end_time.year;
		car_data.ignore(1); 
		car_data >> temp.end_time.month;
		car_data.ignore(1); 
		car_data >> temp.end_time.day;
		car_data >> temp.end_time.hour;
		car_data.ignore(6);		
		cities[i].my_vehicle.push_back(temp);
		cout<<cities[i].city_name<<temp.dst_city;
		printf("%d-%d-%d ", temp.start_time.year, temp.start_time.month, temp.start_time.day);
		printf("%d:00:00\n", temp.start_time.hour);
		printf("%d-%d-%d ", temp.end_time.year, temp.end_time.month, temp.end_time.day);
		printf("%d:00:00\n",temp.end_time.hour);
	}
	return n;
}