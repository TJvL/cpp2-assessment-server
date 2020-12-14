#include "../../../include/commands/implementations/ServerInformationCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {
    ServerInformationCommand::ServerInformationCommand(cpp2::ClientConnection &clientConnection)
            : AbstractCommand(clientConnection) {}

    void ServerInformationCommand::execute() {
        clientConnection.sentOutgoingMessage(std::string("AvanSync server ") + version + ", copyright (c) 2020 Thomas van Leeuwen.");
    }
}
