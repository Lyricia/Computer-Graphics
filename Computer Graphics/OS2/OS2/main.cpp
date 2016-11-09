#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

void sample();
void onlythread();

int sum = 0;

int main()
{
	//onlythread();
	sample();
}

void sample()					// 조건 1
{
	auto start_t = high_resolution_clock::now();
	for (int i = 0; i < 100'000'000; i++) sum = sum + 1;
	auto du = high_resolution_clock::now() - start_t;

	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";

	cout << "Number of Thread = 1, SUM = " << sum << endl;
}

void onlythread()				// 조건 2
{
	thread t1(sample);
	thread t2(sample);
	thread t3(sample);
	thread t4(sample);
	thread t5(sample);
	thread t6(sample);
	thread t7(sample);
	thread t8(sample);
	thread t9(sample);
	thread t10(sample);
	thread t11(sample);
	thread t12(sample);
	thread t13(sample);
	thread t14(sample);
	thread t15(sample);
	thread t16(sample);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();
}
