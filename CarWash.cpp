/*
	William Freet
	CECS 282
	Final lab!-
*/
#include <iostream>
#include <deque>
#include <random>
#include <cstdio>
#include "Washer.h"

using namespace std;

void main() {

	int seconds_per_car;
	float probability;
	int total;

	cout << "Seconds to wash one car: ";
	cin >> seconds_per_car;

	cout << "\nProbability of customer arrival during a second: ";
	cin >> probability;
	
	cout << "\nTotal simulation time: ";
	cin >> total;

	cout << "\nSeconds per car: " << seconds_per_car << endl;
	cout << "Prob: " << probability << endl;
	cout << "Total: " << total << endl;

	deque<Washer> to_serve;
	int customer_count = 0;
	float wait_time_sum = 0;

	probability *= 10000;
	random_device rd;		//only used once to initialize (seed) engine
	mt19937 rng(rd());		//random-number engine used (Mersenne-Twister)
	uniform_int_distribution<int> uni(0, 10000); //0 -> 10,000 w/probability of 25 is the same as
	for (int i = 0; i < total; i++) {			 //0 -> 1	   w/probability of .0025 (mult by 1e4)
		
		auto random_integer = uni(rng);
		if (random_integer < probability) {
			to_serve.push_back(Washer(seconds_per_car));
			customer_count++;
		}
		
		if (!(to_serve.empty())) {
			to_serve.front().oneSecond();

			if (to_serve.front().complete()) {
				wait_time_sum += to_serve.front().getWaitTime();
				to_serve.pop_front();
			}

			if (to_serve.size() > 1) {
				for (deque<Washer>::iterator it = to_serve.begin()++; it != to_serve.end(); ++it) {
					it->wait();
				}
			}
		} 
	}

	//check for cars that were left waiting
	if (!(to_serve.empty())) {
		for (deque<Washer>::iterator it = to_serve.begin(); it != to_serve.end(); ++it) {
			wait_time_sum += it->getWaitTime();
		}
	}
	
	cout << "\nCustomers served: " << customer_count << endl;
	cout << "Average wait time: " << wait_time_sum / customer_count << "\n" << endl;

	system("pause");
}