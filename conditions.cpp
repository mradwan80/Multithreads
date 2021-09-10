//thread sleeps, until notified//

#include <thread>
#include <mutex>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

stack<int> S;

mutex mtx_push;
mutex mtx_pop;

mutex mtx;
condition_variable cond;

void stack_pop()
{
	
	
	unique_lock<mutex> ulk(mtx);
	cond.wait(ulk);					//automatically unlocks the lock !!! waits for notify(), and the lock is re-acquired then. //

	int val = S.top();
	S.pop();
	cout << "value: " << val << "\n";


}

void stack_push(int val)
{
	unique_lock<mutex> ulk(mtx);

	S.push(val);
	cond.notify_one();


}

int main()
{

	int n = 20;
	vector<thread*> threads(n);

	for (int i = 0; i < n / 2; i++)
	{
		threads[i] = new thread(stack_pop);
	}
	for (int i = n / 2; i < n; i++)
	{
		threads[i] = new thread(stack_push, i);
	}

	for (int i = 0; i < n; i++)
		threads[i]->join();



	
}