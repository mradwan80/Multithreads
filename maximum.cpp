//very slow

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

void MaxOfTwo(vector<float>& values, int threadid, int n, int j)
{
	int index1 = threadid * j * 2;
	int index2 = index1 + j;

	if (index1 >= n || index2 >= n)
		return;

	//swapping is also possible. use it if ok to have same values but order changed.
	/*if (values[index1] < values[index2])
	{
		float tmp = values[index1];
		values[index1] = values[index2];
		values[index2] = tmp;
	}*/

	if (values[index1] < values[index2])
		values[index1] = values[index2];


}


int main()
{
	int n = 100000;
	vector<float>values(n);
	for (int i = 0; i < n; i++)
	{
		values[i] = -0.005*i*i + 4 * i + 10; //max is *//
	}
	
	//for testing purposes
	//for (int i = 0; i < n; i++)
	//for (int i = 0; i < 10; i++)
	//	cout << values[i] << "\n";

	////////
	////////
	////////

	auto start_lsearch = high_resolution_clock::now();
	float max = std::numeric_limits<float>::lowest();
	int maxind;
	for (int i = 0; i < n; i++)
	{
		if (values[i] > max)
		{
			max = values[i];
			maxind = i;
		}
	}
	auto end_lsearch = high_resolution_clock::now();
	

	////////
	////////
	////////


	auto start_threads = high_resolution_clock::now();
	
	int threadsnum = n / 2;
	vector<thread*> threads(threadsnum, nullptr);

	for (int j = 1; j <n ; j *= 2)
	//for (int j = 1; j <8; j *= 2) //for testing purposes
	{
		for (int i = 0; i < threadsnum / j; i++)
		{
			threads[i] = new thread(MaxOfTwo, ref(values), i, n, j);
			threads[i]->join();
			delete threads[i];
		}
	}
	auto end_threads = high_resolution_clock::now();
	
	//cout << values[0] << "," << values[2] << "," << values[4] << "," << values[6] << "\n"; //for testing purposes

	////////
	////////
	////////

	cout << "(linear search) maximum value is " << max << ", at index " << maxind << "\n";
	cout << "(threads) maximum value is " << values[0] << "\n";
	
	auto duration_lsearch = duration_cast<milliseconds>(end_lsearch - start_lsearch);
	auto duration_threads = duration_cast<milliseconds>(end_threads - start_threads);
	cout << "linear search took " << duration_lsearch.count() << " milliseconds\n";
	cout << "threads took " << duration_threads.count() << " milliseconds\n";
	
	


	return 1;
}
