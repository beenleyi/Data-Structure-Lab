#include"struct.h"
extern city cities[CITY_NUM];

extern void get_my_time(my_time &);
extern void add_time(my_time &, int);

void dulplicate_best_route(route_ptr & best_detail_route, const route_ptr & temp_route){
	route_ptr  i, j, k;
	i = best_detail_route->next_ptr;
	while(i){
		j = i->next_ptr;
		delete i;
		i = j;
	}
	i = best_detail_route;
	j = temp_route;
	while(j != NULL){
		k = new route;
		i->next_ptr = k;
		k->wait_time = j->wait_time;
		k->arrival_time = j->arrival_time;
		k->city_no = j->city_no;
		k->vehicle = j->vehicle;
		k->vehicle_time = j->vehicle_time;
		k->next_ptr = NULL;
        //cout<<"Now you are in "<<cities[k->city_no].city_name;
        //printf(" at % d-%d-%d % d:%d. You are waiting for the no.%d vehicle for %d hours. Then you spend %d hours to the next station.\n", k->arrival_time.year, k->arrival_time.month, k->arrival_time.day, k->arrival_time.hour, k->arrival_time.minute, k->vehicle, k->wait_time, k->vehicle_time  );
		j = j->next_ptr;
		i = i->next_ptr;
	}
	return;
}

void trace_back(route_ptr cur_ptr, const request & user_request, double risk_v, int time_v, route_info & best_route, route_ptr & head){
	vector < vehicle>::const_iterator i, j;
	j=cities[cur_ptr->city_no].my_vehicle.end();
	for (i = cities[cur_ptr->city_no].my_vehicle.begin(); i != j; i++){
		route_ptr k;
        k = head;
		int flag=0;
		while(k){
			if (i->dst_city_no == k->city_no) {
				flag = 1;
				break;
			}
			else k=k->next_ptr;
		}
		//防止路线循环
		if (flag) continue;
		int temp_wait, temp_time_v,temp_hour;
		double temp_risk_v,temp_city_risk;
		temp_wait = i->start_time.hour - cur_ptr->arrival_time.hour;
		if (temp_wait>0) cur_ptr->wait_time = temp_wait; else cur_ptr->wait_time = 24 + temp_wait;
		cur_ptr->vehicle_time = i->time_spent.hour;
		temp_city_risk=city_risk_no2value[cities[cur_ptr->city_no].city_risk_no];
		temp_risk_v = cur_ptr->wait_time *temp_city_risk  + cur_ptr->vehicle_time * vehicle_risk_no2value[i->type]*temp_city_risk;
		temp_time_v = cur_ptr->wait_time + cur_ptr->vehicle_time;
		if (user_request.travel_type == 1 && temp_time_v + time_v >= (user_request.limited_time)) continue;
		if ((temp_risk_v + risk_v) >= best_route.total_risk) continue;		
		risk_v = temp_risk_v + risk_v;
		time_v = temp_time_v + time_v;
		cur_ptr->vehicle = i->type;
		if (i->dst_city_no==user_request.dst_city_no){
			best_route.total_risk = risk_v;
			best_route.total_time = time_v;
            //printf("total_risk:%lf total_time:%d\n", best_route.total_risk, best_route.total_time );
			dulplicate_best_route(best_route.detail_route,head);
		}
		else{
			route_ptr new_route;
			new_route = new route;
			new_route->city_no = i->dst_city_no;
			//计算到达时间，不考虑跨年情况
			temp_hour = cur_ptr->wait_time + cur_ptr->vehicle_time;
			new_route->arrival_time.year = cur_ptr->arrival_time.year;
			new_route->arrival_time.month = cur_ptr->arrival_time.month;
			new_route->arrival_time.day = cur_ptr->arrival_time.day;
			new_route->arrival_time.hour = cur_ptr->arrival_time.hour;
            new_route->arrival_time.minute = 0;
			add_time(new_route->arrival_time, temp_hour);
			cur_ptr->next_ptr = new_route;
			new_route->next_ptr=NULL;
            trace_back(new_route, user_request, risk_v, time_v, best_route,head);
			delete new_route;
			cur_ptr->next_ptr = NULL;
		}
		risk_v -= temp_risk_v;
		time_v-=temp_time_v;
	}
	return;

}
