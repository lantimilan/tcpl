// priority_queue.cpp
#include <queue>
#include <string>
#include <iostream>
#include <vector>

struct Person {
  std::string firstName;
  std::string lastName;

  Person(const std::string& s1, const std::string& s2) : firstName(s1), lastName(s2) {}
};

bool operator<(const Person& p1, const Person& p2)
{
  if (p1.lastName != p2.lastName) return p1.lastName < p2.lastName;
  return p1.firstName < p2.firstName;
}

bool operator==(const Person& p1, const Person& p2)
{
  return p1.firstName == p2.firstName && p1.lastName == p2.lastName;
}

bool operator>(const Person& p1, const Person& p2)
{
  return !(p1 < p2 || p1 == p2);
}

int main()
{
  std::priority_queue<Person, std::vector<Person>, std::greater<Person>> pq;
  pq.push(Person("John", "Kennedy"));
  pq.push(Person("George", "Washington"));
  pq.push(Person("Abraham", "Lincohn"));
  pq.push(Person("Bill", "Clinton"));

  while (!pq.empty()) {
    Person p = pq.top();
    pq.pop();
    std::cout << p.firstName << " " << p.lastName << std::endl;
  }
}
