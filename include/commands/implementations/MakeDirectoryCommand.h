#ifndef CPP2SERVER_MAKEDIRECTORYCOMMAND_H
#define CPP2SERVER_MAKEDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class MakeDirectoryCommand : public AbstractCommand {
    public:
        explicit MakeDirectoryCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~MakeDirectoryCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_MAKEDIRECTORYCOMMAND_H
