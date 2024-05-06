#include <iostream>
using namespace std;

class Task
{
public:
	int workTime;
	int weight;
	int requriedTime;
	int number_of_task;

	Task(int workTime, int weight, int requriedTime, int number_of_task)
	{
		this->workTime = workTime;
		this->weight = weight;
		this->requriedTime = requriedTime;
		this->number_of_task = number_of_task;
	}
};