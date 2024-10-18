#include <iostream>

class Math
{
private:
    static Math* instancePtr;

    Math() {};

public:
    Math(const Math& obl) = delete;
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
        return new Circle;
    }
};

class SquareFactory : public ShapeFactory
{
public:
    Shape* createShape() override
    {
        return new Square;
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
        return new WindowsButton;
    }

    CheckBox* createCheckBox() override
    {
        return new WindowsCheckBox;
    }
};

class MacFactory : public GUIFactory
{
public:
    Button* createButton() override
    {
        return new MacButton;
    }

    CheckBox* createCheckBox() override
    {
        return new MacCheckBox;
    }
};

class Pizza {
private:
    std::string dough;
    std::string sauce;
    std::string topping;

public:
    void setDough(std::string dough) {
        this->dough = dough;
    }

    void setSauce(std::string sauce) {
        this->sauce = sauce;
    }

    void setTopping(std::string topping) {
        this->topping = topping;
    }
};

class PizzaBuilder 
{
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

class Meal {
private:
    std::string appetizer;
    std::string mainCourse;
    std::string dessert;

public:
    void setAppetizer(const std::string& app) { appetizer = app; }
    void setMainCourse(const std::string& main) { mainCourse = main; }
    void setDessert(const std::string& des) { dessert = des; }
    void showMeal() 
    {
        std::cout << "Meal consists of: " << appetizer << ", " << mainCourse << ", and " << dessert << "." << std::endl;
    }
};

class MealBuilder 
{
public:
    virtual void buildAppetizer() = 0;
    virtual void buildMainCourse() = 0;
    virtual void buildDessert() = 0;
    virtual Meal* getMeal() = 0;
};

class ItalianMealBuilder : public MealBuilder 
{
    Meal* meal;
public:
    ItalianMealBuilder() 
    { 
        meal = new Meal(); 
    }
    void buildAppetizer() 
    {
        meal->setAppetizer("Bruschetta"); 
    }
    void buildMainCourse() 
    {
        meal->setMainCourse("Pizza");
    }
    void buildDessert()
    {
        meal->setDessert("Gelato");
    }
    Meal* getMeal() 
    {
        return meal;
    }
};

class Cook 
{
private:
    MealBuilder* builder;

public:
    Cook(MealBuilder* builder)
    {
        this->builder = builder;
    }

    void constructMeal() 
    {
        builder->buildAppetizer();
        builder->buildMainCourse();
        builder->buildDessert();
    }

    Meal* getMeal() 
    {
        return builder->getMeal();
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