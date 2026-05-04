#include <iostream>

class A {
public:
    virtual std::ostream& printOn(std::ostream& os) const {
        os << __PRETTY_FUNCTION__ << "\n";
        return os;
    }
    virtual ~A() {}
    friend std::ostream& operator<<(std::ostream& os, const A& obj) {
        return obj.printOn(os);
    }
};

class B : public A {
public:
    // TODO: nadpisz printOn dla B
    // ma wypisać __PRETTY_FUNCTION__
    virtual std::ostream& printOn(std::ostream& os) const override{
        os << __PRETTY_FUNCTION__ << "\n";
        return os;
    }
};

class C : public B {
    // TODO: NIC NIE DODAWAJ - brak nadpisania printOn
};

class D : public A {
protected:
    // TODO: nadpisz printOn dla D, ale jako protected
    virtual std::ostream& printOn(std::ostream& os) const override{
        os << __PRETTY_FUNCTION__ << "\n";
        return os;
    }
};

class E : public C, public D {
public:
    virtual std::ostream& printOn(std::ostream& os) const override {
        // 1. Najpierw wywołaj printOn z C (czyli z B)
        C::printOn(os);
        // 2. Potem wywołaj printOn z D (dostępne, bo jesteśmy w metodzie E)
        D::printOn(os);
        // 3. Na końcu wypisz swój własny
        os << __PRETTY_FUNCTION__ << "\n";
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const E& obj) {
        // Wywołujemy tylko E::printOn – to ona sama zadba o wywołanie C i D
        obj.printOn(os);
        return os;
    }
};
// TODO: zdefiniuj operator<< dla E (wykorzystując powyższą deklarację friend)

int main() {
    A a;
    B b;
    C c;
    D d;
    const E e;

    std::cout << "a: " << a;
    std::cout << "b: " << b;
    std::cout << "c: " << c;
    std::cout << "d: " << d;
    std::cout << "e: " << e;
}