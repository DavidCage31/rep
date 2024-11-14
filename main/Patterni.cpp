#include <iostream>

class Math
{
private:
    static Math* instancePtr;

    Math() {};

public:
    Math(const Math& obj) = delete;
    ~Math()
    {
        instancePtr = nullptr;
    }

    static Math* getInstance()
    {
        if (instancePtr == nullptr)
            instancePtr = new Math();
        return instancePtr;
    }

    int sum(int a, int b)
    {
        return a + b;
    }

    double sum(double a, double b)
    {
        return a + b;
    }
};

Math* Math::instancePtr = nullptr;

class Shape
{
public:
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    void draw() override
    {
        std::cout << "Circle\n";
    }
};

class Square : public Shape
{
public:
    void draw() override
    {
        std::cout << "Square\n";
    }
};

class ShapeFactory
{
public:
    virtual Shape* createShape() = 0;
};

class CircleFactory : public ShapeFactory
{
public:
    Shape* createShape() override
    {
        return new Circle();
    }
};

class SquareFactory : public ShapeFactory
{
public:
    Shape* createShape() override
    {
        return new Square();
    }
};

class Button
{
public:
    virtual void paint() = 0;
};

class WindowsButton : public Button
{
    void paint() override
    {
        std::cout << "WindowsButton\n";
    }
};

class MacButton : public Button
{
    void paint() override
    {
        std::cout << "MacButton\n";
    }
};

class CheckBox
{
public:
    virtual void paint() = 0;
};

class WindowsCheckBox : public CheckBox
{
public:
    void paint() override
    {
        std::cout << "WindowsCheckBox\n";
    }
};

class MacCheckBox : public CheckBox
{
public:
    void paint() override
    {
        std::cout << "MacCheckBox\n";
    }
};

class GUIFactory
{
public:
    virtual Button* createButton() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

class WindowsFactory : public GUIFactory
{
public:
    Button* createButton() override
    {
        return new WindowsButton();
    }

    CheckBox* createCheckBox() override
    {
        return new WindowsCheckBox();
    }
};

class MacFactory : public GUIFactory
{
public:
    Button* createButton() override
    {
        return new MacButton();
    }

    CheckBox* createCheckBox() override
    {
        return new MacCheckBox();
    }
};

class Pizza 
{
private:
    std::string dough;
    std::string sauce;
    std::string topping;

public:
    void setDough(std::string dough) 
    {
        this->dough = dough;
    }

    void setSauce(std::string sauce) 
    {
        this->sauce = sauce;
    }

    void setTopping(std::string topping) 
    {
        this->topping = topping;
    }
};

class PizzaBuilder 
{
public:
    virtual ~PizzaBuilder() = 0;
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual Pizza* getResult() = 0;
};

class HawaiianPizzaBuilder : public PizzaBuilder 
{
private:
    Pizza* pizza;

public:
    HawaiianPizzaBuilder() 
    {
        this->pizza = new Pizza();
    }
    ~HawaiianPizzaBuilder()
    {
        delete this->pizza;
    }

   
    void buildDough() override
    {
        pizza->setDough("cross");
    }

    void buildSauce() override
    {
        pizza->setSauce("mild");
    }

    void buildTopping() override
    {
        pizza->setTopping("ham+pineapple");
    }

    Pizza* getResult() override
    {
        return pizza;
    }
};

class PizzaDirector
{
private:
    PizzaBuilder* builder;

public:
    PizzaDirector(PizzaBuilder* builder)
    {
        this->builder = builder;
    }

    void constructPizza()
    {
        builder->buildDough();
        builder->buildSauce();
        builder->buildTopping();
    }
};

int main()
{
    ShapeFactory* circleFactory = new CircleFactory();
    ShapeFactory* squareFactory = new SquareFactory();

    Shape* circle = circleFactory->createShape();
    Shape* square = squareFactory->createShape();

    circle->draw();
    square->draw();

    delete circleFactory;
    delete squareFactory;
    delete circle;
    delete square;

    return 0;
}
