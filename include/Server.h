#ifndef CPP2SERVER_SERVER_H
#define CPP2SERVER_SERVER_H

#include "commands/CommandFactory.h"
#include "commands/CommandMapper.h"

namespace cpp2 {
    class Server {
    public:
        Server(const int serverPort);

        virtual ~Server() = default;

        void handleClientConnection() const;

    private:
        const int serverPort;
        CommandFactory commandFactory;
        CommandMapper commandMapper;
    };
}

#endif //CPP2SERVER_SERVER_H
