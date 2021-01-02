#include <iostream>
#include "../../include/communication/Server.h"
#include "../../include/Constants.h"

namespace cpp2 {
    Server::Server(const int serverPort, const std::string &syncDirectoryPath)
            : serverPort(serverPort), syncDirectoryPath(syncDirectoryPath) {}

    void Server::handleClientConnection() const {
        FileSystemManager fileSystemManager{syncDirectoryPath};
        std::cout << "waiting for the client to connect" << NEW_LINE;
        ClientConnection clientConnection{serverPort};

        std::cout << "the client has connected" << NEW_LINE;
        clientConnection.sentOutgoingMessage(std::string(WELCOME_RESPONSE));

        auto handlingConnection = true;
        while (handlingConnection) {
            try {
                auto message = clientConnection.waitForIncomingMessage();
                std::cout << "client sent command: " << message << NEW_LINE;
                auto commandName = commandMapper.getCommandName(message);
                auto command = commandFactory.createCommand(commandName, clientConnection, fileSystemManager);
                handlingConnection = command->execute();
            } catch (const std::logic_error &error) {
                const auto response = error.what();
                std::cout << "sent client error response: " << response << NEW_LINE;
                clientConnection.sentOutgoingMessage(response);
            }
        }
    }
}
