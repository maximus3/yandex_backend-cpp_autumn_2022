#include <iostream>
#include <fstream>

int main() {
    std::ifstream fin("input.txt");
    int idx_op = -1, idx_cl = -1;
    bool was_neg = false, was_sec_type = false;

    int cnt = 0, s_cnt = 0;
    int i = 1;
    while (true) {
        char c;
        fin >> std::noskipws >> c;
        if (fin.eof())
            break;
        if (c == '{') {
            s_cnt += 1;
            if (!was_neg && cnt == 0)
                idx_op = i;
            cnt += 1;
        }
        if (c == '}') {
            s_cnt += 1;
            cnt -= 1;
            if (!was_neg and !was_sec_type)
                idx_cl = i;
            was_sec_type = true;
            if (cnt < 0) {
                if (was_neg) {
                    std::cout << -1;
                    return 0;
                }
                was_neg = true;
                if (idx_cl == -1)
                    idx_cl = i;
                cnt = 0;
            }
        }
        i += 1;
    }
    fin.close();
    if (s_cnt % 2 == 0){
        std::cout << -1;
        return 0;
    }
    if (cnt == 0 && was_neg) {
        std::cout << idx_cl;
        return 0;
    }
    if (cnt == 1 && !was_neg){
        std::cout << idx_op;
        return 0;
    }
    std::cout << -1;
    return 0;
}