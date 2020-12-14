#include "../../../include/commands/implementations/MakeDirectoryCommand.h"

namespace cpp2 {

    MakeDirectoryCommand::MakeDirectoryCommand(ClientConnection &clientConnection)
            : AbstractCommand(clientConnection) {}

    void MakeDirectoryCommand::execute() {
    }
}
