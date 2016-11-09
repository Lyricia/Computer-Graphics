#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;
using namespace std::chrono;

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
	t_maxnum = 2;
	p.clear();

	auto start_t = high_resolution_clock::now();
	
	thread t1(threadtas);
	thread t2(threadtas);
	t1.join();
	t2.join();
	
	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
	cout << "Number of Thread = "<<t_maxnum<<", SUM = " << sum << endl;
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
		while(atomic_flag_test_and_set(&p));
		sum = sum + 1;
		p.clear();
	}
}

