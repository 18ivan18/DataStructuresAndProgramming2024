#include <string>
#include <stack>
#include <cassert>
#include <iostream>

bool isValid(const std::string &s)
{
    std::stack<char> openingBrackets;
    for (char c : s)
    {
        switch (c)
        {
        case '{':
        case '(':
        case '[':
            openingBrackets.push(c);
            break;
        case '}':
        case ')':
        case ']':
        {
            if (openingBrackets.empty())
            {
                return false;
            }
            char openingBracket = openingBrackets.top();
            openingBrackets.pop();
            if ((c == '}' && openingBracket != '{') ||
                (c == ')' && openingBracket != '(') ||
                (c == ']' && openingBracket != '['))
            {
                return false;
            }
            break;
        }
        default:
            return false;
        }
    }
    return openingBrackets.empty();
}

int main()
{
    assert(isValid("()"));
    assert(!isValid("["));
    assert(!isValid("]"));
    assert(!isValid("()(()"));
    assert(isValid("()[]{}"));
    assert(!isValid("(]"));
    assert(!isValid("([)]"));
    assert(isValid("{[]}"));
}