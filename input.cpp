#include"struct.h"

extern city cities[CITY_NUM];
extern void get_time(my_time &);

int get_city_no(string c){
	int i;
	for (i = 0; i < total_city; i++){
		if (c == cities[i].city_name) break;
	}
	static int flag = 0;
	while(i == total_city){
		cout<<"****ERROR INPUT****"<<endl;
		cout<<"Please input the correct city name.\n";
		if (flag == 0){
			cout<<"We provide the travel plan services for these cities:\n";
			 for (i = 0; i < total_city; i++) cout <<"*" << cities[i].city_name << endl;
			 flag = 1;
		}
		cout<<"Please input again:";	
		cin >> c;
		for (i = 0; i < total_city; i++){
			if (c == cities[i].city_name) break;		
		}
	}
	return i;
}	


void input(request & user_request){
	string c, d;
	int n;
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"Welcome to the travel plan helper!!!"<<endl;
	cout<<"Please input your departure city, destination city and your travel plan."<<endl;
	cout<<"0 for the least risky travel plan without time limited and 1 for the least risky travel plan in the limited time :)"<<endl;
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"The departure city name:"; 
	cin >> c;
	user_request.dept_city_no = get_city_no(c);
	cout<<"The destination city name:";
	cin >> c;
	user_request.dst_city_no = get_city_no(c);
	cout<<"The travel type:";
	cin >> n;
	while(n != 0 && n != 1){
		cout<<"****ERROR INPUT****"<<endl;
		cout<<"Please input 0 or 1 to choose the travel type."<<endl;
		cout<<"Please input again:";
		cin>>n;
	}
	user_request.travel_type = n;
	if (n == 1){
		cout<<"Please input your limited time (hour): ";
		cin>>user_request.limited_time;
	}
	cout<<"Your travel request is from "<<cities[user_request.dept_city_no].city_name<<" to "<<cities[user_request.dst_city_no].city_name;
	if (n == 1) cout<<" with the least risk in "<<user_request.limited_time <<" hours."<<endl;
	else cout<<" with the least risk."<<endl;
	return;
}

