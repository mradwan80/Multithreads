
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

mutex mtx;
std::once_flag flag;

void fnc(int id)
{
	unique_lock<mutex> ulk(mtx);

	cout<<"fnc called from thread " << id << "\n";

	std::call_once(flag, [id]() {cout << "one time call from thread " << id << "\n"; });
}

int main()
{
	int n = 20;
	vector<thread*>threads(n);
	for (int i = 0; i < n; i++)
		threads[i] = new thread(fnc, i);

	for (int i = 0; i < n; i++)
		threads[i]->join();


}