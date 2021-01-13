#ifndef CPP2SERVER_TESTSERVERCONNECTION_H
#define CPP2SERVER_TESTSERVERCONNECTION_H

#include <asio/ip/tcp.hpp>

class TestServerConnection {
public:
    TestServerConnection(const std::string &host, const std::string &port);

    std::string waitForIncomingMessage();

    void sentOutgoingMessage(const std::string &message);

    std::istream &getIncomingStream();

    void pipeStreamTillEnd(const std::istream &inputStream);

private:
    asio::ip::tcp::iostream stream;
};

#endif //CPP2SERVER_TESTSERVERCONNECTION_H
