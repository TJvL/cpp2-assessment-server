#include "../../../include/commands/implementations/CloseConnectionCommand.h"

namespace cpp2 {

    CloseConnectionCommand::CloseConnectionCommand(ClientConnection &clientConnection)
            : AbstractCommand(clientConnection) {}

    void CloseConnectionCommand::execute() {
    }
}
