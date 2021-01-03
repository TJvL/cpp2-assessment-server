#ifndef CPP2SERVER_MAKEDIRECTORYCOMMAND_H
#define CPP2SERVER_MAKEDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class MakeDirectoryCommand : public AbstractCommand {
    public:
        bool execute(ClientConnection &clientConnection, FileSystemManager &fileSystemManager) override;
    };
}

#endif //CPP2SERVER_MAKEDIRECTORYCOMMAND_H
