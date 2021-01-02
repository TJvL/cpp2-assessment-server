#ifndef CPP2SERVER_APPLICATION_H
#define CPP2SERVER_APPLICATION_H

#include "communication/Server.h"

namespace cpp2 {
    class Application {
    public:
        Application(const int port, const std::string &syncDirectoryName);

        virtual ~Application() = default;

        int run() const;

    private:
        Server server;
    };
}

#endif //CPP2SERVER_APPLICATION_H
