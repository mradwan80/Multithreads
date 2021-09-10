//trying different ways to use a mutex//

#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

mutex mtx;

void fnc1(int id)
{
	for (int i = 0; i < 20; i++)
		cout << "function run from thread " << id << "\n";

}

void fnc2(int id)
{
	mtx.lock();

	for (int i = 0; i < 20; i++)
		cout << "function run from thread " << id << "\n";

	mtx.unlock();
}


void fnc3(int id)
{
	lock_guard<mutex> lk(mtx);

	for (int i = 0; i < 20; i++)
		cout << "function run from thread " << id << "\n";

}

void fnc4(int id)
{
	unique_lock<mutex> ulk(mtx);

	//unique_lock<mutex> ulk(mtx, defer_lock); //possible//
	//ulk.lock()

	for (int i = 0; i < 20; i++)
		cout << "function run from thread " << id << "\n";

	//ulk.unlock(); //optional//

}

int main()
{

	/*thread th1(fnc1, 1);
	thread th2(fnc1, 2);
	thread th3(fnc1, 3);
	th1.join();
	th2.join();
	th3.join();
	
	thread th1(fnc2, 1);
	thread th2(fnc2, 2);
	thread th3(fnc2, 3);
	th1.join();
	th2.join();
	th3.join();


	thread th1(fnc3, 1);
	thread th2(fnc3, 2);
	thread th3(fnc3, 3);
	th1.join();
	th2.join();
	th3.join();*/

	thread th1(fnc4, 1);
	thread th2(fnc4, 2);
	thread th3(fnc4, 3);
	th1.join();
	th2.join();
	th3.join();


}