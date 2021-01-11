#ifndef CPP2SERVER_RENAMECOMMAND_H
#define CPP2SERVER_RENAMECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class RenameCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const override;
    };
}

#endif //CPP2SERVER_RENAMECOMMAND_H
