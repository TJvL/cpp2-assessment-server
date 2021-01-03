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
    std::unique_ptr<AbstractCommand> CommandFactory::createCommand(const CommandName commandName) const {
        switch (commandName) {
            case SERVER_INFORMATION:
                return CommandFactory::create<ServerInformationCommand>();
            case LIST_DIRECTORY:
                return CommandFactory::create<ListDirectoryCommand>();
            case MAKE_DIRECTORY:
                return CommandFactory::create<MakeDirectoryCommand>();
            case DOWNLOAD_FILE:
                return CommandFactory::create<DownloadFileCommand>();
            case UPLOAD_FILE:
                return CommandFactory::create<UploadFileCommand>();
            case RENAME:
                return CommandFactory::create<RenameCommand>();
            case DELETE:
                return CommandFactory::create<DeleteCommand>();
            case CLOSE_CONNECTION:
                return CommandFactory::create<CloseConnectionCommand>();
            default:
                throw std::runtime_error("the given command name has no implementation");
        }
    }
}
