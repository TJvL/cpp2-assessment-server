#include "../../../include/commands/implementations/DeleteCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {
    DeleteCommand::DeleteCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool DeleteCommand::execute() {
        const auto relativePath = clientConnection.waitForIncomingMessage();

        if (!fileSystemManager.pathExists(relativePath)) {
            throw std::logic_error{ERROR_NO_SUCH_PATH};
        }

        if (!fileSystemManager.hasWritePermissions(relativePath)) {
            throw std::logic_error{ERROR_NO_PERMISSION};
        }

        fileSystemManager.deletePath(relativePath);
        clientConnection.sentOutgoingMessage(OK_RESPONSE);
        return true;
    }
}
