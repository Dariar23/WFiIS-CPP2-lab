#pragma once
#include <map>
#include <string>

class Expression {
public:
    using Context = std::map<std::string, double>;

    virtual ~Expression() = default;

    virtual double eval(const Context& ctx) const = 0;
//Constant i Variable nie mają dzieci → operator[] musi rzucać wyjątek
//BinaryOperator ma 2 dzieci → operator[] musi zwracać referencję
    virtual const Expression& operator[](size_t idx) const = 0;
    double eval() const {
        return eval(Context{});
    }
};
class Constant: public Expression{
    private:
    double value;

    public:
    Constant(double val): value(val) {}
    double eval(const Context& ctx) const override{
        return value;
    }
    const Expression& operator[](size_t idx) const override{
        throw std::runtime_error("Constant has no children");
    }
    
    
};
class Variable : public Expression{
    private:
    std::string name;

    public:
    Variable(const std::string& name) : name(name){}
    double eval(const Context& ctx) const override{
        return ctx.at(name);
    }
    const Expression& operator[](size_t idx) const override{
        throw std::runtime_error("Variable has no children");
    }


};
class BinaryOperator: public Expression{
    protected:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    public:
    BinaryOperator(std::unique_ptr<Expression> l,std::unique_ptr<Expression> r): left(std::move(l)), right(std::move(r)){}
    const Expression& operator[](size_t ind) const override{
        if(ind==0){
            return *left;
        }
        if(ind==1){
            return *right;
        }
        throw std::runtime_error("BinaryOperator has only 2 children");
    }
    virtual double eval(const Context& ctx) const = 0;

};

class Addition : public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return right->eval(ctx)+left->eval(ctx);
    }
};
class Subtraction:  public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return left->eval(ctx)-right->eval(ctx);
    }
};
class Multiplication:  public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return left->eval(ctx)*right->eval(ctx);
    }
};
class Division : public BinaryOperator {
public:
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override {
        return left->eval(ctx)/right->eval(ctx);
    }
};