#include "../../../include/commands/implementations/ListDirectoryCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {
    ListDirectoryCommand::ListDirectoryCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
    : AbstractCommand(clientConnection, syncManager) {}

    bool ListDirectoryCommand::execute() {
        const auto relativePath = clientConnection.waitForIncomingMessage();

        if (!fileSystemManager.pathExists(relativePath)) {
            throw std::logic_error{ERROR_NO_SUCH_DIRECTORY};
        }

        const auto listing = fileSystemManager.listDirectoryInformation(relativePath);
        clientConnection.sentOutgoingMessage(std::to_string(listing.size()));

        for (const auto &fileInfo : listing) {
            clientConnection.sentOutgoingMessage(fileInfo.toString());
        }

        return true;
    }
}
