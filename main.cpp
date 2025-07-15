#include <iostream>
#include <vector>
#include <type_traits>
#include <initializer_list>

class A {
public:
  std::vector<std::vector<int>> v;

  template<typename... T>
  requires (std::same_as<T, int> && ...)
  A(const std::initializer_list<T>&... l){
    (v.push_back(l), ...);
  }
};

int main (int argc, char *argv[]) {
  A a({1,2,3},{4,5,6},{7,8});

  for(auto& v : a.v){
    for(auto& i : v){
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}

