#include <iostream>
#include <map>


void fill_counter(std::map<char, int>& counter, std::string& s) {
    for (auto c: s) {
        counter[c]++;
    }
}


int main() {
    std::string a, b;
    std::map<char, int> counter;
    std::cin >> a >> b;
    size_t n = a.length();
    std::string res(n, 'I');
    fill_counter(counter, a);
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            res[i] = 'P';
            counter[a[i]]--;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (res[i] == 'P')
            continue;
        if (counter[b[i]] > 0) {
            counter[b[i]] -= 1;
            res[i] = 'S';
        }
    }
    std::cout << res << std::endl;
    return 0;
}