#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

//double calculateWait(time_t curr);
void convert_time_calc(int(*time)[3]);
int calculateWait(tm curr);
int init_schedules();
int on = 1;

struct tm *bg_t[2];

int main(){
	init_schedules();
	for (int i = 0; i < 2; i++) {
		//bg_t[i] = new struct tm;
		std::string hour_val;
		std::string min_val;
		std::string sec_val;
		std::cout << "---Values for picture number " << i << "--- \n";
		std::cout << "Enter an hour value: ";

		if (!std::getline(std::cin, hour_val)) {
			std::cout << "error";
			return -1;
		}
		else {
			bg_t[i]->tm_hour = stoi(hour_val, 0, 10);
		}


		std::cout << "Enter an minute value: ";
		if (!std::getline(std::cin, min_val)) {
			std::cout << "error";
			return -1;
		}
		else {
			bg_t[i]->tm_min = stoi(min_val, 0, 10);
		}

		std::cout << "Enter an second value: ";
		if (!std::getline(std::cin, sec_val)) {
			std::cout << "error";
			return -1;
		}
		else {
			bg_t[i]->tm_sec = stoi(sec_val, 0, 10);
		}

		//char buffer[50];
		//std::cout << asctime_s(buffer, 50, bg_t[i]);
		
	}
	std::cout << "\n h = " << bg_t[0]->tm_hour << "  || m = " << bg_t[0]->tm_min << " || s = " << bg_t[0]->tm_sec << "\n";
	
	//time_t *currentTime = new time_t
	time_t currentTime = time(0);
	time_t *a = &currentTime;
	tm *curr = new struct tm;
	gmtime_s( curr, a);
	/*struct tm *x1 = new struct tm;
	x1->tm_hour = 7;
	x1->tm_min = 8;
	x1->tm_sec = 5;
	struct tm *x2 = new struct tm;
	x2->tm_hour = 4;
	x2->tm_min = 4;
	x2->tm_sec = 15;
	std::cout << "ayy";
	int curr_diff[3] = { x1->tm_hour - x2->tm_hour, x1->tm_min - x2->tm_min, x1->tm_sec - x2->tm_sec };
	convert_time_calc(&curr_diff);
	std::cout << "\n curr_diff in main = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[2] << "/n";*/
	//*currentTime = time(0);
	
	while (on) {
		*a = time(0);
		gmtime_s(curr, a);
		//double x = calculateWait(currentTime);
		int x = calculateWait(*curr);
		std::cout << " \n x = " << x << "\n";
		if (x == -1) {
			std::cout << "\n NEGATIVE ONE";
			break;
		}
		else {
			std::cout << "ayy it workd";
			std::this_thread::sleep_for(std::chrono::seconds(x));
		}
	}	
	
	/*

	char *buff = new char[200];

	//char *buff;
	strcpy_s(buff, 200, "C:\\Users\\petro\\Documents\\Rainmeter\\Skins\\16BitTheme\\@Resources\\BG\\Pokemon Backgrounds\\Afternoon 1366.png");
	int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 200, buff, SPIF_UPDATEINIFILE);
	std::cout << buff ;
	*/
	std::cout << "\n DONE";
	getchar();
	return 0;
}

int init_schedules() {
	int numSched = (sizeof(bg_t) / sizeof(*bg_t));
	
	for (int i = 0; i < numSched; i++) {
		time_t temp;
		time(&temp);
		bg_t[i] = new struct tm;
		localtime_s(bg_t[i] , &temp );
	}
	return 1;
}

double calculateWait(time_t curr) {
	int numSched = (sizeof(bg_t) / sizeof(*bg_t));
	double shortest = 86400;
	for (int i = 0; i < numSched; i++) {
		double curr_diff = difftime(mktime(bg_t[i]), curr);
		std::cout << " CURR DIFF :  " << curr_diff << " : \n";
		if (curr_diff >= 0 && curr_diff < shortest)
			shortest = curr_diff;
	}
	if (shortest >= 86400)
		return -1;
	else
		return shortest;

}

int calculateWait(tm curr) {
	int numSched = (sizeof(bg_t) / sizeof(*bg_t));
	int curr_in_sec = curr.tm_hour * 60 * 60 + curr.tm_min * 60 + curr.tm_sec;
	int shortest = 90061;
	for (int i = 0; i < numSched; i++) {
		//curr.tm_hour -= 4;
		int curr_diff[3] =  { bg_t[i]->tm_hour - curr.tm_hour, bg_t[i]->tm_min - curr.tm_min, bg_t[i]->tm_sec - curr.tm_sec };
		std::cout << "curr_diff = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[2] << "\n";
		std::cout << "bg_t[i]->tm_hour = " << bg_t[i]->tm_hour << " || curr.tm_hour = " << curr.tm_hour << " \n";
		std::cout << "bg_t[i]->tm_min = " << bg_t[i]->tm_min << " || curr.tm_min = " << curr.tm_min << " \n";
		std::cout << "bg_t[i]->tm_sec = " << bg_t[i]->tm_sec << " || curr.tm_sec = " << curr.tm_sec << " \n";

		if (curr_diff[0] >= 0) {
			convert_time_calc(&curr_diff);
			std::cout << "curr_diff now = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[2] << "\n";
			int curr_diff_in_sec = curr_diff[0] * 60 * 60 + curr_diff[1] * 60 + curr_diff[2];
			std::cout << "curr_diff_in_sec = " << curr_diff_in_sec << "\n";
			std::cout << "shortest = " << shortest;

			if (curr_diff_in_sec < shortest) 
				shortest = curr_diff_in_sec;
			
			//std::cout << "curr_diff = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[3];
		}
		
	}
	return shortest;

}

void convert_time_calc(int (*time)[3]) {
	if ((*time)[2] < 0) {
		int min_in_s = (*time)[1] * 60;
		std::cout << "min_in_s = " << min_in_s << "\n";
		int min_plus_s = (*time)[2] + min_in_s;
		std::cout << "min_plus_s = " << min_plus_s << "\n";
		if((*time)[1] < 0 && (*time)[2] < 0)
			(*time)[2] = (min_plus_s % 60) + 60;
		else
			(*time)[2] = min_plus_s % 60;
		std::cout << "time[2] " << (*time)[2] << "\n";
		int new_min = min_plus_s - (*time)[2];
		std::cout << "new_min = " << new_min << "\n";
		(*time)[1] = (int)(new_min / 60);
	}
	if ((*time)[1] < 0) {
		int hr_in_min = (*time)[0] * 60;
		int hr_plus_min = (*time)[1] + hr_in_min;
		(*time)[1] = hr_plus_min % 60;
		int new_hr = hr_plus_min - (*time)[1];
		(*time)[0] = (int)(new_hr / 60);
	}
	
	if ((*time)[0] < 0) {
		return ;
	}

}