#pragma once

#include <string> 

class Expression
{
    struct Node
    {
        virtual float solve() const = 0;
        virtual ~Node() = default;
    };

    struct Operation;
    struct Number;

    Node* root;
    
public:
    Expression(const std::string& expression);

private:
    bool isExpressionCorrect();
    Node* parse(const std::string& expression);

public:
    float solve() const;
    
};

///////////////////////////////////////
/// Nodes

struct Expression::Operation final : Node
{
private:
    char operation;
    
public:
    Node* left;
    Node* right;
    
    explicit Operation(char operation);

    float solve() const override;
    ~Operation() override;

    static bool isOperation(char c);
    static int operationPriority(char c);
};

struct Expression::Number final : Node
{
private:
    float data;
    
public:
    explicit Number(float data);
    explicit Number(std::string data);

    float solve() const override;

    static bool isNumber(char c);
};
