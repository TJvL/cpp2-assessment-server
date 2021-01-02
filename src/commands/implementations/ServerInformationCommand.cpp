#include "../../../include/commands/implementations/ServerInformationCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {
    ServerInformationCommand::ServerInformationCommand(cpp2::ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool ServerInformationCommand::execute() {
        clientConnection.sentOutgoingMessage(INFO_RESPONSE);
        return true;
    }
}
