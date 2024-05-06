#include <iostream>
#include "TxtReader.cpp"
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

TxtReader readData(string file_path)
{
	ifstream infile(file_path);
	int iterator = 0;
	int numerator = 1;
	string line;
	vector<Task> file_tasks;

	if (!infile.is_open()) {
		cout << "Nie mo¿na otworzyæ pliku." << endl;
		return TxtReader(0, 0, file_tasks);
	}
	else
		cout << "Poprawnie wczytano plik" << endl;

	while (getline(infile, line)) {
		istringstream iss(line);
		int a, b, c;
		if (!(iss >> a >> b >> c)) {
			break;
		}

		file_tasks.push_back(Task(a, b, c, numerator));
		iterator++;
		numerator++;
	}

	return TxtReader(1, iterator, file_tasks);
}

void sortVectorByRequiriedTimeDescending(vector<Task>& myVector) {
	sort(myVector.begin(), myVector.end(), [](const Task& a, const Task& b) 
	{
		return a.requriedTime < b.requriedTime;
	});
}

void showData(vector<Task>& tasks)
{
	cout << endl;
	for (int i = 0; i < tasks.size(); i++)
	{
		cout <<tasks[i].workTime << " " << tasks[i].weight << " " << tasks[i].requriedTime << endl;
	}
}


void showOrderData(vector<Task>& tasks)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		cout << tasks[i].number_of_task << " ";
	}
}


int calcPunishment(vector<Task> tasks)
{
	int punishment = 0;
	int time = 0;
	
	for (int i = 0; i < tasks.size(); i++)
	{
		time += tasks[i].workTime;
		if (tasks[i].requriedTime < time)
			punishment += (time - tasks[i].requriedTime) * tasks[i].weight;
	}

	return punishment;
}

int calcSingularPunishment(vector<Task> tasks, int index)
{
	int punishment = 0;
	int time = 0;

	Task task = tasks[index];

	for (int i = 0; i < index + 1; i++)
	{
		time += tasks[i].workTime;
	}

	if (tasks[index].requriedTime < time)
		punishment += (time - tasks[index].requriedTime) * tasks[index].weight;

	return punishment;
}

int sollution1(vector<Task> &tasks)
{
	sortVectorByRequiriedTimeDescending(tasks);

	for (int j = 0; j < tasks.size(); j++)
	{
		vector<int> pushmentValues = vector<int>();

		for (int i = 0; i < tasks.size() - j; i++)
		{
			Task temp = tasks[i];
			pushmentValues.push_back(calcSingularPunishment(tasks, i));
		}

		int minValue = 100000;
		int idx = -1;
		for (int k = 0; k < pushmentValues.size(); k++)
		{
			if (minValue >= pushmentValues[k])
			{
				minValue = pushmentValues[k];
				idx = k;
			}
		}

		pushmentValues.clear();
		Task temp = tasks[idx];
		tasks.erase(tasks.begin() + idx);
		tasks.insert(tasks.end() - j, temp);
	}

	return 0;
}


int main()
{
	TxtReader data = readData("zadanie11.txt");
	showData(data._tasks);

	sollution1(data._tasks);
	showData(data._tasks);

	showOrderData(data._tasks);
	cout << endl << "kara: " << calcPunishment(data._tasks);
	
}
 

///lczymy maksymalne kary dla tasków (sa na ostatniej pozycji), potem sortujemy je po karze

//1. Liczymy potrzebny czas wykonania wszystkich taskó
//liczymy karê dla tego koñcowego czasu dla wszystkich tasków 
//Sortujemy
//Usuwamy ten task dla którego wyjdzie najmniejsza kara
//Odejmujemy czas wykonania tego tasku od czasu koñcowego
//I robimy to jeszcze raz a¿ czas dojdzie do 0