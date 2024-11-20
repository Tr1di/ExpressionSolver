#include <sstream>
#include <stdexcept>

#include "Expression/Expression.h"

using namespace std;


std::string Expression::BinaryOperation::toString() const
{
    ostringstream result;

    std::string leftStr = left->toString();
    std::string rightStr = right->toString();

    std::string space = getOperation() == "^" || getOperation() == "/" ? "" : " ";
    
    Operation* leftOperation = dynamic_cast<Operation*>(left);
    Operation* rightOperation = dynamic_cast<Operation*>(right);
    
    if (leftOperation
        && (leftOperation->getPriority() < getPriority()
            || (leftOperation->getPriority() == 3 && getPriority() == 3)))
    {
        result << "(" << leftStr << ")";
    }
    else
    {
        result << leftStr;
    }

    result << space << getOperation() << space;
    
    if (rightOperation && rightOperation->getPriority() < getPriority())
    {
        result << "(" << rightStr << ")";
    }
    else
    {
        result << rightStr;
    }
    
    return result.str();
}

Expression::BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}

Expression::Operation::Operation(string operation)
    : operation(std::move(operation))
{}

bool Expression::Operation::isOperation(const string& c)
{    
    return c == "+"|| c == "-" || c == "*" || c == "/"|| c == "^";
}

int Expression::Operation::priority(const string& c)
{
    if (c == "+" || c == "-") return 1;
    if (c == "*" || c == "/") return 2;
    if (c == "^") return 3;

    throw invalid_argument("Invalid operator"); 
}

Expression::BinaryOperation::BinaryOperation(const std::string& operation)
    : Operation(operation),
      left(nullptr),
      right(nullptr)
{}

float Expression::BinaryOperation::solve() const
{
    switch (getOperation().front())
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
