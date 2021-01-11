#ifndef CPP2SERVER_SERVER_H
#define CPP2SERVER_SERVER_H

#include "../commands/CommandFactory.h"
#include "../commands/CommandMapper.h"

namespace cpp2 {
    class TerminationException : public std::exception {
    public:
        TerminationException() : message("terminating server by remote command") {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    private:
        std::string message;
    };

    class Server {
    public:
        Server(const int serverPort, const std::string &syncDirectoryPath, const bool canRemoteTerminate);

        void handleClientConnection() const;

    private:
        const int serverPort;
        const FileSystemManager fileSystemManager;
        const CommandFactory commandFactory;
        const CommandMapper commandMapper;
        const bool canRemoteTerminate;
    };
}

#endif //CPP2SERVER_SERVER_H
