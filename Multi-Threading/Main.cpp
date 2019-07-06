#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
//this is a global variable so all threads have access to it.
string globalStr;
//creates a mutex variable so its easier to use
mutex mut;

//
void workerFunc(int num, int i)
{
	//locks this thread while its being used so no other 
	//threads works at the same time.
	mut.lock();
	//This adds the num value to the string.
	globalStr += "\nThread #" + to_string(i) + ", " + to_string(num);
	//unlocks the current thread to allow the next to work.
	mut.unlock();
}

int main ()
{
	//variable for input value.
	int num;
	//constant vaviable for how many threads there will be.
	const int NUMTHREADS = 10;
	
	//creates a thread array with 10 places.
	thread threads[NUMTHREADS];
	//introductions.
	cout << "\t\tWelcome to my Multi-Thread program\n\n";
	cout << "Here you will add number values";
	cout << "\nMain thread pausing...\n";
	//pauses to show intro.
	system("pause");
	//here runs as many threads are from 0 to 10.
	for(int i=0; i< NUMTHREADS;i++)
	{
		//clears screen to keep code clean.
		system("cls");
		//tells the person to input a value for each thread.
		cout << "Add a value to Thread #" << i + 1 << endl;
		//this checks if its a integer.
		while (!(cin >> num))
		{
			//clears the input for a retry if not a integer.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//lets the person out they input something wrong 
			//and re enter an input.
			cout << "Incorrect input, please enter again:\n";
		}
		//this adds the persons input to workFunc and 
		//sends the value
		threads[i] = thread(&workerFunc, num, i + 1);
		i - 1;
	}

	for (thread& t : threads)
	{
		t.join();
	}
	system("cls");
	//comes back online.
	cout << "\n\nMain thread back online\n";
	//prints out to the screen all the threads and there values.
	cout << globalStr << endl;

	//pauses the program so you can see all the values.
	system("pause");
	return 0;
}
