#include <iostream>

int GameObject::id = 0;

class GameObject
{
protected:
    static int id;
    std::string name;
    int x;
    int y;

public:
    GameObject(std::string name, int x, int y)
    {
        id++;
        this->name = name;
        this->x = x;
        this->y = y;
    }

    int getId()
    {
        return id;
    }

    std::string getName()
    {
        return name;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }



};

class Unit : public GameObject
{
protected:
    double hp;
    bool isAlive;

public:
    Unit(std::string name, int x, int y, double hp = 100, bool isAlive = true) : GameObject(name, x, y)
    {
        this->hp = hp;
        this->isAlive = isAlive;
    }

    bool isAlive()
    {
        return isAlive;
    }

    int getHp()
    {
        return hp;
    }

    void receiveDamage(double damage)
    {
        hp -= damage;
    }

};

class Building : public GameObject
{
protected:
    bool isBuilt;

public:
    Building(std::string name, int x, int y, bool isBuild = true) : GameObject(name, x, y)
    {
        this->isBuilt = isBuild;
    }

    bool isBuilt()
    {
        return isBuilt;
    }

};

class Attacker
{
protected:
    double damage;

public:
    virtual void attack(Unit& unit) = 0;
};

class Moveable
{
public:
    virtual int xMove(int step) = 0;
    virtual int yMove(int step) = 0;
};

class Archer : public Unit, Attacker, Moveable
{
private:


public:
    Archer(std::string name, int x, int y, double hp = 100, bool isAlive = true, double damage) : Unit(name, x, y, hp, isAlive)
    {
        this->damage = damage;
    }

    void attack(Unit& unit) override
    {
        unit.receiveDamage(damage);
    }

    int xMove(int step) override
    {
        return x += step;
    }

    int yMove(int step) override
    {
        return y += step;
    }

};

class Fort : public Building, Attacker
{
private:

public:
    Fort(std::string name, int x, int y, bool isBuild = true, double damage) : Building(name, x, y, isBuild)
    {
        this->damage = damage;
    }

    void attack(Unit& unit) override
    {
        unit.receiveDamage(damage);
    }

};

class MobileHome : public Building, Moveable
{
private:

public:
    MobileHome(std::string name, int x, int y, bool isBuild = true) : Building(name, x, y, isBuild)
    {

    }

    int xMove(int step) override
    {
        return x += step;
    }

    int yMove(int step) override
    {
        return y += step;
    }

};

int main()
{
    
}
