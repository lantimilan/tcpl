// future_promise.cpp
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void comp(std::promise<int>& prom)
{
  std::this_thread::sleep_for(std::chrono::seconds(2));
  prom.set_value(123);
}

int main()
{
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();

  std::thread th{comp, std::ref(prom)};
  int result = fut.get();

  std::cout << result << std::endl;

  th.join();
}
