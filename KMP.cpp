    #include <iostream>
    #include <string>
    #include <vector>
     
    void Pref_func(const std::string& s, std::vector<int>& data) {
      for (int i = 1; i < s.size(); ++i) {
        int k = data[i - 1];
        while (s[i] != s[k] && k > 0) {
          k = data[k - 1];
        }
        if (s[i] == s[k]) {
          data[i] = k + 1;
        }
      }
    }
     
    void KMP(std::vector<int>& data, std::string& p, std::pair<int, std::vector<int>>& pair) {
      int count = 0;
      for (int i = p.size() + 1; i < data.size(); ++i) {
        if (data[i] == p.size()) {
          count++;
          pair.second.push_back(i - 2 * p.size() + 1);
        }
      }
      pair.first = count;
    }
     
    int main() {
      std::string S, p, s;
      std::cin >> S >> p;
      s = p + '#' + S;
      std::vector<int> data(s.size(), 0);
      Pref_func(s, data);
      std::pair<int, std::vector<int>> result = {0, std::vector<int> (0)};
      KMP(data, p, result);
      std::cout << result.first << "\n";
      if (result.first > 0) {
        for (int i : result.second) {
          std::cout << i << " ";
        }
      }
      return 0;
    }
     
    // Trifonov Stepan B05-106
