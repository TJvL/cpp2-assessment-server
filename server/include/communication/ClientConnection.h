#ifndef CPP2SERVER_CLIENTCONNECTION_H
#define CPP2SERVER_CLIENTCONNECTION_H

#include <asio.hpp>

namespace cpp2 {
    class ClientConnection {
    public:
        ClientConnection(int listenPort);

        ~ClientConnection();

        ClientConnection(const ClientConnection &other) = delete;

        ClientConnection(ClientConnection &&other) = delete;

        ClientConnection &operator=(const ClientConnection &other) = delete;

        ClientConnection &operator=(ClientConnection &&other) = delete;

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