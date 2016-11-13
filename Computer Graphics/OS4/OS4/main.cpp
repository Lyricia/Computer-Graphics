#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;


class Cfork {
	mutex mylock;
public:
	void grab() {
		mylock.lock();
	}
	void release() {
		mylock.unlock();
	}
};

Cfork Fork[5];

void philo(int id)
{

	for (int i = 0; i < 1000000; ++i)
	{
		if ((id % 2) == 1)
		{
			Fork[id].grab();
			Fork[(id + 1) % 5].grab();
			//cout << "Eating " << id << endl;
			Fork[id].release();
			Fork[(id + 1) % 5].release();
			//cout << "thinking " << id << endl;
		}

		else if ((id % 2) == 0)
		{
			Fork[(id + 1) % 5].grab();
			Fork[id].grab();
			//cout << "Eating " << id << endl;
			Fork[(id + 1) % 5].release();
			Fork[id].release();
			//cout << "thinking " << id << endl;
		}
	}
}

int main(void)
{
	auto start_t = high_resolution_clock::now();

	thread t1(philo,0);
	thread t2(philo,1);
	thread t3(philo,2);
	thread t4(philo,3);
	thread t5(philo,4);
	t5.join();
	t4.join();
	t3.join();
	t2.join();
	t1.join();

	auto du = high_resolution_clock::now() - start_t;
	cout << "Computing time is " << duration_cast<milliseconds>(du).count() << "ms, ";
}