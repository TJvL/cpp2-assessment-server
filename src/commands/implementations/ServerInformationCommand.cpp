#include "../../../include/commands/implementations/ServerInformationCommand.h"
#include "../../../include/Constants.h"

namespace cpp2 {

    bool ServerInformationCommand::execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) {
        clientConnection.sentOutgoingMessage(INFO_RESPONSE);
        return true;
    }
}
