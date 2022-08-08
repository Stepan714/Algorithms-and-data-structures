#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::vector<std::pair<std::string, std::map<std::string, int64_t>>> mymap;
  std::unordered_map<std::string, int64_t> mymap2;
  std::string name, product;
  int64_t cnt;
  int64_t c = 0;
  while (std::cin >> name && std::cin >> product && std::cin >> cnt) {
    if (mymap2.find(name) == mymap2.cend()) {
      std::map<std::string, int64_t> buf;
      buf.emplace(product, cnt);
      mymap.emplace_back(name, std::move(buf));
      mymap2.emplace(name, c++);
    } else {
      auto t = mymap[mymap2[name]].second.find(product);
      if (t == mymap[mymap2[name]].second.cend()) {
        mymap[mymap2[name]].second.emplace(product, cnt);
      } else {
        t->second += cnt;
      }
    }
  }
  std::sort(mymap.begin(), mymap.end());
  for (auto& i : mymap) {
    std::cout << i.first << ":\n";
    for (auto& k : i.second) {
      std::cout << k.first << " " << k.second << "\n";
    }
  }
  return 0;
}
