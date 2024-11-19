#include <iostream>

#include "Expression/Expression.h"

template <class T>
void getValue(const std::string& prompt, T& value)
{
    std::cout << prompt;
    std::cin >> value;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << prompt;
        std::cin >> value;
    }
    
    std::string endLine;
    std::getline(std::cin, endLine);
}

template <>
inline void getValue<std::string>(const std::string& prompt, std::string& value)
{
    std::cout << prompt;
    getline(std::cin, value);
}

void startSolving()
{
    std::string input;
    getValue("| Enter expression: ", input);

    try
    {
        const Expression expression(input);
        std::cout << "---------------------------------------\n"
                  << "| " << expression << " = " << expression.solve() << "\n";
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
                      << "| 1 - Enter Expression\n"
                      << "| 2 - Exit\n"
                      << "--------------------\n";
            getValue("| Select action: ", chose);

            std::cout << "--------------------\n";
            
            switch (chose)
            {
            case 1:
                startSolving();
                break;
            case 2:
                std::cout << "| Goodbye!\n"
                          << "--------------------";
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
}
