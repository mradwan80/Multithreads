//deadlock situation//

//also, use:
//lock_guard<mutex> l1(mtx1); 
//instead of :
//mtx1.lock();
//mtx1.unlock();

#include <thread>
#include <mutex>
#include <iostream>
using namespace std;



mutex mtx1;
mutex mtx2;

void write1()
{
	lock_guard<mutex> l1(mtx1);
	lock_guard<mutex> l2(mtx2);

	cout << "fnc 1\n";


}

void write2()
{
	lock_guard<mutex> l2(mtx2);
	lock_guard<mutex> l1(mtx1);

	cout << "fnc 2\n";

}

void fnc1()
{

	for (int i = 0; i < 100; i++)
		write1();

}

void fnc2()
{

	for (int i = 0; i < 100; i++)
		write2();

}

////////////
////////////
////////////

void write3()
{
	lock_guard<mutex> l1(mtx1);
	lock_guard<mutex> l2(mtx2);


	cout << "fnc 3\n";

}

void write4()
{

	lock_guard<mutex> l1(mtx1);
	lock_guard<mutex> l2(mtx2);

	cout << "fnc 4\n";

}



void fnc3()
{

	for (int i = 0; i < 100; i++)
		write3();

}

void fnc4()
{

	for (int i = 0; i < 100; i++)
		write4();

}
////////////
////////////
////////////

void write5()
{
	{
		lock_guard<mutex> l1(mtx1);
	
	}

	{
		lock_guard<mutex> l2(mtx2);
		cout << "fnc 5\n";
	}

}

void write6()
{
	{
		lock_guard<mutex> l2(mtx2);

	}

	{
		lock_guard<mutex> l1(mtx1);
		cout << "fnc 6\n";
	}
}



void fnc5()
{

	for (int i = 0; i < 100; i++)
		write5();

}

void fnc6()
{

	for (int i = 0; i < 100; i++)
		write6();

}

////////////
////////////
////////////

void write7()
{
	lock(mtx1, mtx2);

	cout << "fnc 7\n";

}

void write8()
{
	lock(mtx1, mtx2);

	cout << "fnc 8\n";

}



void fnc7()
{

	for (int i = 0; i < 100; i++)
		write7();

}

void fnc8()
{

	for (int i = 0; i < 100; i++)
		write8();

}


int main()
{

	//deadlock happens again. because we lock mtx1 then mtx2 in one function, and mtx2 then mtx1 is another//
	/*thread th1(fnc1);
	thread th2(fnc2);
	th1.join();
	th2.join();*/

	//no deadlock. because we alwaays lock mtx1 then mtx2. we do not change the order//
	/*thread th3(fnc3);
	thread th4(fnc4);
	th3.join();
	th4.join();*/

	//no deadlock. because the block of each mutex ends before the block of the next mutex starts//
	/*thread th5(fnc5);
	thread th6(fnc6);
	th5.join();
	th6.join();*/

	thread th7(fnc7);
	thread th8(fnc8);
	th7.join();
	th8.join();


	return 1;
}