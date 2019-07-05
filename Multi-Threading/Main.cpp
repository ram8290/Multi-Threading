#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

string globalStr;
mutex mut;

void workerFunc(int num)
{
	mut.lock();
	globalStr += "\nThread #" + to_string(num);
	mut.unlock();
}

int main ()
{
	const int NUMTHREADS = 10;
	thread threads[NUMTHREADS];

	cout << "\nMain thread pausing...\n";

	for(int i=0; i< NUMTHREADS;i++)
	{
		threads[i] = thread(&workerFunc, (i+1));
	}

	for (thread& t : threads)
	{
		t.join();
	}

	cout << "\n\nMain thread back online\n";
	cout << globalStr << endl;


	system("pause");
	return 0;
}
