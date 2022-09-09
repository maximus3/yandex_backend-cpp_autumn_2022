#include <iostream>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <set>
#include <tuple>


using mqueue = std::set<std::tuple<int, int, std::string>>;


void replace_sep_to_space(std::string& s) {
    size_t pos = s.find(',');
    while (pos != std::string::npos) {
        s.replace(pos, 1, " ");
        pos = s.find(',', pos);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::unordered_map<std::string, std::pair<int, mqueue>> spec_data;
    std::unordered_map<std::string, std::string> cq_data;
    std::unordered_map<std::string, std::pair<int, int>> crp_data;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string data;
        std::cin >> data;
        replace_sep_to_space(data);
        std::stringstream stream(data);

        std::string s;
        int m;
        stream >> s >> m;
        spec_data[s] = std::make_pair(m, mqueue());
    }

    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::string data;
        std::cin >> data;
        replace_sep_to_space(data);
        std::stringstream stream(data);

        std::string c, q;
        int r, p;
        stream >> c >> q >> r >> p;
        cq_data[c] = q;
        crp_data[c] = std::make_pair(r, p);
    }

    std::set<std::string> res;
    for (const auto& [name, spec]: cq_data) {
        int cnt, pen;
        cnt = crp_data[name].first;
        pen = -crp_data[name].second;
        spec_data[spec].second.insert(std::tie(cnt, pen, name));
        res.insert(name);
        if (spec_data[spec].second.size() > spec_data[spec].first) {
            res.erase(std::get<2>(*spec_data[spec].second.begin()));
            spec_data[spec].second.erase(spec_data[spec].second.begin());
        }
    }

    for (const auto& s: res) {
        std::cout << s << '\n';
    }
    return 0;
}