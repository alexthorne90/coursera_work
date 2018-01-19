#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    bool result = true;
    long error_index = 0;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket
            Bracket o_bracket(next, position);
            opening_brackets_stack.push(o_bracket);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket
            if (opening_brackets_stack.empty())
            {
                result = false;
                error_index = position;
                break;
            }
            Bracket test_bracket = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!test_bracket.Matchc(next))
            {
                result = false;
                error_index = position;
                break;
            }
        }
    }

    if (!opening_brackets_stack.empty() && result)
    {
        result = false;
        error_index = opening_brackets_stack.top().position;
    }

    // Printing answer
    if (result)
        std::cout << "Success";
    else
        std::cout << error_index + 1;

    return 0;
}
