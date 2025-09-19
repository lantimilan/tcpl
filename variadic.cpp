// variadic.cpp
#include <iostream>

template<typename T>
void op(T val)
{
  std::cout << val << std::endl;
}

void f()
{
  std::cout << "--->basecase" << std::endl;
}

template<typename T, typename... Tail>
void f(T head, Tail... tail)
{
  op(head);
  f(tail...);
}

int main()
{
  std::cout << "first:\n";
  f(1, 2.2, "hello");

  std::cout << "second:\n";
  f(0.2, 'c', "yuck!", 0, 1, 2);
}
