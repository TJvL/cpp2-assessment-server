#include <iostream>
#include "../../../include/commands/implementations/UploadFileCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    bool UploadFileCommand::execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) {
        const auto relativePath = clientConnection.waitForIncomingMessage();
        const auto fileSize = std::stoul(clientConnection.waitForIncomingMessage());

        auto pathWithoutFile = std::filesystem::path{relativePath}.replace_filename("");
        if (!fileSystemManager.pathExists(pathWithoutFile)) {
            throw std::logic_error{ERROR_NO_SUCH_DIRECTORY};
        }

        if (fileSize > fileSystemManager.freeSpaceAvailable(relativePath)) {
            throw std::logic_error{ERROR_NOT_ENOUGH_DISK_SPACE};
        }

        if (!fileSystemManager.hasWritePermissions(relativePath)) {
            throw std::logic_error{ERROR_NO_PERMISSION};
        }

        clientConnection.sentOutgoingMessage(OK_RESPONSE);

        auto &inputStream = clientConnection.getIncomingStream();
        fileSystemManager.writeFileFromStream(relativePath, inputStream, fileSize);

        std::cout << "client file received" << NEW_LINE;

        return true;
    }
}
