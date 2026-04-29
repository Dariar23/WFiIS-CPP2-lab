#pragma once
#include <map>
#include <string>
#include <vector>
#include "Expression.h"


class ExpressionParser {

    public:
    static std::unique_ptr<Expression> parseRPN(const std::string& rpn);
    
    private:
    static bool isNumber(const std::string& token);
    static bool isOperator(const std::string& token);
    static char getOperator(const std::string& token);
    static std::unique_ptr<Expression> createOperator(
        char op, 
        std::unique_ptr<Expression> left, 
        std::unique_ptr<Expression> right
    );
    static std::vector<std::string> tokenize(const std::string& rpn);
};
