#include <iostream>
#include "../../../include/commands/implementations/CloseConnectionCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    bool CloseConnectionCommand::execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const {
        std::cout << "client has disconnected" << NEW_LINE;
        return false;
    }
}
