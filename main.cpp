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


class pairV {
public:
  std::vector<int> fst;
  std::vector<int> snd;

  pairV(std::initializer_list<int> l, std::initializer_list<int> m) : fst(l), snd(m) {}
};

class B {
public:
  std::vector<pairV> v;

  template<typename... T>
  requires (( sizeof...(T)%2 == 0 ) && (std::same_as<T, int> && ...))
  B(const std::initializer_list<T>&... lists){
    v.reserve(sizeof...(lists)/2);
    auto lists_tuple = std::make_tuple(lists...);
    auto create_pairs = [&]<size_t... Is>(std::index_sequence<Is...>){
      (v.emplace_back(std::get<2*Is>(lists_tuple), std::get<2*Is+1>(lists_tuple)), ...);
    };
    create_pairs(std::make_index_sequence<sizeof...(lists)/2>());
  }
}

int main (int argc, char *argv[]) {
  A a({1,2,3},{4,5,6},{7,8});
  B b({1,2,3},{4,5,6},{7,8},{9,10});
  B bx({1,2,3},{4},{5,6});

  for(auto& v : a.v){
    for(auto& i : v){
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }

  for(auto& v : b.v){
    std::cout << "[{";
    for(auto& i : v.fst){
      std::cout << i << ' ';
    }

    std::cout << "}{";
    for(auto& i : v.snd){
      std::cout << i << ' ';
    }
    
    std::cout << "}]\n";
  }
  return 0;
}

