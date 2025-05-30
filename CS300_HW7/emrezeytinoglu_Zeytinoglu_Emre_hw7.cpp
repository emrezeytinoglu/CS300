#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h>
#include "emrezeytinoglu_Zeytinoglu_Emre_hw7_HW7PrintQueue.h"

using namespace std;

int MIN_TIME_CREATING;
int MAX_TIME_CREATING;
mutex printMUTEX;
int print_count = 0;
int sended_count = 0;
mutex coutMUTEX;
int TOTAL_ITEMS;
HW7PrintQueue PRINTER_QUEUE;
int finish_count = 0;
int MAX_PAGE_COUNT;
mutex userMUTEX;
int MIN_PAGE_COUNT;

int random_range(const int& min, const int& max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void user_thread_function(int user_id)
{
	while (print_count < TOTAL_ITEMS) {
		this_thread::sleep_for(chrono::seconds(random_range(MIN_TIME_CREATING, MAX_TIME_CREATING)));
		userMUTEX.lock();
		if (print_count >= TOTAL_ITEMS) {
			userMUTEX.unlock();
		}
		else {
			int newsize, newpagecount;
			newpagecount = random_range(MIN_PAGE_COUNT, MAX_PAGE_COUNT);
			print_count++;
			PRINTER_QUEUE.enqueue(print_count, newpagecount);
			newsize = PRINTER_QUEUE.getCurrentSize();
			userMUTEX.unlock();

			coutMUTEX.lock();
			sended_count++;
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);
			cout << "User " << user_id << " sent new print job with ID " << sended_count
				<< " sent to the printer queue, number of pages: " << newpagecount << " (print queue size: "
				<< newsize << ") " << put_time(ptm, "%X") << endl;
			coutMUTEX.unlock();
		}
	}
}

void print_thread_function()
{
	int PRINT_ID, PAGE_COUNT;
	while (finish_count < TOTAL_ITEMS)
	{
		printMUTEX.lock();
		if (PRINTER_QUEUE.isEmpty())
		{
			printMUTEX.unlock();
		}
		else
		{
			PRINTER_QUEUE.dequeue(PRINT_ID, PAGE_COUNT);
			int afterDeleting = PRINTER_QUEUE.getCurrentSize();
			finish_count++;
			printMUTEX.unlock();

			coutMUTEX.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);
			cout << "The printer started to print the job with ID: " << PRINT_ID << ", number of pages: "
				<< PAGE_COUNT << " (queue size is: " << afterDeleting << ") " << put_time(ptm, "%X") << endl;
			coutMUTEX.unlock();

			this_thread::sleep_for(chrono::seconds(PAGE_COUNT));

			coutMUTEX.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
			localtime_s(ptm, &tt);
			cout << "The printer finished printing the job with ID: " << PRINT_ID << ", number of pages: "
				<< PAGE_COUNT << " " << put_time(ptm, "%X") << endl;
			coutMUTEX.unlock();
		}
	}
}

int main()
{
	cout << "Please enter the max number of print jobs: ";
	cin >> TOTAL_ITEMS;

	cout << "Please enter the min and max values for the waiting time period (in seconds) after creating a print job: " << endl;
	cout << "Min: ";
	cin >> MIN_TIME_CREATING;
	cout << "Max: ";
	cin >> MAX_TIME_CREATING;

	cout << "Please enter the min and max values for the number of pages in a print job: " << endl;
	cout << "Min number of pages: ";
	cin >> MIN_PAGE_COUNT;
	cout << "Max number of pages: ";
	cin >> MAX_PAGE_COUNT;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &tt);

	cout << "Simulation starts " << put_time(ptm, "%X") << endl;

	thread thr0(user_thread_function, 1);
	thread thr1(user_thread_function, 2);
	thread thr2(user_thread_function, 3);
	thread thr3(print_thread_function);

	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	localtime_s(ptm, &tt);
	cout << "End of the simulation ends: " << put_time(ptm, "%X") << endl;
	return 0;
}