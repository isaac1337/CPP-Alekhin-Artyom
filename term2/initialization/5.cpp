#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
using namespace std;

int sumFromString(const string& input) {
    if (input.empty() || input.front() != '[' || input.back() != ']') {
        throw invalid_argument("Некорректный формат строки");
    }

    string numbers = input.substr(1, input.size() - 2);

    stringstream ss(numbers);
    string token;
    int sum = 0;

    while (getline(ss, token, ',')) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());

        for (char c : token) {
            if (!isdigit(c) && c != '-') {
                throw invalid_argument("Некорректный формат строки");
            }
        }

        if (!token.empty()) {
            sum += stoi(token);
        }
    }

    return sum;
}

int main() {
    // Тестовые примеры
    string testCases[] = {
        "[10, 20, 30, 40, 50]",
        "[4, 8, 15, 16, 23, 42]",
        "[20]",
        "[]",
        "[invalid, text]"
    };

    for (const string& testCase : testCases) {
        try {
            int result = sumFromString(testCase); 
            cout << "Сумма чисел из строки " << testCase << " = " << result << endl;
        } catch (const invalid_argument& e) {
            cout << "Ошибка: " << e.what() << " в строке " << testCase << endl;
        }
    }

    return 0;
}
