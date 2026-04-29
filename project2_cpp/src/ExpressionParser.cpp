#include "ExpressionParser.h"
#include "Expression.h"
#include <sstream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <cctype>

std::vector<std::string> ExpressionParser::tokenize(const std::string& rpn) {
    std::vector<std::string> tokens;
    std::istringstream iss(rpn);
    std::string token;

    while(iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
bool ExpressionParser::isNumber(const std::string& token) {
    char* end = nullptr;
    std::strtod(token.c_str(), &end);
    return end != token.c_str() && *end == '\0';
}
// bool isNumber(const std::string& token) {
//     for (char c : token) {
//         if (!std::isdigit(c) && c != '.' && c != '-' && c != '+')
//             return false;
//     }
//     return true;
// }
bool ExpressionParser::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}
char ExpressionParser::getOperator(const std::string& token) {
    return token[0];
}
std::unique_ptr<Expression> ExpressionParser::createOperator(
    char op,
    std::unique_ptr<Expression> left,
    std::unique_ptr<Expression> right
) {
    switch (op) {
        case '+':
            return std::make_unique<Addition>(std::move(left), std::move(right));
        case '-':
            return std::make_unique<Subtraction>(std::move(left), std::move(right));
        case '*':
            return std::make_unique<Multiplication>(std::move(left), std::move(right));
        case '/':
            return std::make_unique<Division>(std::move(left), std::move(right));
        default:
            throw std::runtime_error("Unknown operator");
    }
}
std::unique_ptr<Expression> ExpressionParser::parseRPN(const std::string& rpn) {
    auto tokens = tokenize(rpn);
    std::stack<std::unique_ptr<Expression>> st;

    for(const auto& token : tokens) {

        if(isNumber(token)) {
            st.push(std::make_unique<Constant>(std::stod(token)));
            continue;
        }

        if (isOperator(token)) {
            if (st.size() < 2)
                throw std::runtime_error("Not enough operands");

            auto right = std::move(st.top()); st.pop();
            auto left  = std::move(st.top()); st.pop();

            char op = getOperator(token);
            st.push(createOperator(op, std::move(left), std::move(right)));
            continue;
        }

        // иначе — переменная
        st.push(std::make_unique<Variable>(token));
    }

    if (st.size() != 1)
        throw std::runtime_error("Invalid RPN expression");

    return std::move(st.top());
}
