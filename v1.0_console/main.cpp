#include"struct.h"
city cities[CITY_NUM];
extern void log_input(const request &);
extern void log_output(const route_info &, int);
extern simulation(const route_info &, int);
extern void find_route(const request &, route_info &);
extern void input(request &);
extern int init();

int main(){
	request user_request;
	route_info best_route;
	init();
	input(user_request);
	log_input(user_request);
	find_route(user_request, best_route);
	log_output(best_route,user_request.dst_city_no);
	simulation(best_route,user_request.dst_city_no);
	return 0;
}