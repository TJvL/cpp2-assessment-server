#ifndef CPP2SERVER_LISTDIRECTORYCOMMAND_H
#define CPP2SERVER_LISTDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class ListDirectoryCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) override;
    };
}

#endif //CPP2SERVER_LISTDIRECTORYCOMMAND_H
