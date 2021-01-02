#ifndef CPP2SERVER_LISTDIRECTORYCOMMAND_H
#define CPP2SERVER_LISTDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class ListDirectoryCommand : public AbstractCommand {
    public:
        explicit ListDirectoryCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~ListDirectoryCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_LISTDIRECTORYCOMMAND_H
