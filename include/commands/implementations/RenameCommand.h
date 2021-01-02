#ifndef CPP2SERVER_RENAMECOMMAND_H
#define CPP2SERVER_RENAMECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class RenameCommand : public AbstractCommand {
    public:
        explicit RenameCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~RenameCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_RENAMECOMMAND_H