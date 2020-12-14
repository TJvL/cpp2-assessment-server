#include "../../../include/commands/implementations/RenameFileCommand.h"

namespace cpp2 {

    RenameFileCommand::RenameFileCommand(ClientConnection &clientConnection)
            : AbstractCommand(clientConnection) {}

    void RenameFileCommand::execute() {
    }
}
