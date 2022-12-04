#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

struct Node {
  std::unordered_map<char, int> next; // transition edges
  bool is_terminal;
  int suff_ref;
  int exit_link = -1;
  int id; // idx in data_
};

class PrefixTree {
  std::vector<std::string> vocabl_;
  std::vector<Node> data_;
 public:

  void Insert(std::string& str, std::unordered_map<int, std::string>& term) {
    int j = 0;
    int id;
    for (auto symbol : str) {
      auto next_id = data_[j].next.find(symbol);
      data_[j].id = j;
      if (next_id == data_[j].next.end()) {
        data_.push_back(Node{});
        data_[j].next.insert(std::pair{symbol, static_cast<int>(data_.size()) - 1});
        id = static_cast<int>(data_.size()) - 1;
      } else {
        id = next_id->second;
      }
      j = id;
    }
    data_[j].is_terminal = true;
    data_[j].id = j;
    term.insert({j, str});
  }

  struct Third {
    char symbol;
    int parent;
    int node;
  };

  void TrieBuildSuffixReferences() { // this functioin uses BFS
    data_[0].suff_ref = -1;
    std::queue<Third> node_queue;
    for (auto i : data_[0].next) {
      node_queue.push(Third{i.first, 0, i.second}); // Firstly, parent is root
    }
    while (!node_queue.empty()) {
      auto third = node_queue.front();
      node_queue.pop();
      int suff = data_[third.parent].suff_ref;
      while (suff != -1 && data_[suff].next.find(third.symbol) == data_[suff].next.end()) {
        suff = data_[suff].suff_ref;
      }
      data_[third.node].suff_ref = (suff == -1 ? 0 : data_[suff].next[third.symbol]);
      for (auto h : data_[third.node].next) {  // put to queue the node's neighbors
        node_queue.push(Third{h.first, third.node, h.second});
      }
    }
  }

  void TrieBuildExitLinks() {
    data_[0].exit_link = -1;
    std::queue<int> queue_node;
    for (auto& i : data_[0].next) {
      data_[i.second].exit_link = -1;
      queue_node.push(i.second);
    }
    while (!queue_node.empty()) {
      auto node = queue_node.front();
      queue_node.pop();
      int suff = data_[node].suff_ref;
      if (suff != 0) {
        data_[node].exit_link = (data_[suff].is_terminal ? suff : data_[suff].exit_link);
      }
      for (auto& neighbor : data_[node].next) {
        queue_node.push(neighbor.second);
      }
    }
  }

  PrefixTree(std::vector<std::string>& v, std::unordered_map<int, std::string>& term) : vocabl_(v) {
    data_.push_back(Node{});
    data_[0].id = 0;
    int k = 0;
    for (auto& str : vocabl_) {
      this->Insert(str, term); // insert string from vocabulary
    }
    this->TrieBuildSuffixReferences(); // Do suff_reference
    this->TrieBuildExitLinks(); // Do exit_links
  }

  bool Find_str(std::string& str) {
    auto node = data_[0];   // root
    for (auto&& symbol : str) {
      auto next_id = node.next.find(symbol);
      if (next_id == node.next.end()) {
        return false;
      }
      node = data_[next_id->second];
    }
    return node.is_terminal;
  }

  void Print() const {
    for (int i = 0; i < data_.size(); i++) {
      std::cout << i << " " << data_[i].suff_ref << " " << data_[i].exit_link << " " << data_[i].is_terminal << " #####\n" ;
      for (auto d : data_[i].next) {
        std::cout << d.first << " " << d.second << " ";
      }
      std::cout << "\n__________________\n";
    }
  }

  /*int NextState(int node, char symbol) {
    while (node != -1 && data_[node].next.find(symbol) == data_[node].next.end()) {
      node = data_[node].suff_ref;
    }
    return (node == -1) ? 0 : data_[node].next[symbol];
  }
*/

  void Terminal(std::string& str, std::unordered_map<int, std::string>& term, int node, std::unordered_map<std::string, std::pair<int, int>>& result_data, int i) {
    if (data_[node].is_terminal) {  // the first position
      if (result_data[term[node]].first == 0) {
        result_data[term[node]].second = i - static_cast<int>(term[node].size()) + 1;
        result_data[term[node]].first++;
        //result_data[term[node]].second = 1 + node - static_cast<int>(term[node].size());
      } else {
        result_data[term[node]].first++;
        result_data[term[node]].second = std::min(result_data[term[node]].second, i);
      }
    }
  }
/*
  void PrintEntries(int node) {
    if (!data_[node].is_terminal) {
      node = data_[node].exit_link;
    }
    while (node != -1) {

      node = data_[node].exit_link;
    }
  }*/

  std::unordered_map<std::string, std::pair<int, int>> AhoCorasick(std::string& str, std::unordered_map<int, std::string>& term) {
    std::unordered_map<std::string, std::pair<int, int>> result_data;
    for (int i = 0; i < vocabl_.size(); ++i) {
      result_data.emplace(std::pair{vocabl_[i], std::pair{0, 0}});
    }
    int node = 0;
    for (int i = 0; i < str.size(); i++) {

      Terminal(str, term, node, result_data, i);

      if (node != -1) {
        int exit = data_[node].exit_link;
        while (exit != -1) {
          Terminal(str, term, exit, result_data, i);
          exit = data_[exit].exit_link;
        }
      }

      while (node != -1 && data_[node].next.find(str[i]) == data_[node].next.end()) {
        node = data_[node].suff_ref;
      }
      if (node != -1 && data_[node].next.find(str[i]) != data_[node].next.end()) {
        node = data_[node].next.find(str[i])->second;
      }
      if (node == -1 && data_[0].next.find(str[i]) != data_[0].next.end()) {
        node = data_[0].next.find(str[i])->second;
      }
    }
    return result_data;
  }
};

int main() {
  std::string T;
  std::cin >> T;
  T = T + "*";
  int n;
  std::cin >> n;
  std::vector<std::string> v (n);

  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  std::unordered_map<int, std::string> term(n);

  PrefixTree tree(v, term); // the reference to vocabulary

  //tree.Print();
  //std::cout << "\n";
  auto result = tree.AhoCorasick(T, term);
  //std::cout << "\n";
  for (auto& i : v) {
    std::cout << result[i].first << " " << result[i].second << "\n";
  }
  return 0;
}
// Выводит кол-во вхождений кажлого образца и индекс самого первого вхождения
