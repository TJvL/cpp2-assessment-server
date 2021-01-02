#include "../../include/communication/ClientConnection.h"
#include "../../include/Constants.h"

namespace cpp2 {
    ClientConnection::ClientConnection(int listenPort)
            : acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), listenPort)) {
        acceptor.accept(stream.socket());
    }

    ClientConnection::~ClientConnection() {
        stream.close();
    }

    std::string ClientConnection::waitForIncomingMessage() {
        std::string message;
        getline(stream, message);

        if (stream.fail()) {
            throw std::runtime_error("connection interrupted");
        }

        message.erase(message.end() - 1); // remove '\r'

        return message;
    }

    void ClientConnection::sentOutgoingMessage(const std::string &message) {
        stream << message << RETURN_NEW_LINE;
    }

    std::istream& ClientConnection::getIncomingStream() {
        return stream;
    }

    void ClientConnection::pipeStreamTillEnd(const std::istream &inputStream) {
        stream << inputStream.rdbuf();
    }
}
