#include "../../../include/commands/implementations/MakeDirectoryCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    bool MakeDirectoryCommand::execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) {
        const auto relativePath = clientConnection.waitForIncomingMessage();
        const auto directoryName = clientConnection.waitForIncomingMessage();

        if (!fileSystemManager.pathExists(relativePath)) {
            throw std::logic_error{ERROR_NO_SUCH_DIRECTORY};
        }

        if (!fileSystemManager.hasWritePermissions(relativePath)) {
            throw std::logic_error{ERROR_NO_PERMISSION};
        }

        fileSystemManager.makeDirectory(relativePath, directoryName);

        clientConnection.sentOutgoingMessage(OK_RESPONSE);

        return true;
    }
}
