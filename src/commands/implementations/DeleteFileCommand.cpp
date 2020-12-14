#include "../../../include/commands/implementations/DeleteFileCommand.h"

namespace cpp2 {
    DeleteFileCommand::DeleteFileCommand(ClientConnection &clientConnection)
            : AbstractCommand(clientConnection) {}

    void DeleteFileCommand::execute() {
    }
}
