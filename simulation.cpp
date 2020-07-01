#include"struct.h"
extern city cities[CITY_NUM];
extern void add_time(my_time &, int);

void simulation(const route_info & best_route,int dst_city_no){
	cout<<"Start to simulatioin ?(y or n)"<<endl;
	char c;
	cin >> c;
	if (c == 'y'){
		route_ptr i;
		i = best_route.detail_route->next_ptr;
		my_time cur_time;
		int temp_hour;
		while(i){
			cur_time = i->arrival_time;		
			temp_hour = i->wait_time;
			while(temp_hour--){
				printf("It's %d-%d-%d %02d:%02d now. ", cur_time.year, cur_time.month, cur_time.day, cur_time.hour,cur_time.minute);
				printf("You are waiting at ");
				cout << cities[i->city_no].city_name<<"."<<endl;
				add_time(cur_time, 1);
				Sleep(10000);
			}
			temp_hour = i->vehicle_time;
			while(temp_hour--){
				printf("It's %d-%d-%d %02d:%02d now.", cur_time.year, cur_time.month, cur_time.day, cur_time.hour,cur_time.minute);
				printf(" You are on a ");
				if (i->vehicle == 0) printf("plane. This plane is flying to ");
				else if(i->vehicle == 1) printf("train. This train is bound to ");
				else printf("car. Next stop is ");
				if (i->next_ptr) cout << cities[i->next_ptr->city_no].city_name<<"." << endl;
				else cout<<"the destination--"<<cities[dst_city_no].city_name<<"."<<endl;
				add_time(cur_time, 1);
				Sleep(10000);
			}
			i = i->next_ptr;
		}
		printf("It's % d-%d-%d % 02d:%02d now.", cur_time.year, cur_time.month, cur_time.day, cur_time.hour, cur_time.minute);
		printf("You arrive in the destination!\n");
	}else return;
}