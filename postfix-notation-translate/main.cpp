#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global first array
const vector<string> FIRST_TERM = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
const vector<string> FIRST_EXPR = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

// Global variable
vector<string> input = {"9", "+", "5", "5", "-", "3"}; // Input string of oringin code
size_t lookahead = 0; // A pointer to input string
size_t last_symbol = -1;

void term();

void expr();

void match(const string &t);

void output_error();

int main() {
    cout << "Let's start compile some code!" << endl;
    cout << "Code: ";
    for (const auto &item: input) cout << item << ' ';
    cout << endl;
    expr();
    cout << endl << "End of compile" << endl;
    return 0;
}

// term -> 1 ~ 9
void term() {
    for (const auto &item: FIRST_TERM) {
        if (item == input.at(lookahead)) {
            // If we found first symbol in FIRST_TERM
            lookahead++;
            cout << item << ' '; // An action to print some code
            return;
        }
    }
    output_error();
}

// expr -> expr + term | expr - term | term
void expr() {
    // Find matched first string in FIRST(expr)
    bool is_find = false;
    for (const auto &item: FIRST_EXPR) {
        if (item == input.at(lookahead)) {
            // If we found first symbol in FIRST_TERM
            is_find = true;
        }
    }

    if (!is_find) {
        output_error();
    }

    // Calculate last '+' or '-' to ensure which formula to take
    int condition = 0;
    if (last_symbol == -1) {
        last_symbol = input.size();
    }
    while (--last_symbol && last_symbol > lookahead) {
        if (input.at(last_symbol) == "+") condition = 1;
        else if (input.at(last_symbol) == "-") condition = 2;
        if (condition != 0) break;
    }
    if (lookahead == last_symbol) condition = 3;

    switch (condition) {
        case 1: // expr + term
            expr();
            match("+");
            term();
            cout << "+ ";
            break;
        case 2: // expr - term
            expr();
            match("-");
            term();
            cout << "- ";
            break;
        case 3: // term
            term();
            break;
        default:
            output_error();
    }
}

void match(const string &t) {
    lookahead++;
}

void output_error() {
    cout << endl << "syntax error at " << "\"" << input.at(lookahead) << "\""
         << " (location = " << lookahead << ')' << endl
         << endl << "End of compile" << endl;
    exit(1);
}
