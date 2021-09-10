//you get value using future
//you can pass a value through a future that gets the value
//a future is either attached to a promise, in which case it gets its value from the value the promise sets,
//or equals to async, in which case it gets the returned value from the function.

#include <thread>
#include <mutex>
#include <vector>
#include <stack>
#include <iostream>
#include <future>
using namespace std;

int dbl(future<int>& f)
{
	int val = f.get();
	return 2 * val;
}

int main()
{

	promise<int> prom;
	future<int> f = prom.get_future(); //parameter to be passed//

	future<int> f2 = async(dbl, ref(f)); //runs. waits for the promise//

	//do stuff//

	int input = 7;
	prom.set_value(input);

	int res = f2.get(); //getting a result//
	cout << "input and result: " << input << " " << res << "\n";





	return 1;

}