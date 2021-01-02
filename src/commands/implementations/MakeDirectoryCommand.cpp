#include "../../../include/commands/implementations/MakeDirectoryCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    MakeDirectoryCommand::MakeDirectoryCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool MakeDirectoryCommand::execute() {
        auto relativePath = clientConnection.waitForIncomingMessage();
        auto directoryName = clientConnection.waitForIncomingMessage();

        fileSystemManager.makeDirectory(relativePath, directoryName);

        clientConnection.sentOutgoingMessage(OK_RESPONSE);
        return true;
    }
}
