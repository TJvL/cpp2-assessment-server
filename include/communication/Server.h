#ifndef CPP2SERVER_SERVER_H
#define CPP2SERVER_SERVER_H

#include "../commands/CommandFactory.h"
#include "../commands/CommandMapper.h"

namespace cpp2 {
    class Server {
    public:
        Server(const int serverPort, const std::string &syncDirectoryPath);

        void handleClientConnection() const;

    private:
        const int serverPort;
        const FileSystemManager fileSystemManager;
        const CommandFactory commandFactory;
        const CommandMapper commandMapper;
    };
}

#endif //CPP2SERVER_SERVER_H
