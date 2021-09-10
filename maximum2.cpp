//faster than maximum.cpp, but still slower than linear search, even with bigger n and different threads num (tried 2,4,10).//

#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void GetMax(vector<float> values, vector<float>&maxs, int tid, int start, int end)
{
	float max = numeric_limits<float>::lowest();
	for (int i = start; i <= end; i++)
	{
		if (values[i] > max)
			max = values[i];
	}
	maxs[tid] = max;

}

int main()
{
	int n = 10000000;
	vector<float>values(n);
	for (int i = 0; i < n; i++)
	{
		values[i] = -0.005*i*i + 4 * i + 10; //max is *//
	}
	
	////////
	////////
	////////

	auto start_lsearch = high_resolution_clock::now();

	float max_lsearch = std::numeric_limits<float>::lowest();
	int maxind;
	for (int i = 0; i < n; i++)
	{
		if (values[i] > max_lsearch)
		{
			max_lsearch = values[i];
			maxind = i;
		}
	}
	auto end_lsearch = high_resolution_clock::now();


	////////
	////////
	////////

	auto start_threads = high_resolution_clock::now();

	int div = 4;
	vector<thread*>threads(div);

	vector<int>starts(div);
	vector<int>ends(div);
	vector<float>maxs(div);

	starts[0] = 0;
	ends[0] = n / div;
	
	for (int i = 1; i < div; i++)
	{
		starts[i] = ends[i - 1] + 1;
		ends[i] = ends[i - 1] + n / div;
	}

	if (ends[div - 1] >= n) ends[div-1] = n - 1;

	for (int i = 0; i < div; i++)
	{
		threads[i] = new thread(GetMax, values, ref(maxs), i, starts[i], ends[i]);
		threads[i]->join();
	}

	float max_threads = numeric_limits<float>::lowest();
	for (int i = 0; i < div; i++)
	{
		if (maxs[i] > max_threads)
			max_threads = maxs[i];
	}

	auto end_threads = high_resolution_clock::now();

	////////
	////////
	////////

	cout << "(linear search) maximum value is " << max_lsearch << ", at index " << maxind << "\n";
	cout << "(threads) maximum value is " << max_threads << "\n";

	auto duration_lsearch = duration_cast<milliseconds>(end_lsearch - start_lsearch);
	auto duration_threads = duration_cast<milliseconds>(end_threads - start_threads);
	cout << "linear search took " << duration_lsearch.count() << " milliseconds\n";
	cout << "threads took " << duration_threads.count() << " milliseconds\n";




	return 1;
}