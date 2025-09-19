// unique_lock.cpp
#include <iostream>
#include <chrono>
#include <mutex>
using namespace std;
using namespace std::chrono;

mutex m1;
mutex m2;
mutex m3;

void f()
{
  auto t0 = high_resolution_clock::now();
  unique_lock<mutex> lck1{m1, defer_lock};
  unique_lock<mutex> lck2{m2, defer_lock};
  unique_lock<mutex> lck3{m3, defer_lock};
  lock(lck1, lck2, lck3); // acquire all three locks
  auto t1 = high_resolution_clock::now();
  cout << "acquired all three locks\n";
  cout << duration_cast<nanoseconds>(t1 - t0).count() 
          << " nanoseconds passed\n";
  // implicitly release all three locks
}

int main()
{
  f();
}
