#pragma once

#include <queue>
#include <string> 

class Expression
{
    struct Node;
    struct Operation;
    struct Number;

    Node* root;
    
public:
    Expression(const std::string& expression);

private:
    static bool isExpressionCorrect(const std::string& expression);
    static Node* parse(const std::string& expression);
    static Node* parseQueues(std::queue<Node*>& nodes, std::deque<char>& operands, int lastPriority = 0);
    
public:
    float solve() const;
    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Expression& expression);
    
};

///////////////////////////////////////
/// Nodes

struct Expression::Node
{
    virtual float solve() const = 0;
    virtual std::string toString() const = 0;
    virtual ~Node() = default;
};

struct Expression::Operation final : Node
{
private:
    char operation;
    
public:
    Node* left;
    Node* right;
    
    explicit Operation(char operation);

    float solve() const override;
    std::string toString() const override;
    ~Operation() override;

    static bool isOperation(char c);
    static int priority(char c);
};

struct Expression::Number final : Node
{
private:
    float data;
    
public:
    explicit Number(float data);
    explicit Number(std::string data);

    float solve() const override;
    std::string toString() const override;

    static bool isNumber(char c);
};