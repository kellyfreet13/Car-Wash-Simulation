#ifndef WASHER_H
#define WASHER_H

#include <iostream> 

using namespace std;

class Washer
{
public:
	Washer() {};
	~Washer() {};

	Washer(int seconds) {
		seconds_for_wash = seconds;
		wash_time_left = seconds_for_wash;
		time_spent_waiting = 0;
	};


	void oneSecond() {
		wash_time_left -= 1;
	}

	bool complete() {
		return wash_time_left == 0;
	}

	void wait() {
		time_spent_waiting++;
	}

	float getWaitTime() {
		return time_spent_waiting;
	}

	void getInfo() {
		cout << "Washtime left " << wash_time_left << endl;
	}

private:
	int seconds_for_wash;
	int wash_time_left;
	float time_spent_waiting;
};

#endif // !WASHER_H

