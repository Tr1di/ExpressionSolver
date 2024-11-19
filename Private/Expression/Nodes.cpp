#include <sstream>
#include <stdexcept>

#include "Expression/Expression.h"

using namespace std;

Expression::Operation::Operation(char operation)
    : operation(operation),
      left(nullptr),
      right(nullptr)
{}

float Expression::Operation::solve() const
{
    switch (operation)
    {
    case '+':
        return left->solve() + right->solve();
    case '-':
        return left->solve() - right->solve();
    case '*':
        return left->solve() * right->solve();
    case '/':
        return left->solve() / right->solve();
    case '^':
        return pow(left->solve(), right->solve());
    default:
        throw invalid_argument("Wrong operator is used");
    }
}

std::string Expression::Operation::toString() const
{
    ostringstream result;

    std::string leftStr = left->toString();
    std::string rightStr = right->toString();

    std::string space = operation == '^' || operation == '/' ? "" : " ";
    
    Operation* leftOperation = dynamic_cast<Operation*>(left);
    Operation* rightOperation = dynamic_cast<Operation*>(right);
    
    if (leftOperation && priority(leftOperation->operation) < priority(operation))
    {
        result << "(" << leftStr << ")";
    }
    else
    {
        result << leftStr;
    }

    result << space << operation << space;
    
    if (rightOperation && priority(rightOperation->operation) < priority(operation))
    {
        result << "(" << rightStr << ")";
    }
    else
    {
        result << rightStr;
    }
    
    return result.str();
}

Expression::Operation::~Operation()
{
    delete left;
    delete right;
}

bool Expression::Operation::isOperation(char c)
{    
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Expression::Operation::priority(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;

    throw invalid_argument("Invalid operator"); 
}

Expression::Number::Number(float data)
    : data(data)
{}

Expression::Number::Number(std::string data)
    : Number(std::stof(data))
{}

float Expression::Number::solve() const
{    
    return data;
}

std::string Expression::Number::toString() const
{
    ostringstream result;
    result << data;
    return result.str();
}

bool Expression::Number::isNumber(char c)
{
    return isdigit(c) || c == '.';
}
