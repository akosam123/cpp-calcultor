/******************************************************************************
Self-Made Calculator
Akosa Morah

Console calculator with PEMDAS, factorials, history, and a saved answer.
*******************************************************************************/

#include <cmath>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct HistoryEntry {
    string expression;
    double result;
};

// Recursive factorial: n! = n * (n - 1)!, with 0! and 1! both equal to 1.
unsigned long long factorial(unsigned int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

class ExpressionParser {
public:
    ExpressionParser(const string& input, double savedAnswer)
        : text(input), position(0), ans(savedAnswer) {}

    double parse() {
        double value = parseExpression();
        skipSpaces();
        if (position != text.size()) {
            throw runtime_error("Unexpected character '" +
                                string(1, text[position]) + "'.");
        }
        return value;
    }

private:
    const string& text;
    size_t position;
    double ans;

    void skipSpaces() {
        while (position < text.size() &&
               isspace(static_cast<unsigned char>(text[position]))) {
            ++position;
        }
    }

    bool match(char expected) {
        skipSpaces();
        if (position < text.size() && text[position] == expected) {
            ++position;
            return true;
        }
        return false;
    }

    bool matchWord(const string& expected) {
        skipSpaces();
        size_t start = position;
        for (char expectedCharacter : expected) {
            if (position >= text.size() ||
                tolower(static_cast<unsigned char>(text[position])) !=
                    tolower(static_cast<unsigned char>(expectedCharacter))) {
                position = start;
                return false;
            }
            ++position;
        }

        // Do not accept "ans" as the beginning of a longer word.
        if (position < text.size() &&
            isalpha(static_cast<unsigned char>(text[position]))) {
            position = start;
            return false;
        }
        return true;
    }

    // expression = term (("+" | "-") term)*
    double parseExpression() {
        double value = parseTerm();
        while (true) {
            if (match('+')) {
                value += parseTerm();
            } else if (match('-')) {
                value -= parseTerm();
            } else {
                return value;
            }
        }
    }

    // term = unary (("*" | "/") unary)*
    double parseTerm() {
        double value = parseUnary();
        while (true) {
            if (match('*')) {
                value *= parseUnary();
            } else if (match('/')) {
                double divisor = parseUnary();
                if (divisor == 0.0) {
                    throw runtime_error("Division by zero is not allowed.");
                }
                value /= divisor;
            } else {
                return value;
            }
        }
    }

    // Unary signs have lower precedence than powers, so -2^2 means -(2^2).
    double parseUnary() {
        if (match('+')) {
            return parseUnary();
        }
        if (match('-')) {
            return -parseUnary();
        }
        return parsePower();
    }

    // Calling parseUnary on the right makes exponentiation right-associative:
    // 2^3^2 is interpreted as 2^(3^2).
    double parsePower() {
        double base = parsePostfix();
        if (match('^')) {
            double exponent = parseUnary();
            double result = pow(base, exponent);
            if (!isfinite(result)) {
                throw runtime_error("That power does not produce a real, finite number.");
            }
            return result;
        }
        return base;
    }

    // postfix = primary ("!")*
    double parsePostfix() {
        double value = parsePrimary();
        while (match('!')) {
            if (value < 0 || floor(value) != value) {
                throw runtime_error(
                    "Factorial requires a non-negative whole number.");
            }
            if (value > 20) {
                throw runtime_error(
                    "Factorial is limited to 20! to prevent integer overflow.");
            }
            value = static_cast<double>(
                factorial(static_cast<unsigned int>(value)));
        }
        return value;
    }

    // primary = number | Ans | sqrt("(" expression ")") | "(" expression ")"
    double parsePrimary() {
        skipSpaces();

        if (matchWord("ans")) {
            return ans;
        }

        if (matchWord("sqrt")) {
            if (!match('(')) {
                throw runtime_error("Use sqrt(expression), including parentheses.");
            }
            double value = parseExpression();
            if (!match(')')) {
                throw runtime_error("Missing ')' after square root.");
            }
            if (value < 0) {
                throw runtime_error(
                    "A negative number has no real square root.");
            }
            return sqrt(value);
        }

        if (match('(')) {
            double value = parseExpression();
            if (!match(')')) {
                throw runtime_error("Missing closing parenthesis.");
            }
            return value;
        }

        return parseNumber();
    }

    double parseNumber() {
        skipSpaces();
        size_t charactersRead = 0;

        try {
            double value = stod(text.substr(position), &charactersRead);
            position += charactersRead;
            return value;
        } catch (const exception&) {
            throw runtime_error("Expected a number, Ans, sqrt(...), or (...).");
        }
    }
};

void displayHelp() {
    cout << "\nEnter a complete expression and press Enter.\n"
         << "Operators: +  -  *  /  ^  !\n"
         << "Other:     sqrt(expression), parentheses, and Ans\n"
         << "\nExamples:\n"
         << "  2 + 3 * 4          = 14\n"
         << "  (2 + 3) * 4        = 20\n"
         << "  5!                  = 120\n"
         << "  sqrt(81) + 2^3      = 17\n"
         << "  Ans * 2             uses the latest saved result\n"
         << "\nCommands:\n"
         << "  history   show previous calculations\n"
         << "  prev      recall the previous result into Ans\n"
         << "  next      move forward through recalled results\n"
         << "  clear     reset Ans to zero\n"
         << "  clear history   erase calculation history\n"
         << "  help      show these instructions\n"
         << "  quit      exit the calculator\n\n";
}

void displayHistory(const vector<HistoryEntry>& history) {
    if (history.empty()) {
        cout << "History is empty.\n";
        return;
    }

    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << ". " << history[i].expression << " = "
             << setprecision(15) << history[i].result << '\n';
    }
}

int main() {
    vector<HistoryEntry> history;
    size_t historyPosition = 0;
    double ans = 0.0;
    string input;

    cout << "Self-Made Calculator\n"
         << "Type help for instructions or quit to exit.\n";

    while (true) {
        cout << "\nAns = " << setprecision(15) << ans << "\n> ";

        if (!getline(cin, input)) {
            cout << "\nSee you soon!\n";
            break;
        }

        if (input.empty()) {
            continue;
        }

        if (input == "quit" || input == "exit" || input == "n" ||
            input == "N") {
            cout << "See you soon!\n";
            break;
        }
        if (input == "help") {
            displayHelp();
            continue;
        }
        if (input == "history") {
            displayHistory(history);
            continue;
        }
        if (input == "clear") {
            ans = 0.0;
            historyPosition = history.size();
            cout << "Ans was reset to 0.\n";
            continue;
        }
        if (input == "clear history") {
            history.clear();
            historyPosition = 0;
            cout << "History was erased.\n";
            continue;
        }
        if (input == "prev") {
            if (history.empty() || historyPosition == 0) {
                cout << "There is no previous calculation.\n";
            } else {
                --historyPosition;
                ans = history[historyPosition].result;
                cout << history[historyPosition].expression << " = "
                     << setprecision(15) << ans << '\n';
            }
            continue;
        }
        if (input == "next") {
            if (history.empty() || historyPosition + 1 >= history.size()) {
                cout << "There is no newer calculation.\n";
            } else {
                ++historyPosition;
                ans = history[historyPosition].result;
                cout << history[historyPosition].expression << " = "
                     << setprecision(15) << ans << '\n';
            }
            continue;
        }

        try {
            ExpressionParser parser(input, ans);
            double result = parser.parse();
            if (!isfinite(result)) {
                throw runtime_error("The result is too large or is not a number.");
            }

            ans = result;
            history.push_back({input, result});
            historyPosition = history.size();
            cout << "= " << setprecision(15) << result << '\n';
        } catch (const exception& error) {
            cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
