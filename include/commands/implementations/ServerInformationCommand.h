#ifndef CPP2SERVER_SERVERINFORMATIONCOMMAND_H
#define CPP2SERVER_SERVERINFORMATIONCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class ServerInformationCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const override;
    };
}

#endif //CPP2SERVER_SERVERINFORMATIONCOMMAND_H
