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
    std::unique_ptr<AbstractCommand> CommandFactory::createCommand(CommandName commandName, ClientConnection& clientConnection, FileSystemManager &syncManager) const {
        switch (commandName) {
            case SERVER_INFORMATION:
                return std::move(CommandFactory::create<ServerInformationCommand>(clientConnection, syncManager));
            case LIST_DIRECTORY:
                return std::move(CommandFactory::create<ListDirectoryCommand>(clientConnection, syncManager));
            case MAKE_DIRECTORY:
                return std::move(CommandFactory::create<MakeDirectoryCommand>(clientConnection, syncManager));
            case DOWNLOAD_FILE:
                return std::move(CommandFactory::create<DownloadFileCommand>(clientConnection, syncManager));
            case UPLOAD_FILE:
                return std::move(CommandFactory::create<UploadFileCommand>(clientConnection, syncManager));
            case RENAME:
                return std::move(CommandFactory::create<RenameCommand>(clientConnection, syncManager));
            case DELETE:
                return std::move(CommandFactory::create<DeleteCommand>(clientConnection, syncManager));
            case CLOSE_CONNECTION:
                return std::move(CommandFactory::create<CloseConnectionCommand>(clientConnection, syncManager));
            default:
                throw std::runtime_error("the given command name has no implementation");
        }
    }
}
