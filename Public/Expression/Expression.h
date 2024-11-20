#pragma once

#include <queue>
#include <string> 

class Expression
{
    struct Node;
    struct Number;
    struct Operation;
    struct UnaryOperation;
    struct BinaryOperation;
    
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

struct Expression::Operation : Node
{
private:
    std::string operation;

public:
    explicit Operation(std::string operation);

    std::string getOperation() const { return operation; }
    int getPriority() const { return priority(operation); }
    
    static bool isOperation(const std::string& c);
    static int priority(const std::string& c);
};

struct Expression::UnaryOperation final : Operation
{
    Node* expression;
};

struct Expression::BinaryOperation final : Operation
{
    Node* left;
    Node* right;

    explicit BinaryOperation(const std::string& operation);
    
    float solve() const override;
    std::string toString() const override;
    ~BinaryOperation() override;
};