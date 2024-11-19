#include "Expression.h"

#include <complex>
#include <stack>
#include <vector>

using namespace std;

Expression::Expression(const string& expression)
{
    if(!isExpressionCorrect())
    {
        throw exception("Expression is invalid");
    }
    
    root = parse(expression);
}

bool Expression::isExpressionCorrect()
{
    return true;
}

Expression::Node* Expression::parse(const string& expression)
{    
    vector<Node*> nodes;
    deque<char> operands;
    
    for(auto it = expression.begin(); it < expression.end(); ++it)
    {
        if (*it == ' ')
        {
            continue;
        }
        
        if (!operands.empty() && operands.back() == '(' && *it != '(' && *it != ')')
        {
            continue;
        }

        if (*it == ')')
        {
            if (!operands.empty() && operands.back() == '(')
            {
                operands.pop_back();
                continue;
            }

            break;
        }
        
        if (*it == '(')
        {
            if (operands.empty() || operands.back() != '(')
            {
                Node* subExpression = parse(expression.substr(distance(expression.begin(), it) + 1));
                nodes.push_back(subExpression);
            }

            operands.push_back(*it);
            continue;
        }
        
        if (Number::isNumber(*it))
        {
            stringstream number;

            while(it < expression.end() && Number::isNumber(*it))
            {
                number << *it;
                ++it;
            }
            --it;

            nodes.push_back(new Number(number.str()));
        }
        else if (Operation::isOperation(*it))
        {
            operands.push_back(*it);
        }
        else
        {
            throw std::exception("Something wrong");
        }
    }

    if (operands.empty() && !nodes.empty())
    {
        return nodes.back();
    }
    
    Node* lastExpression = nullptr;
    
    for (auto op = operands.rbegin(); op < operands.rend(); ++op)
    {
        Operation* newOp = new Operation(*op);

        if (lastExpression)
        {
            newOp->right = lastExpression;
        }
        else
        {
            newOp->right = nodes.back();
            nodes.pop_back();
        }
        
        newOp->left = nodes.back();
        nodes.pop_back();       

        lastExpression = newOp;
    }
    
    return lastExpression;
}

float Expression::solve() const
{
    if (!root)
    {
        throw exception("Expression is invalid");
    }

    return root->solve();
}

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

Expression::Operation::~Operation()
{
    delete left;
    delete right;
}

bool Expression::Operation::isOperation(char c)
{    
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Expression::Operation::operationPriority(char c)
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

bool Expression::Number::isNumber(char c)
{
    return isdigit(c) || c == '.';
}
