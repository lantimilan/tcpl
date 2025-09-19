// iterator_traits.cpp
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <forward_list>

template<typename Ran>
void sort_helper(Ran beg, Ran end, std::random_access_iterator_tag)
{
  std::cout << "sort random access iterator\n";
  return std::sort(beg, end);
}

template<typename For>
void sort_helper(For beg, For end, std::forward_iterator_tag)
{
  std::cout << "sort forward iterator\n";
  // TODO(lyan): find out how to use decltype
  // std::vector<decltype(*beg)> v{beg, end};
  std::vector<int> v{beg, end};
  std::sort(v.begin(), v.end());
  std::copy(v.begin(), v.end(), beg);
}

template<typename C>
using Iterator_type = typename C::iterator;

template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category;

template<typename C>
void sort(C& c)
{
  // note the dispatch on iterator category
  using Iter = Iterator_type<C>;
  sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
}

template<typename C>
void print(const C& c)
{
  for (const auto& e : c) {
    std::cout << e << " ";
  }
  std::cout << "\n";
}

int main()
{
  std::vector<int> v{9, 8, 7, 1, 2, 3, 6, 5, 4};
  sort(v);
  print(v);

  std::forward_list<int> l{1, 3, 5, 2, 4, 6};
  sort(l);
  print(l);
}
