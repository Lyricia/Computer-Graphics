#include <iostream>
#include <queue>

using namespace std;

const int NumberOfCPU = 4;

struct PCB {
	int PID;
	int arrive_time;
	int length;
	int executed_Length;
	int priority;
};

int current_time;

void GenerateProcess()
{
	struct data {
		int time;
		int length;
		int priority;
	};

	vector <data> proc;

	const int TOTAL_TIME = 10000;
	const int AVE_LENGTH = 10;

	for (int i = 0; i < TOTAL_TIME / AVE_LENGTH; i++)
	{
		proc.push_back(data{ rand() % TOTAL_TIME , 
			AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2) + 4,
			rand() % 10 });

//		proc[rand() % TOTAL_TIME] = AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2);
//		cout << rand() % TOTAL_TIME << " ";
//		cout << AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2) << " ";
//		cout << rand() % 10 << endl;
	}

	for (int i = 0; i < TOTAL_TIME; i++)
		for (auto p : proc)
			if (p.time == i) cout << i << " " << p.length << " " << p.priority << endl;
	cout << "-1 -1 -1";
}

bool GetProcess(int current_time, int * length, int *priority, bool *end_of_schedule)
{
	static int number_of_process = 0;
	static bool end_of_process = false;
	static bool have_process = false;
	static int proc_arrive_time = 0;
	static int proc_length = 0;
	static int proc_priority = 0;

	if (true == end_of_process) {
		*length = *priority = 0;
		*end_of_schedule = true;
		return false;
	}

	if (false == have_process) {
		cin >> proc_arrive_time >> proc_length >> proc_priority;
		have_process = true;
	}

	if (proc_arrive_time > current_time) {
		*length = *priority = 0;
		*end_of_schedule = false;
		return false;
	}

	if (-1 == proc_arrive_time) 	{
		end_of_process = true;
		*length = *priority = 0;
		*end_of_schedule = true;
		return false;
	}

	*length = proc_length;
	*priority = proc_priority;
	*end_of_schedule = false;
	have_process = false;
	return true;
}

void FCFS()
{
	int current_time = 0;
	queue <PCB *> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.front();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		 if (nullptr != current_process) {
			current_process->executed_Length++;
//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		 }
//		 else { cout << "PAUSE\n";  }

		current_time++;
	}
	
	cout << "Total Execution Time = " << current_time << endl;
	cout 
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

struct length_Greater 
{
	bool operator()(PCB *a, PCB *b) 
	{
		return a->length > b->length;
	}
};

void SJF()
{
	int current_time = 0;
	priority_queue <PCB *, vector<PCB *>, length_Greater> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.top();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

void SRF()
{
	int current_time = 0;
	priority_queue <PCB *, vector<PCB *>, length_Greater> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
			else
			{
				ready_queue.push(new PCB{ current_process->PID, current_process->arrive_time, current_process->length, current_process->executed_Length, current_process->priority });
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.top();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

struct priority_Greater
{
	bool operator()(PCB *a, PCB *b)
	{
		return b->priority > a->priority;
	}
};

//Non-preemptive priority schedule
void NonPreemptivePrioritySchedule()	
{
	int current_time = 0;
	priority_queue <PCB *, vector<PCB *>, priority_Greater> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.top();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

void PreemptivePrioritySchedule()
{
	int current_time = 0;
	priority_queue <PCB *, vector<PCB *>, priority_Greater> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
			else
			{
				ready_queue.push(new PCB{ current_process->PID, current_process->arrive_time, current_process->length, current_process->executed_Length, current_process->priority });
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.top();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}

void RoundRobin()
{
	int current_time = 0;
	queue <PCB *> ready_queue;
	PCB *current_process = nullptr;
	int total_return_time = 0;
	int total_wait_time = 0;
	int total_process = 0;
	int total_response_time = 0;
	int pid = 1;
	int timeslice = 2;

	for (;;) {
		int length, priority;
		bool end_of_schedule;

		while (true == GetProcess(current_time, &length, &priority, &end_of_schedule))
		{
			ready_queue.push(new PCB{ pid++, current_time, length, 0, priority });
		}

		if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
			else if (current_time % timeslice == 0)
			{
				ready_queue.push(new PCB{ current_process->PID, current_process->arrive_time, current_process->length, current_process->executed_Length, current_process->priority });
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == ready_queue.empty())
			{
				current_process = ready_queue.front();
				ready_queue.pop();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && ready_queue.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
			//			cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
		//		 else { cout << "PAUSE\n";  }

		current_time++;
	}

	cout << "Total Execution Time = " << current_time << endl;
	cout
		<< "Number of Processes Executed = " << total_process << endl;
	cout << "Average Return Time = " << total_return_time / total_process << endl;
	cout << "Average Wait Time = " << total_wait_time / total_process << endl;
	cout << "Average Response Time = " << total_response_time / total_process << endl;
}


int main()
{
	//GenerateProcess();
	RoundRobin();
}