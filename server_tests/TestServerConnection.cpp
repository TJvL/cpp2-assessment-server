#include <iostream>
#include "TestServerConnection.h"
#include "../server/include/Constants.h"

TestServerConnection::TestServerConnection(const std::string &host, const std::string &port)
        : stream(host, port) {
    if (!stream) {
        throw std::runtime_error("could not connect to server");
    }
}

std::string TestServerConnection::waitForIncomingMessage() {
    std::string message;
    getline(stream, message);

    if (stream.fail()) {
        std::cout << "connection interrupted" << NEW_LINE;
        return "";
        //throw std::runtime_error("connection interrupted");
    }

    message.erase(message.end() - 1); // remove '\r'

    return message;
}

void TestServerConnection::sentOutgoingMessage(const std::string &message) {
    stream << message << RETURN_NEW_LINE;
}

std::istream& TestServerConnection::getIncomingStream() {
    return stream;
}

void TestServerConnection::pipeStreamTillEnd(const std::istream &inputStream) {
    stream << inputStream.rdbuf();
}
