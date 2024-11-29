#include <iostream>
#include <vector>

class SortingStrategy 
{
public:
	virtual void sort(std::vector<int>& arr) = 0;
};

class BubbleSort : public SortingStrategy 
{
public:
    void sort(std::vector<int>& arr) override 
    {
        
    }
};

class QuickSort : public SortingStrategy 
{
public:
    void sort(std::vector<int>& arr) override 
    {
        
    }
};

class SortContext 
{
private:
    SortingStrategy* strategy;

public:
    void setStrategy(SortingStrategy* strategy) 
    {
        this->strategy = strategy;
    }

    void executeStrategy(std::vector<int>& arr) 
    {
        strategy->sort(arr);
    }
};

enum RequestType
{
    Type_A, Type_B
};

class Request 
{
private:
    RequestType type;

public:
    Request(RequestType type) : type(type) { }

    RequestType getType()
    {
        return type;
    }
};

class Handler 
{
public:
    virtual void setNextHandler(Handler* nextHandler) = 0;
    virtual void handleRequest(Request* request) = 0;
};

class ConcreteHandlerA : public Handler
{
private:
    Handler* nextHandler;

public:
    void setNextHandler(Handler* nextHandler) override
    {
        this->nextHandler = nextHandler;
    }

    void handleRequest(Request* request) override
    {
        if (request->getType() == Type_A)
            std::cout << "ConcreteHandlerA handled the request.\n";
        else if (nextHandler != nullptr)
            nextHandler->handleRequest(request);
    }
};

class ConcreteHandlerB : public Handler
{
private:
    Handler* nextHandler;

public:
    void setNextHandler(Handler* nextHandler) override
    {
        this->nextHandler = nextHandler;
    }

    void handleRequest(Request* request) override
    {
        if (request->getType() == Type_B)
            std::cout << "ConcreteHandlerA handled the request.\n";
        else if (nextHandler != nullptr)
            nextHandler->handleRequest(request);
    }
};

template<typename T>
class Iterator 
{
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

template<typename T>
class VectorIterator : public Iterator 
{
private:
    const std::vector<T>& collection;
    size_t position;

public:
    VectorIterator(const std::vector<T>& collection) : collection(collection), position(0) {}

    bool hasNext() override 
    {
        return position < collection.size();
    }

    int next() override 
    {
        if (hasNext()) 
            return collection[position++];
        
        throw std::out_of_range("No more elements in the collection");
    }
};

int main()
{


	return 0;
}
