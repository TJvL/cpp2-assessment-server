#ifndef CPP2SERVER_APPLICATION_H
#define CPP2SERVER_APPLICATION_H

#include "Server.h"

namespace cpp2 {
    class Application {
    public:
        Application(const int serverPort);

        virtual ~Application() = default;

        int run() const;

    private:
        Server server;
    };
}

#endif //CPP2SERVER_APPLICATION_H
