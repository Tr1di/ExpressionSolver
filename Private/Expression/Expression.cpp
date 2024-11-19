#include "Expression/Expression.h"

#include <complex>
#include <stack>

using namespace std;

Expression::Expression(const string& expression)
{
    if (!isExpressionCorrect(expression))
    {
        throw std::invalid_argument("Braces placed incorrectly");
    }
    
    root = parse(expression);
}

bool Expression::isExpressionCorrect(const std::string& expression)
{
    stack<char> braces;

    for (const auto it : expression)
    {
        if (it == '(')
        {
            braces.push(it);
        }

        if (it == ')')
        {
            if (braces.empty() || braces.top() != '(')
            {
                return false;
            }

            braces.pop();
        }
    }
    
    return braces.empty();
}

Expression::Node* Expression::parse(const string& expression)
{
    queue<Node*> nodes;
    deque<char> operands;

    stack<char> chars;
    
    for(auto it = expression.begin(); it < expression.end(); ++it)
    {
        if (*it == ' ')
        {
            continue;
        }
        
        if (!operands.empty() && operands.back() == '(' && *it != '(' && *it != ')')
        {
            chars.push(*it);
            continue;
        }

        if (*it == ')')
        {            
            chars.push(*it);
            if (!operands.empty() && operands.back() == '(')
            {
                operands.pop_back();
                continue;
            }
            
            break;
        }
        
        if (*it == '(')
        {
            chars.push(*it);
            
            if (operands.empty() || operands.back() != '(')
            {
                Node* subExpression = parse(expression.substr(distance(expression.begin(), it) + 1));
                nodes.push(subExpression);
            }

            operands.push_back(*it);            
            continue;
        }
        
        if (Number::isNumber(*it) || ((*it == '-' || *it == '+') && (chars.empty() || Operation::isOperation(chars.top()))))
        {
            stringstream number;

            do
            {
                number << *it;
                ++it;
            }
            while(it < expression.end() && Number::isNumber(*it));
            
            --it;

            nodes.push(new Number(number.str()));
        }
        else if (Operation::isOperation(*it))
        {
            operands.push_back(*it);
        }
        else
        {
            throw std::exception("Expression is invalid");
        }

        chars.push(*it);
    }

    return parseQueues(nodes, operands);
}

Expression::Node* Expression::parseQueues(std::queue<Node*>& nodes, std::deque<char>& operands, int lastPriority)
{    
    if (operands.empty() && !nodes.empty())
    {
        return nodes.front();
    }
    
    Node* lastExpression = nullptr;

    while (!operands.empty())
    {
        char op = operands.front();
        operands.pop_front();

        Operation* newOp = new Operation(op);

        if (lastExpression)
        {
            newOp->left = lastExpression;
        }
        else
        {
            newOp->left = nodes.front();
            nodes.pop();
        }

        if (!operands.empty())
        {
            const int current = Operation::priority(op);
            const int next = Operation::priority(operands.front());
            
            if (next > current || next == 3)
            {
                newOp->right = parseQueues(nodes, operands, current);
                lastExpression = newOp;
                continue;
            }

            if (next < current && next <= lastPriority)
            {
                newOp->right = nodes.front();
                nodes.pop();
                
                return newOp;
            }
        }
        
        newOp->right = nodes.front();
        nodes.pop();

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

std::string Expression::toString() const
{
    if (!root)
    {
        throw exception("Expression is invalid");
    }
    
    return root->toString();
}

std::ostream& operator<<(std::ostream& out, const Expression& expression)
{
    return out << expression.toString();
}
