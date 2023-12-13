#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<string> read_file_lines(const string &path) {
    std::fstream file(path);
    string line;
    vector<string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

size_t extract_num(const string &box) {
    int start = box.find_first_of("0123456789");
    int end = box.find_first_not_of("0123456789", start);
    return std::stoi(box.substr(start, end - start));
}

size_t check_sum(const string &box) {
    size_t sum = 0;

    if (box.find_first_not_of(".0123456789") != string::npos) {
        sum += extract_num(box);
    }

    return sum;
}


static std::unordered_map<int, int> star_loc_num_pairs;

void solve(const vector<string> &input) {
    int sum_basic = 0;
    int sum_gear_ratio = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            int start = -1;
            int len = -1;
            if (isdigit(input[i][j])) {
                start = j;
                j++;
                while (isdigit(input[i][j])) {
                    j++;
                }
                len = j - start;
            }

            if (start != -1) {
                string box = "";
                size_t line_start = std::max(start - 1, 0);
                size_t line_end = len + 2 >= input[i].size() ? string::npos : len + 2;


                int star_loc = -1;

                if (i > 0) {
                    string box_top = input[i - 1].substr(line_start, line_end);
                    if (box_top.find("*") != string::npos) {
                        star_loc = input[i - 1].find("*", line_start) + (input[i - 1].size() * (i - 1));
                    }
                    box.append(box_top);
                }

                if (input[i].substr(line_start, line_end).find("*") != string::npos && star_loc == -1) {
                    star_loc = input[i].find("*", line_start) + (input[i].size() * i);
                }
                box.append(input[i].substr(line_start, line_end));

                if (i < input.size() - 1) {
                    string box_bottom = input[i + 1].substr(line_start, line_end);
                    if (box_bottom.find("*") != string::npos) {
                        star_loc = input[i + 1].find("*", line_start) + (input[i + 1].size() * (i + 1));
                    }
                    box.append(box_bottom);
                }

                if (star_loc != -1) {
                    if (star_loc_num_pairs.count(star_loc) > 0) {
                        cout << "star_loc = " << star_loc << ": multiply " << star_loc_num_pairs[star_loc] << " and " << extract_num(box) << endl;
                        sum_gear_ratio += star_loc_num_pairs[star_loc] * extract_num(box);
                        star_loc_num_pairs[star_loc] = extract_num(box);
                    } else {
                        star_loc_num_pairs.try_emplace(star_loc, extract_num(box));
                    }

                }

                sum_basic += check_sum(box);

                start = -1;
                len = -1;



            }
        }
    }

    cout << "sum part nums = " << sum_basic << endl;
    cout << "sum gear ratios = " << sum_gear_ratio << endl;
}

int main(int argc, char *argv[]) {
    printf("day3\n");
    vector<string> input = read_file_lines("input.txt");
    solve(input);

    return 0;
}
