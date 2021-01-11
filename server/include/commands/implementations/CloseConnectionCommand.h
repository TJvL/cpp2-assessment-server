#ifndef CPP2SERVER_CLOSECONNECTIONCOMMAND_H
#define CPP2SERVER_CLOSECONNECTIONCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class CloseConnectionCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const override;
    };
}

#endif //CPP2SERVER_CLOSECONNECTIONCOMMAND_H
