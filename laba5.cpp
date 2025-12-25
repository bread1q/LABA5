#include <iostream>
#include <string>
#include <memory>

using namespace std;

// ===== Базовый класс ====== 

class Base {
public:
    Base() { cout << "Base()\n"; }
    Base(Base* obj) { cout << "Base(Base*)\n"; }
    Base(Base& obj) { cout << "Base(Base&)\n"; }

    virtual ~Base() { cout << "~Base()\n"; }

    void nonVirtualMethod() const { cout << "Base::nonVirtualMethod()\n"; }
    virtual void virtualMethod() const { cout << "Base::virtualMethod()\n"; }
    void callerMethod() const {
        cout << "Base::callerMethod() вызывает:\n";
        cout << "  1. nonVirtualMethod(): ";
        nonVirtualMethod();
        cout << "  2. virtualMethod(): ";
        virtualMethod();
    }

    virtual string className() const { return "Base"; }
    virtual bool isA(const string& type) const {
        return type == "Base";
    }
};