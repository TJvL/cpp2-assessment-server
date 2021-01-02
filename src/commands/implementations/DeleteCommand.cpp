#include "../../../include/commands/implementations/DeleteCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {
    DeleteCommand::DeleteCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool DeleteCommand::execute() {
        auto relativePath = clientConnection.waitForIncomingMessage();
        fileSystemManager.deletePath(relativePath);
        clientConnection.sentOutgoingMessage(OK_RESPONSE);
        return true;
    }
}
