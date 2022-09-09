#include <iostream>
#include <tuple>
#include "json.hpp"

using json = nlohmann::json;
using date = std::tuple<int, int, int>;


date str_to_date(const std::string& s) {
    int y, m, d;
    char tmp;
    std::stringstream stream(s);
    stream >> d >> tmp >> m >> tmp >> y;
    return {y, m, d};
}


void to_lower_str(std::string& s) {
    for (auto& c: s) {
        c = std::tolower(c);
    }
}


int main() {
    std::string s;
    std::getline(std::cin, s);
    json json_data = json::parse(s);
    json res = json::array();
    std::unordered_map<std::string, std::string> raw_filters;

    for (int i = 0; i < 5; i++) {
        std::string cur_filter, value;
        std::cin >> cur_filter >> value;
        raw_filters[cur_filter] = value;
    }

    std::string name_contains = raw_filters["NAME_CONTAINS"];
    to_lower_str(name_contains);
    int price_gt = std::stoi(raw_filters["PRICE_GREATER_THAN"]);
    int price_lt = std::stoi(raw_filters["PRICE_LESS_THAN"]);
    date date_after = str_to_date(raw_filters["DATE_AFTER"]);
    date date_before = str_to_date(raw_filters["DATE_BEFORE"]);

    std::copy_if(json_data.begin(), json_data.end(), std::back_inserter(res),
                 [name_contains, price_gt, price_lt, date_after, date_before](json js){
        std::string s = js["name"].get<std::string>();
        to_lower_str(s);
        int price =  js["price"].get<int>();
        date dt = str_to_date(js["date"].get<std::string>());
        return
            s.find(name_contains) != std::string::npos
            && price_gt <= price && price <= price_lt
            && date_after <= dt && dt <= date_before
        ;
    });
    std::sort(res.begin(), res.end(), [](const json& lhs, const json& rhs){return lhs["id"].get<int>() < rhs["id"].get<int>();});

    std::cout << res.dump() << std::endl;
    return 0;
}