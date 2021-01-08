#include <iostream>
#include "../../include/communication/Server.h"
#include "../../include/Constants.h"

namespace cpp2 {
    Server::Server(const int serverPort, const std::string &syncDirectoryPath)
            : serverPort(serverPort), fileSystemManager(syncDirectoryPath) {}

    void Server::handleClientConnection() const {
        std::cout << "waiting for the client to connect" << NEW_LINE;
        ClientConnection clientConnection{serverPort};

        std::cout << "the client has connected" << NEW_LINE;
        clientConnection.sentOutgoingMessage(WELCOME_RESPONSE);

        auto handlingConnection = true;
        while (handlingConnection) {
            try {
                const auto message = clientConnection.waitForIncomingMessage();
                std::cout << "client sent command: " << message << NEW_LINE;
                const auto commandName = commandMapper.getCommandName(message);
                const auto command = commandFactory.createCommand(commandName);
                handlingConnection = command->execute(clientConnection, fileSystemManager);
            } catch (const std::logic_error &error) {
                const auto response = error.what();
                std::cout << "sent client error response: " << response << NEW_LINE;
                clientConnection.sentOutgoingMessage(response);
            }
        }
    }
}
