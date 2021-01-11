#include <iostream>
#include "../../../include/commands/implementations/DownloadFileCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    bool DownloadFileCommand::execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const {
        const auto relativePath = clientConnection.waitForIncomingMessage();

        if (!fileSystemManager.pathExists(relativePath)) {
            throw std::logic_error{ERROR_NO_SUCH_FILE};
        }

        if (!fileSystemManager.hasWritePermissions(relativePath)) {
            throw std::logic_error{ERROR_NO_PERMISSION};
        }

        const auto inputStream = fileSystemManager.openReadFileStream(relativePath);

        const auto fileSize = fileSystemManager.fileSize(relativePath);
        clientConnection.sentOutgoingMessage(std::to_string(fileSize));

        clientConnection.pipeStreamTillEnd(*inputStream);

        std::cout << "file sent to client" << NEW_LINE;

        return true;
    }
}
