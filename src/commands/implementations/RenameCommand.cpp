#include "../../../include/commands/implementations/RenameCommand.h"

namespace cpp2 {

    RenameCommand::RenameCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool RenameCommand::execute() {
        return true;
    }
}
