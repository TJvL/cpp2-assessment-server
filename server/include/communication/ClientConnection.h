#ifndef CPP2SERVER_CLIENTCONNECTION_H
#define CPP2SERVER_CLIENTCONNECTION_H

#include <asio.hpp>

namespace cpp2 {
    class ClientConnection {
    public:
        ClientConnection(int listenPort);

        std::string waitForIncomingMessage();

        void sentOutgoingMessage(const std::string &message);

        std::istream &getIncomingStream();

        void pipeStreamTillEnd(const std::istream &inputStream);

    private:
        asio::io_context ioContext;
        asio::ip::tcp::acceptor acceptor;
        asio::ip::tcp::iostream stream;
    };
}

#endif //CPP2SERVER_CLIENTCONNECTION_H
