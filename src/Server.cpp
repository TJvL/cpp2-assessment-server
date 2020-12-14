#include <iostream>
#include "../include/Server.h"
#include "../include/Constants.h"

namespace cpp2 {
    Server::Server(const int serverPort)
            : serverPort(serverPort) {}

    void Server::handleClientConnection() const {
        std::cout << "waiting for the client to connect" << lf;
        ClientConnection clientConnection{serverPort};

        std::cout << "the client has connected" << lf;
        clientConnection.sentOutgoingMessage(std::string("Welcome to AvanSync server ") + version);

        auto handlingConnection = true;
        while (handlingConnection) {
            try {
                auto message = clientConnection.waitForIncomingMessage();
                std::cout << "client command: " << message << lf;
                auto commandName = commandMapper.getCommandName(message);
                auto command = commandFactory.createCommand(commandName, clientConnection);
                command->execute();
            } catch (const std::logic_error &error) {
                const auto response = error.what();
                std::cerr << "sent client error response: " << response << lf;
                clientConnection.sentOutgoingMessage(response);
            }
        }
    }
}
