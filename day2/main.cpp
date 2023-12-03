#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;

vector<string> get_file_lines(string file_name) {
    std::fstream file(file_name);
    vector<string> res;
    string line;
    while (std::getline(file, line)) {
        res.push_back(line);
    }

    return res;
}

int get_valid_games(int r, int g, int b, vector<string> input) {

    int sum_powers = 0;

    for (string s : input) {
        struct {
            int id;
            int max_r = 0;
            int max_g = 0;
            int max_b = 0;
        } game;

        game.id = std::stoi(s.substr(s.find(' ') + 1, s.find(':') - 5));
        s.erase(0, 7 + std::to_string(game.id).length());

        size_t next_semicolon = 0;
        size_t last_semicolon = 0;
        string token;
        while ((next_semicolon = s.find("; ", last_semicolon)) != std::string::npos) {
            token = s.substr(last_semicolon, next_semicolon - last_semicolon);

            int next_comma = 0;
            string color;
            int last_comma = 0;
            while ((next_comma = token.find(", ", last_comma)) != string::npos) {
                color = token.substr(last_comma, next_comma - last_comma);

                int val = std::stoi(color.substr(0, color.find(' ')));
                string c = color.substr(color.find(' ') + 1, color.length());
                printf("%d %s\n", val, c.c_str());

                if (c == "red") {
                    game.max_r = std::max(game.max_r, val);
                } else if (c == "blue") {
                    game.max_b = std::max(game.max_b, val);
                } else if (c == "green") {
                    game.max_g = std::max(game.max_g, val);
                }

                last_comma = next_comma + 2;
            }
            // get last comma split
            color = token.substr(last_comma, next_comma - last_comma);

            int val = std::stoi(color.substr(0, color.find(' ')));
            string c = color.substr(color.find(' ') + 1, color.length());
            printf("%d %s\n", val, c.c_str());

            if (c == "red") {
                game.max_r = std::max(game.max_r, val);
            } else if (c == "blue") {
                game.max_b = std::max(game.max_b, val);
            } else if (c == "green") {
                game.max_g = std::max(game.max_g, val);
            }

            // s.erase(0, pos + 2);
            last_semicolon = next_semicolon + 2;
        }

        // get last semicolon split
        token = s.substr(last_semicolon, next_semicolon - last_semicolon);

        int next_comma = 0;
        string color;
        int last_comma = 0;
        while ((next_comma = token.find(", ", last_comma)) != string::npos) {
            color = token.substr(last_comma, next_comma - last_comma);

            int val = std::stoi(color.substr(0, color.find(' ')));
            string c = color.substr(color.find(' ') + 1, color.length());
            printf("%d %s\n", val, c.c_str());

            if (c == "red") {
                game.max_r = std::max(game.max_r, val);
            } else if (c == "blue") {
                game.max_b = std::max(game.max_b, val);
            } else if (c == "green") {
                game.max_g = std::max(game.max_g, val);
            }

            last_comma = next_comma + 2;
        }
        color = token.substr(last_comma, next_comma - last_comma);

        int val = std::stoi(color.substr(0, color.find(' ')));
        string c = color.substr(color.find(' ') + 1, color.length());
        printf("%d %s\n", val, c.c_str());

        if (c == "red") {
            game.max_r = std::max(game.max_r, val);
        } else if (c == "blue") {
            game.max_b = std::max(game.max_b, val);
        } else if (c == "green") {
            game.max_g = std::max(game.max_g, val);
        }

        sum_powers += game.max_r * game.max_g * game.max_b;
    }
    return sum_powers;
}

int main(int argc, char *argv[]) {
    std::cout << get_valid_games(12, 13, 14, get_file_lines("input.txt"));
    return 0;
}
