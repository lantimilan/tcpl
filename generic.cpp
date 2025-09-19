// generic.cpp
#include <iostream>
#include <vector>

template<typename C, typename Oper>
void for_all(C& c, Oper oper) {
  for (auto& x : c)
    oper(x);
}

int main(int argc, char* argv[]) {
  std::vector<int> vi{9, 8, 7, 6 , 5, 4, 3, 2, 1}; 
  std::vector<std::string> vs{"aaa", "bbb", "ccc", "ddd"};

  int x = 5;
  for_all(vi, [&x](int a) { std::cout << a << " "; });
  std::cout << std::endl;

  for_all(vs, [](const std::string& s) { std::cout << s << " "; });
  std::cout << std::endl;


  for_all(vi, [&x](int& a) { a = (a < x ? a : x); }); // cap element at x
  for_all(vi, [&x](int a) { std::cout << a << " "; });
  std::cout << std::endl;
}
