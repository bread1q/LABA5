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

    void nonVirtualMethod() { cout << "Base::nonVirtualMethod()\n"; }
    virtual void virtualMethod() { cout << "Base::virtualMethod()\n"; }
    void callerMethod() {
        cout << "Base::callerMethod() вызывает:\n";
        cout << "  1. nonVirtualMethod(): ";
        nonVirtualMethod();
        cout << "  2. virtualMethod(): ";
        virtualMethod();
    }

    virtual string className() { return "Base"; }
    virtual bool isA(string& name) {
        return name == "Base";
    }
};

class Desc : public Base {
public:
    Desc() { cout << "Desc()\n"; }
    Desc(Desc* obj) : Base(obj) { cout << "Desc(Desc*)\n"; }
    Desc(Desc& obj) : Base(obj) { cout << "Desc(Desc&)\n"; }

    ~Desc() override { cout << "~Desc()\n"; }

    // перекрываемый метод
    void nonVirtualMethod() { cout << "Desc::nonVirtualMethod()\n"; }

    // переопределенный метод
    void virtualMethod() override { cout << "Desc::virtualMethod()\n"; }

    string className() override { return "Desc"; }
    bool isA(string& name) override { return (name == "Desc") || Base::isA(name); }

    void descSpecificMethod() { cout << "Desc::descSpecificMethod()\n"; }
};

void demo_virtual_and_nonvirtual() {
    cout << "\n=== 1. ВИРТУАЛЬНЫЕ И НЕВИРТУАЛЬНЫЕ МЕТОДЫ ===\n";

    Desc desc;
    Base* basePtr = &desc;

    cout << "\n1. Прямой вызов методов у объекта Desc:\n";
    cout << "desc.nonVirtualMethod(): ";
    desc.nonVirtualMethod(); // Desc::nonVirtualMethod()
    cout << "desc.virtualMethod(): ";
    desc.virtualMethod(); // Desc::virtualMethod()

    cout << "\n2. Вызов через указатель Base*:\n";
    cout << "basePtr->nonVirtualMethod(): ";
    basePtr->nonVirtualMethod(); // Base::nonVirtualMethod()
    cout << "basePtr->virtualMethod(): ";
    basePtr->virtualMethod(); // Desc::virtualMethod()

    cout << "\n3. Вызов callerMethod():\n";
    cout << "desc.callerMethod():\n";
    desc.callerMethod();  // Base::nonVirtualMethod(), Desc::virtualMethod()
}

void demo_constructors_and_destructors() {
    cout << "\n=== 2. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР ===" << endl;
    
    cout << "\n2. Виртуальный деструктор:" << endl;
    Base* polyPtr = new Desc();
    cout << "Удаление через Base* указатель:" << endl;
    delete polyPtr;  // Вызываются оба деструктора (~Desc() и ~Base())
    
    cout << "\n3. Без виртуального деструктора:" << endl;
    cout << "Если бы деструктор Base не был виртуальным," << endl;
    cout << "то при delete polyPtr вызвался бы только ~Base()" << endl;
}

int main() {
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 5 ===" << endl;

    demo_virtual_and_nonvirtual();
    demo_constructors_and_destructors();
}