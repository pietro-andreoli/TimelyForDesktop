//@author Pietro Andreoli - github.com/topfight
	
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

//Declaration for a function that converts the calculated time values into a proper time. (See function documentation for details)
void convert_time_calc(int(*time)[3]);

/**
	Looks through all the schedules and calculates the time until the nearest schedule

	@param curr the current time of the system to be compared to the scheduled times
	@return the difference in time between the current time and the next closest schedule
*/
int calculateWait(tm curr);

/**
	Does the same as calculateWair(tm curr), may remove this  in the future.

	@param curr the current time of the system to be compared to the scheduled times
	@return the difference in time between the current time and the next closest schedule
*/
double calculateWait(time_t curr);

/**
	Initializes all the schedules

	@return will always retrun 1, mainly because I dont know what else itd return. Pretty much unnecessary.
*/
int init_schedules();
//not used atm
int on = 1;
//An array to hold the schedules the user enters.
struct tm *bg_t[2];

int main(){
	//Initialize the schedules
	init_schedules();
	//Get user input for the time values in the schedules
	for (int i = 0; i < 2; i++) {
		//Variables to hold the user input for each time value.
		std::string hour_val;
		std::string min_val;
		std::string sec_val;
		std::cout << "---Values for picture number " << i << "--- \n";
		std::cout << "Enter an hour value: ";
		//Following if statements get the input from the user and converts to int. Very unstable, will come back to it. 
		//TODO: prep code for invalid inputs
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

		
	}
	//Just a debugging print statement, will be removed
	std::cout << "\n h = " << bg_t[0]->tm_hour << "  || m = " << bg_t[0]->tm_min << " || s = " << bg_t[0]->tm_sec << "\n";
	
	//Getting the current time of the system. 
	//TODO: Find a faster way of getting the current time
	time_t currentTime = time(0);
	time_t *a = &currentTime;
	tm *curr = new struct tm;
	gmtime_s( curr, a);
	//While loop where it constantly checks when the next schedule is and waits the appropriate amount of time
	while (on) {
		//Setting the current time
		*a = time(0);
		gmtime_s(curr, a);
		//std::cout << "\n time.h = " << curr->tm_hour;
		//Getting the calculated time for waiting.
		//uncomment when you figure out what hmade this line stop working 
		//int x = calculateWait(*curr);
		time_t temp;
		int x = calculateWait(time(&temp));
		//just a debugging print statement
		std::cout << " \n x = " << x << "\n";
		//If calculated -1 (meaning there was some sort of error)
		if (x == -1) {
			std::cout << "\n NEGATIVE ONE";
			break;
		}
		//Otherwise make the thread sleep the necessary amount of time
		else {
			std::cout << "ayy it workd";
			std::this_thread::sleep_for(std::chrono::seconds(x));
		}
	}	
	
	/* CODE FOR CHANGING THE DESKTOP BACKGROUND

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
//Initializes the schedules, will likely be removed in the future. (See function documentation for details)
int init_schedules() {
	int numSched = (sizeof(bg_t) / sizeof(*bg_t));
	//loops through and intializes the list of all schedules
	for (int i = 0; i < numSched; i++) {
		time_t temp;
		time(&temp);
		bg_t[i] = new struct tm;
		localtime_s(bg_t[i] , &temp );
	}
	return 1;
}
//Function that calculates which scheduled background change is closest. (See function documentation for details)
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
//Function that calculates which scheduled background change is closest. (See function documentation for details)
int calculateWait(tm curr) {
	//Gets the size of the list of schedules
	int numSched = (sizeof(bg_t) / sizeof(*bg_t));
	//gets the current time in seconds
	int curr_in_sec = curr.tm_hour * 60 * 60 + curr.tm_min * 60 + curr.tm_sec;
	//Variable to hold the shortest amount of time to the next schedule (defaulted to a day in seconds)
	int shortest = 90061;
	//temp var, may be removed
	int next_day_shortest = -1;
	//If "curr.tm_hour -= 4;" is uncommented, comment it out or remove it. My computers time is bugged and so it is internally 4 hours ahead.
	curr.tm_hour -= 4;
	//Looping through all the schedules
	for (int i = 0; i < numSched; i++) {
		//Calculates the difference between the current schedule and now, stores it in an array. index 0 = hours, index 1 = minutes, index 2 = seconds
		int curr_diff[3] =  { bg_t[i]->tm_hour - curr.tm_hour, bg_t[i]->tm_min - curr.tm_min, bg_t[i]->tm_sec - curr.tm_sec };
		std::cout << "curr_diff = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[2] << "\n";
		std::cout << "bg_t[i]->tm_hour = " << bg_t[i]->tm_hour << " || curr.tm_hour = " << curr.tm_hour << " \n";
		std::cout << "bg_t[i]->tm_min = " << bg_t[i]->tm_min << " || curr.tm_min = " << curr.tm_min << " \n";
		std::cout << "bg_t[i]->tm_sec = " << bg_t[i]->tm_sec << " || curr.tm_sec = " << curr.tm_sec << " \n";
		//if the current difference in hours is not negative (meaning the difference between the schedule and now does not indicated the schedule is before the current time)
		if (curr_diff[0] >= 0) {
			//convert the calculated time (which may include negative minutes or seconds) into a proper time (with positive minutes and seconds)
			//ex. 3:40:-5 -> 3:39:55
			convert_time_calc(&curr_diff);
			std::cout << "curr_diff now = " << curr_diff[0] << ", " << curr_diff[1] << ", " << curr_diff[2] << "\n";
			//Calculates the current difference in seconds
			int curr_diff_in_sec = curr_diff[0] * 60 * 60 + curr_diff[1] * 60 + curr_diff[2];
			std::cout << "curr_diff_in_sec = " << curr_diff_in_sec << "\n";
			std::cout << "shortest = " << shortest;
			//If we have found a new shortest then set the indicating variable
			if (curr_diff_in_sec < shortest && curr_diff_in_sec >=0) 
				shortest = curr_diff_in_sec;
			
		}
		
	}
	//Meaning a new shortest was never found
	if (shortest == 90061) {
		//There are no more scheduled backgrounds for the rest of the day, so prep for the next day
		//Get how long it will be until the 24h mark
		int curr_diff[3] = { 24 - curr.tm_hour,0 - curr.tm_min, 0 - curr.tm_sec };
		//get proper time
		convert_time_calc(&curr_diff);
		//return the time in seconds until the end of the day
		return curr_diff[0] * 60 * 60 + curr_diff[1] * 60 + curr_diff[2];
	}else
		return shortest;

}

//converts improper time to proper time. May be fully commented later...
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