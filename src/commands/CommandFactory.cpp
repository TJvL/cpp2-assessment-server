#include "../../include/commands/CommandFactory.h"
#include "../../include/commands/implementations/ServerInformationCommand.h"
#include "../../include/commands/implementations/ListDirectoryCommand.h"
#include "../../include/commands/implementations/MakeDirectoryCommand.h"
#include "../../include/commands/implementations/DownloadFileCommand.h"
#include "../../include/commands/implementations/UploadFileCommand.h"
#include "../../include/commands/implementations/RenameCommand.h"
#include "../../include/commands/implementations/DeleteCommand.h"
#include "../../include/commands/implementations/CloseConnectionCommand.h"

namespace cpp2 {
    std::unique_ptr<AbstractCommand> CommandFactory::createCommand(const CommandName commandName, ClientConnection& clientConnection, FileSystemManager &fileSystemManager) const {
        switch (commandName) {
            case SERVER_INFORMATION:
                return CommandFactory::create<ServerInformationCommand>(clientConnection, fileSystemManager);
            case LIST_DIRECTORY:
                return CommandFactory::create<ListDirectoryCommand>(clientConnection, fileSystemManager);
            case MAKE_DIRECTORY:
                return CommandFactory::create<MakeDirectoryCommand>(clientConnection, fileSystemManager);
            case DOWNLOAD_FILE:
                return CommandFactory::create<DownloadFileCommand>(clientConnection, fileSystemManager);
            case UPLOAD_FILE:
                return CommandFactory::create<UploadFileCommand>(clientConnection, fileSystemManager);
            case RENAME:
                return CommandFactory::create<RenameCommand>(clientConnection, fileSystemManager);
            case DELETE:
                return CommandFactory::create<DeleteCommand>(clientConnection, fileSystemManager);
            case CLOSE_CONNECTION:
                return CommandFactory::create<CloseConnectionCommand>(clientConnection, fileSystemManager);
            default:
                throw std::runtime_error("the given command name has no implementation");
        }
    }
}
