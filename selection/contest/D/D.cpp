#include <iostream>
#include <vector>
#include <tuple>

using ddvector = std::vector<std::string>;
using ddtuple = std::tuple<int, int, char>;


void fill(ddvector& data, std::vector<ddtuple>& queue, ddtuple& args) {
    int x = std::get<0>(args), y = std::get<1>(args);
    char cur = std::get<2>(args);

    if (x >= data.size() || y >= data[x].size()) return;
    if (data[x][y] != '.' && cur != 'S') return;
    data[x][y] = cur;
    if (cur != 'U')
        queue.emplace_back(std::make_tuple(x - 1, y, 'D'));
    if (cur != 'D')
        queue.emplace_back(std::make_tuple(x + 1, y, 'U'));
    if (cur != 'L')
        queue.emplace_back(std::make_tuple(x, y - 1, 'R'));
    if (cur != 'R')
        queue.emplace_back(std::make_tuple(x, y + 1, 'L'));
}


int main() {
    int n, m;
    std::cin >> n >> m;
    ddvector data;

    std::vector<ddtuple> queue;

    for (int i = 0; i < n; i++) {
        std::string tmp;
        std::cin >> tmp;
        data.push_back(tmp);
        for (int j = 0; j < m; j++) {
            if (data[i][j] == 'S') {
                queue.emplace_back(std::make_tuple(i, j, 'S'));
            }
        }
    }
    while (!queue.empty()) {
        auto tmp = queue.back();
        queue.pop_back();
        fill(data, queue, tmp);
    }

    for (auto& line: data) {
        std::cout << line << std::endl;
    }
    return 0;
}