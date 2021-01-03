#include "../../../include/commands/implementations/RenameCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    RenameCommand::RenameCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool RenameCommand::execute() {
        const auto relativePath = clientConnection.waitForIncomingMessage();
        const auto newName = clientConnection.waitForIncomingMessage();

        if (!fileSystemManager.pathExists(relativePath)) {
            throw std::logic_error{ERROR_NO_SUCH_PATH};
        }

        if (!fileSystemManager.hasWritePermissions(relativePath)) {
            throw std::logic_error{ERROR_NO_PERMISSION};
        }

        fileSystemManager.renamePath(relativePath, newName);

        clientConnection.sentOutgoingMessage(OK_RESPONSE);

        return true;
    }
}
