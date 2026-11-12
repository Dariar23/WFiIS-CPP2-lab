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
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Expression> simplify() const = 0;
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
    std::string toString() const override{
        return std::to_string(value);
    }
    std::unique_ptr<Expression> simplify() const override {
    return std::make_unique<Constant>(value);
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

    std::string toString() const override{
        return name;
    }
    std::unique_ptr<Expression> simplify() const override {
    return std::make_unique<Variable>(name);
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
    std::string toString() const override {
            return "(" + left->toString() + " " + getSymbol() + " " + right->toString() + ")";
        }
        
        virtual char getSymbol() const = 0; 
};
class Negation : public Expression {
private:
    std::unique_ptr<Expression> child;

public:
    explicit Negation(std::unique_ptr<Expression> c)
        : child(std::move(c)) {}

    double eval(const Context& ctx) const override {
        return -child->eval(ctx);
    }

    const Expression& operator[](size_t idx) const override {
        if (idx != 0)
            throw std::runtime_error("Negation has only 1 child");
        return *child;
    }

    std::string toString() const override {
        return "(-" + child->toString() + ")";
    }

    std::unique_ptr<Expression> simplify() const override {
        auto s = child->simplify();

        
        if(auto c = dynamic_cast<Constant*>(s.get())) {
            return std::make_unique<Constant>(-c->eval({}));
        }

        return std::make_unique<Negation>(std::move(s));
    }
};


class Addition : public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return right->eval(ctx)+left->eval(ctx);
    }

    char getSymbol() const override {
        return '+';
    }
    std::unique_ptr<Expression> simplify() const override {
    auto l = left->simplify();
    auto r = right->simplify();

    auto lc = dynamic_cast<Constant*>(l.get());
    auto rc = dynamic_cast<Constant*>(r.get());

    if (lc && rc)
        return std::make_unique<Constant>(lc->eval({}) + rc->eval({}));

    if (rc && rc->eval({}) == 0.0) return std::move(l);
    if (lc && lc->eval({}) == 0.0) return std::move(r);

    return std::make_unique<Addition>(std::move(l), std::move(r));
}

};
class Subtraction:  public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return left->eval(ctx)-right->eval(ctx);
    }
    char getSymbol() const override {
        return '-';
    }
    std::unique_ptr<Expression> simplify() const override {
    auto l = left->simplify();
    auto r = right->simplify();

    auto lc = dynamic_cast<Constant*>(l.get());
    auto rc = dynamic_cast<Constant*>(r.get());

    if (lc && rc)
        return std::make_unique<Constant>(lc->eval({}) - rc->eval({}));

    if (rc && rc->eval({}) == 0.0) return std::move(l);

    if (lc && lc->eval({}) == 0.0)
        return std::make_unique<Negation>(std::move(r));

    return std::make_unique<Subtraction>(std::move(l), std::move(r));
}

    
};
class Multiplication:  public BinaryOperator{
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override{
        return left->eval(ctx)*right->eval(ctx);
    }
    char getSymbol() const override {
        return '*';
    }
    std::unique_ptr<Expression> simplify() const override {
    auto l = left->simplify();
    auto r = right->simplify();

    auto lc = dynamic_cast<Constant*>(l.get());
    auto rc = dynamic_cast<Constant*>(r.get());

    if(lc && rc)
        return std::make_unique<Constant>(lc->eval({}) * rc->eval({}));

    if((lc && lc->eval({}) == 0.0) || (rc && rc->eval({}) == 0.0))
        return std::make_unique<Constant>(0.0);

    if (rc && rc->eval({}) == 1.0) return std::move(l);
    if (lc && lc->eval({}) == 1.0) return std::move(r);

    return std::make_unique<Multiplication>(std::move(l), std::move(r));
}

};
class Division : public BinaryOperator {
public:
    using BinaryOperator::BinaryOperator;

    double eval(const Context& ctx) const override {
        return left->eval(ctx)/right->eval(ctx);
    }
    char getSymbol() const override {
        return '/';
    }
    std::unique_ptr<Expression> simplify() const override {
    auto l = left->simplify();
    auto r = right->simplify();

    auto lc = dynamic_cast<Constant*>(l.get());
    auto rc = dynamic_cast<Constant*>(r.get());

    if (lc && rc)
        return std::make_unique<Constant>(lc->eval({}) / rc->eval({}));

    if (rc && rc->eval({}) == 1.0)
        return std::move(l);

    return std::make_unique<Division>(std::move(l), std::move(r));
}

};
