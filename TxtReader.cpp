#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Task.cpp"

using namespace std;

class TxtReader
{
public:
	int _number_of_task;
	int _counter;
	vector<Task> _tasks;

	TxtReader(int number_of_task, int counter, vector<Task> tasks)
	{
		this->_number_of_task = number_of_task;
		this->_counter = counter;
		this->_tasks = tasks;
	}
};