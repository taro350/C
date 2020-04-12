// Every time you execute, it'll work and will get Segmentation Fault every now and then.
// g++ -Wall -pthread multithread_example.cpp -o multithread_example.o


#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <atomic>

//long sumthread = 0;

std::atomic<long> sumthread(0);

void SumNumber(const std::vector<int>& array, int is, int ie){
	for (int i = is; i <= ie; ++i){
		sumthread += array[i];
	}
	
};


int main(){
	
	std::vector<int> array;
	for (int i=0; i < 3000; ++i){
		array.push_back( rand() );
	}

	long threadSum = 0;

	for (unsigned int i = 0; i < array.size(); ++i){
		threadSum += array[i];
	}

	printf("The sum was %ld\n", threadSum);

	std::thread t1(SumNumber, array, 0, 999);
	std::thread t2(SumNumber, array, 100, 10000);

	t1.join();
	t2.detach();

	printf("The sum of these threads is %ld\n", sumthread.load());
	return 0;

}

