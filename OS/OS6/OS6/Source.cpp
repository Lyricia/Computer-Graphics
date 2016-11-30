#include <iostream>
#include <list>

using namespace std;

const int NumberOfCPU = 4;

struct PCB {
	int PID;
	int arrive_time;
	int running_length;
	int executed_Length;
	int memorysize;
	int memorystartidx;
	bool IsAlloc;
};

int current_time;

bool MEMORYARRAY[512];			//false empty			true filled

void GenerateProcess()
{
	struct data {
		int time;
		int running_length;
		int memorysize;
	};

	list <data> proc;

	const int TOTAL_TIME = 10000;
	const int AVE_LENGTH = 10;

	for (int i = 0; i < TOTAL_TIME / AVE_LENGTH; i++)
	{
		proc.push_back(data{ rand() % TOTAL_TIME ,
			AVE_LENGTH + (rand() % AVE_LENGTH - AVE_LENGTH / 2) + 4,
			rand() % 10 });
	}

	for (int i = 0; i < TOTAL_TIME; i++)
		for (auto p : proc)
			if (p.time == i) cout << i << " " << p.running_length << " " << p.memorysize << endl;
	cout << "-1 -1 -1";
}

bool GetProcess(int current_time, int * running_length, int *memorysize, bool *end_of_schedule)
{
	static int number_of_process = 0;
	static bool end_of_process = false;
	static bool have_process = false;
	static int proc_arrive_time = 0;
	static int proc_running_length = 0;
	static int proc_memorysize = 0;

	if (true == end_of_process) {
		*running_length = *memorysize = 0;
		*end_of_schedule = true;
		return false;
	}

	if (false == have_process) {
		cin >> proc_arrive_time >> proc_running_length >> proc_memorysize;
		have_process = true;
	}

	if (proc_arrive_time > current_time) {
		*running_length = *memorysize = 0;
		*end_of_schedule = false;
		return false;
	}

	if (-1 == proc_arrive_time) 	{
		end_of_process = true;
		*running_length = *memorysize = 0;
		*end_of_schedule = true;
		return false;
	}

	*running_length = proc_running_length;
	*memorysize = proc_memorysize;
	*end_of_schedule = false;
	have_process = false;
	return true;
}

void FirstFit()
{
	int current_time = 0;
	list <PCB *> ready_list;
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
			ready_list.push_back(new PCB{ pid++, current_time, length, 0, priority });
		}
		
		if (true == ready_list.empty()){
			break;
		}

		for (auto p : ready_list)
		{
			ready_list.remove_if([](PCB* p)->bool { return p->running_length <= p->executed_Length; });

			if (p->IsAlloc == false)
			{
				for (int i = 0; i < 512; i++)
				{
					if (MEMORYARRAY[i] == false) 
					{
						for (int j = i; j < i + p->memorysize; j++) 
						{
							if (MEMORYARRAY[j] == true) 	
								break;
							else 
							{
								for (int k = i; k < i + p->memorysize; k++) 
								{
									MEMORYARRAY[k] = true;
								}
								p->memorystartidx = i;
								p->IsAlloc = true;
								p->arrive_time = current_time;
							}
						}
					}
				}
			}

			if (p->IsAlloc == true) 
			{
				if (p->running_length <= p->executed_Length) {
					//relase
					for (int i = p->memorystartidx; i < p->memorystartidx + p->memorysize; i++) {
						MEMORYARRAY[i] = false;
					}
				}
				else p->executed_Length++;
			}
		}



		/*if (nullptr != current_process)
		{
			if (current_process->executed_Length >= current_process->running_length) {
				total_return_time += current_time - current_process->arrive_time;
				total_wait_time += current_time - current_process->arrive_time - current_process->running_length;
				total_process++;
				delete current_process;
				current_process = nullptr;
			}
		}

		if (nullptr == current_process)
		{
			if (false == reday_list.empty())
			{
				current_process = reday_list.front();
				reday_list.pop_front();
				if (0 == current_process->executed_Length)
					total_response_time += current_time - current_process->arrive_time;
			}
		}

		if ((true == end_of_schedule) && reday_list.empty() && (nullptr == current_process))  break;

		if (nullptr != current_process) {
			current_process->executed_Length++;
						cout << "Time:" << current_time << "   PID" << current_process->PID << endl;
		}
				 else { cout << "PAUSE\n";  }
*/
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
}