#include <iostream>
#include "../../../include/commands/implementations/CloseConnectionCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    CloseConnectionCommand::CloseConnectionCommand(ClientConnection &clientConnection, FileSystemManager &syncManager)
            : AbstractCommand(clientConnection, syncManager) {}

    bool CloseConnectionCommand::execute() {
        std::cout << "client has disconnected" << NEW_LINE;
        return false;
    }
}
