#ifndef CPP2SERVER_RENAMECOMMAND_H
#define CPP2SERVER_RENAMECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class RenameCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) override;
    };
}

#endif //CPP2SERVER_RENAMECOMMAND_H
