// threads-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;



void doTask(const long long int timeInMilliseconds)
{
    auto start = chrono::steady_clock::now();

    this_thread::sleep_for(std::chrono::milliseconds(timeInMilliseconds));

    auto end = chrono::steady_clock::now();
    cout << "Task took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms. \n";

}

int main()
{
    auto startSingle = chrono::steady_clock::now();

    cout << "Single-threaded\n";
    doTask(150);
    doTask(200);
    doTask(300);
    doTask(250);
    doTask(860);

    auto endSingle = chrono::steady_clock::now(); 

    auto startMulti = chrono::steady_clock::now();
    cout << "Multi-threaded\n";
    thread thread_1 = thread(doTask, 150);
    thread thread_2 = thread(doTask, 200);
    thread thread_3 = thread(doTask, 300);
    thread thread_4 = thread(doTask, 250);
    thread thread_5 = thread(doTask, 860);
    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();
    thread_5.join();
    //thread producer = thread();
    //thread consumer = thread(); 


    auto endMulti = chrono::steady_clock::now();
    cout << "Single-threaded took " << chrono::duration_cast<chrono::milliseconds>(endSingle - startSingle).count() << "ms. \n";
    cout << "Multi-threaded took " << chrono::duration_cast<chrono::milliseconds>(endMulti - startMulti).count() << "ms. \n";

    return 0;
}
