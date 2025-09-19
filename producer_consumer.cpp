// producer_consumer.cpp
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

class Message {
 public:
  Message(const std::string& d) : data(d) {}
  std::string getData() const { return data; }
 private:
  std::string data;
};

std::queue<Message> mqueue;
std::condition_variable mcond;
std::mutex mmutex;

void consumer() {
  while(true) {
    std::unique_lock<std::mutex> lck(mmutex);
    mcond.wait(lck, [] { return !mqueue.empty(); } );
//    while (mcond.wait(lck)) {
      // do nothing
//    }
    // if we are here, producer has put messages in queue and notified
    auto m = mqueue.front();
    mqueue.pop();
    lck.unlock(); // release lck because we have done on mqueue
    std::cout << "received message:" << m.getData() << std::endl;
    // will implicit unlock lck if not unlock already
  }
}

void producer() {
  int idx = 1;
  while(true) {
    Message m(std::string("idx" + std::to_string(idx++)));
    std::lock_guard<std::mutex> lck(mmutex);
    mqueue.push(m);
    mcond.notify_one();
  }
}

int main()
{
  std::thread t1{consumer};
  std::thread t2{producer};
  t1.join();
  t2.join();
}
