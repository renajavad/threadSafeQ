#include <mutex>
#include <queue>
#include <iostream>
#include <iomanip>
#include <thread>
class threadSafeQ{
std::queue<int> rawQ;
std::mutex m;
public:
int& retrieveAndDelete()
{
	int front_value = 0;
	m.lock();
	if(!rawQ.empty())
	{
		front_value = rawQ.front();
		rawQ.pop();
	}
	m.unlock();
	return front_value;
}

threadSafeQ(std::queue<int> rawQ)
{
    this->rawQ = rawQ;
}

void push(int val)
{
	m.lock();
	rawQ.push(val);
	m.unlock();
}
void print()
{
    m.lock();
    while (!rawQ.empty())
    {
		std::cout << rawQ.front() << "\n";
        rawQ.pop();
    }
    m.unlock();
}
};
int main()
{
std::queue<int> q;
for (int i = 0; i <= 10; i++)
{
    q.push(i);
}
threadSafeQ func(q);
std::thread funTest1(&threadSafeQ::retrieveAndDelete, &func);
std::thread funTest2(&threadSafeQ::push, &func, 11);

if(funTest1.joinable())
{
	funTest1.join();
}
if(funTest2.joinable())
{
	funTest2.join();
}

func.print();
return 0;	
}
