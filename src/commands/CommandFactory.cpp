#include "../../include/commands/CommandFactory.h"
#include "../../include/commands/implementations/ServerInformationCommand.h"
#include "../../include/commands/implementations/ListDirectoryCommand.h"
#include "../../include/commands/implementations/MakeDirectoryCommand.h"
#include "../../include/commands/implementations/DownloadFileCommand.h"
#include "../../include/commands/implementations/UploadFileCommand.h"
#include "../../include/commands/implementations/RenameFileCommand.h"
#include "../../include/commands/implementations/DeleteFileCommand.h"
#include "../../include/commands/implementations/CloseConnectionCommand.h"

namespace cpp2 {
    std::unique_ptr<AbstractCommand> CommandFactory::createCommand(CommandName commandName, ClientConnection& clientConnection) const {
        switch (commandName) {
            case CommandName::SERVER_INFORMATION:
                return std::move(CommandFactory::create<ServerInformationCommand>(clientConnection));
            case LIST_DIRECTORY:
                return std::move(CommandFactory::create<ListDirectoryCommand>(clientConnection));
            case MAKE_DIRECTORY:
                return std::move(CommandFactory::create<MakeDirectoryCommand>(clientConnection));
            case DOWNLOAD_FILE:
                return std::move(CommandFactory::create<DownloadFileCommand>(clientConnection));
            case UPLOAD_FILE:
                return std::move(CommandFactory::create<UploadFileCommand>(clientConnection));
            case RENAME_FILE:
                return std::move(CommandFactory::create<RenameFileCommand>(clientConnection));
            case DELETE_FILE:
                return std::move(CommandFactory::create<DeleteFileCommand>(clientConnection));
            case CLOSE_CONNECTION:
                return std::move(CommandFactory::create<CloseConnectionCommand>(clientConnection));
            default:
                throw std::runtime_error("the given command name has no implementation");
        }
    }
}
