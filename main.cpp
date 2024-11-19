#include <iostream>

#include "Expression.h"

int main(int argc, char* argv[])
{
    std::string input;
    std::getline(std::cin, input);

    const Expression expression(input);
    std::cout << expression.solve();
    
    return 0;
}
