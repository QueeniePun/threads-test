#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

void doTask(const long long int timeInMilliseconds, const int &taskId, const int &consumerId)
{
    auto start = chrono::steady_clock::now();

    this_thread::sleep_for(std::chrono::milliseconds(timeInMilliseconds));

    auto end = chrono::steady_clock::now();
    cout << "Consumer Thread " << consumerId << " completed Task " << taskId << ". Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms. \n";

}


void doProduction(queue<int> &q, std::mutex &numbersMutex)
{
    
    // attempt to add element to a data structure 
    int taskId = 1;
    while (true)
    {
        numbersMutex.lock();
        q.push(taskId);
        int qSize = q.size();
        cout << "doProduction() Queue size: " << qSize << endl;
        cout << "doProduction() Task ID: " << q.back() << " added to queue." << endl;
        taskId++;
        numbersMutex.unlock();

        if (qSize > 10)
        {
            this_thread::sleep_for(std::chrono::milliseconds(200));
        }  
    } 
}


void doConsumption(queue<int> &q, std::mutex &numbersMutex, int consumerId)
{
    // look at data structure and see what is available to be done
    while (true) 
    {
        numbersMutex.lock();

        if (!q.empty()) 
        {
            int num = rand() % 1000;
            int taskId = q.front();
            q.pop();
            numbersMutex.unlock();
            cout << "doConsumption() Task ID: " << taskId << " removed from queue." << endl;
            cout << "doConsumption() Updated Queue size: " << q.size() << endl;
            doTask(num, std::ref(taskId), consumerId);
            continue; // skip, redundant unlock
        }
        numbersMutex.unlock();
    }
}

int main()
{
    queue<int> numbers;
    std::mutex numbersMutex;
    thread producer = thread(doProduction, std::ref(numbers), std::ref(numbersMutex));
    cout << "Producer thread created. \n";
    thread consumer1 = thread(doConsumption, std::ref(numbers), std::ref(numbersMutex), 1);
    cout << "Consumer thread 1 created. \n";
    thread consumer2 = thread(doConsumption, std::ref(numbers), std::ref(numbersMutex), 2);
    cout << "Consumer thread 2 created. \n";
    thread consumer3 = thread(doConsumption, std::ref(numbers), std::ref(numbersMutex), 3);
    cout << "Consumer thread 3 created. \n";
    thread consumer4 = thread(doConsumption, std::ref(numbers), std::ref(numbersMutex), 4);
    cout << "Consumer thread 4 created. \n";
    thread consumer5 = thread(doConsumption, std::ref(numbers), std::ref(numbersMutex), 5);
    cout << "Consumer thread 5 created. \n";

    // These are blocking because each thread is an infinite loop.
    producer.join(); 
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();


    return 0;
}
