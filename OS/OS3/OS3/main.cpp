#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;
using namespace std::chrono;

void sample();
void dekker(int id);
void threadmutex();
void threadatomic();
void threadtas();

int sum = 0;
atomic <int> sum_ato = 0;

atomic_flag p;
mutex mylock;

bool flag[2];
int turn;
int t_maxnum;

int main()
{
	flag[0] = false;
	flag[1] = false;
	turn = 0;
	t_maxnum = 1;
	p.clear();
	
	auto start_t = high_resolution_clock::now();
	
	thread t1(threadtas);
	thread t2(threadtas);
	thread t3(threadtas);
	thread t4(threadtas);
	thread t5(threadtas);
	thread t6(threadtas);
	thread t7(threadtas);
	thread t8(threadtas);
	thread t9(threadtas);
	thread t10(threadtas);
	thread t11(threadtas);
	thread t12(threadtas);
	thread t13(threadtas);
	thread t14(threadtas);
	thread t15(threadtas);
	thread t16(threadtas);
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
	
	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = " << t_maxnum << ", SUM = " << sum << endl;
	
}

void sample()					// Á¶°Ç 1
{
	for (int i = 0; i < 100'000'000; i++) 
		sum = sum + 1;
}

void dekker(int id)
{
	for (int i = 0; i < 50'000'000; i++)
	{
		flag[id] = true;
		while (flag[(id + 1) % 2] == true)
		{
			if (turn == (id + 1) % 2)
			{
				flag[id] = false;
				while (turn == (id + 1) % 2) {}
				flag[id] = true;
			}
		}
		sum = sum + 1;
		turn = (id + 1) % 2;
		flag[id] = false;
	}
}


void threadmutex()
{
	for (int i = 0; i < 100'000'000 / t_maxnum; i++)
	{
		mylock.lock();
		sum = sum + 1;
		mylock.unlock();
	}
}

void threadatomic()
{
	for (int i = 0; i < 100'000'000 / t_maxnum; i++)
	{
		sum_ato++;
	}
}

void threadtas()
{
	for (int i = 0; i < 100'000'000 / t_maxnum; i++)
	{
		while (atomic_flag_test_and_set(&p));
		sum = sum + 1;
		p.clear();
	}
}