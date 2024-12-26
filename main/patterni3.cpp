#include <iostream>

class DataBase {
public:
    virtual void query(std::string sql) = 0;
};

class RealDataBase : public DataBase {
public:
    void query(std::string sql) override {
        std::cout << "Executing query: " + sql + '\n';
    }
};

class DataBaseProxy : public DataBase {
private:
    RealDataBase* realDataBase;
    bool hasAccess;

public:
    DataBaseProxy(bool hasAccess) {
        this->realDataBase = new RealDataBase();
        this->hasAccess = hasAccess;
    }
    ~DataBaseProxy() {
        delete realDataBase;
    }

    void query(std::string sql) override {
        if (hasAccess)
            realDataBase->query(sql);
        else
            std::cout << "Access denied. Query cannot be executed.\n";
    }
};

class ExternalLogger {
public:
    void logMessage(std::string msg) {
        std::cout << "External log: " + msg + '\n';
    }
};

class Logger {
public:
    virtual void log(std::string msg) = 0;
};

class LoggerAdapter : public Logger {
private:
    ExternalLogger externalLogger;

public:
    LoggerAdapter(ExternalLogger externalLogger) : externalLogger(externalLogger) { }

    void log(std::string msg) override {
        externalLogger.logMessage(msg);
    }
};

class Device {
public:
    virtual void print(std::string data) = 0;
};

class Monitor : public Device {
public:
    void print(std::string data) override {
        std::cout << "Displaying on monitor: " + data + '\n';
    }
};

class Printer : public Device {
public:
    void print(std::string data) override {
        std::cout << "Printing to paper: " + data + '\n';
    }
};

class Output {
protected:
    Device* device;

public:
    Output(Device* device) : device(device) {};

    virtual void render(std::string data) = 0;
};

class TextOutput : public Output {
public:
    TextOutput(Device* device) : Output(device) {};

    void render(std::string data) override {
        device->print("Text: " + data);
    }
};

class ImageOutput : public Output {
public:
    ImageOutput(Device* device) : Output(device) {};

    void render(std::string data) override {
        device->print("Image: [Binary data: " + data + " ]");
    }
};

int main() {
    DataBase* userDb = new DataBaseProxy(false);
    DataBase* adminDb = new DataBaseProxy(true);

    userDb->query("SELECT * FROM users");
    adminDb->query("SELECT * FROM users");

    delete userDb;
    delete adminDb;

    std::cout << '\n';


    ExternalLogger* elogger = new ExternalLogger();
    Logger* logger          = new LoggerAdapter(*elogger);

    logger->log("some message");

    delete logger;
    delete elogger;

    std::cout << '\n';


    Device* monitor = new Monitor();
    Device* printer = new Printer();

    Output* textOnMonitor = new TextOutput(monitor);
    Output* textOnPrinter = new TextOutput(printer);

    textOnMonitor->render("Hello, world!");
    textOnPrinter->render("Hello, world!");

    Output* imageOnMonitor = new ImageOutput(monitor);

    imageOnMonitor->render("101010101");

    delete imageOnMonitor;
    delete textOnPrinter;
    delete textOnMonitor;
    delete printer;
    delete monitor;

    return 0;
}
