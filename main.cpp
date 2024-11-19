#include <iostream>

#include "Expression/Expression.h"

void startSolving()
{
    std::string input;
    std::cout << "Enter expression: ";
    std::cin.ignore();
    std::getline(std::cin, input);

    try
    {
        const Expression expression(input);
        std::cout << expression << " = " << expression.solve() << "\n";
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

int main(int argc, char* argv[])
{
    int chose;
    
    while(true)
    {
        try
        {
            std::cout << "---------Expression Calculator---------\n"
                      << "1 - Enter Expression\n"
                      << "2 - Exit\n"
                      << "\nSelect action: ";
            std::cin >> chose;

            switch (chose)
            {
            case 1:
                startSolving();
                break;
            case 2:
                return 0;
            default:
                throw std::exception("Invalid action");
            }
        }
        catch (const std::exception& exception)
        {
            std::cout << exception.what() << "\n";
        }
    }
    
    return 0;
}
