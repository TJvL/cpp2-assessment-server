#include "../../../include/commands/implementations/ListDirectoryCommand.h"

namespace cpp2 {
    ListDirectoryCommand::ListDirectoryCommand(ClientConnection &clientConnection)
    : AbstractCommand(clientConnection) {}

    void ListDirectoryCommand::execute() {
    }
}
