#ifndef CPP2SERVER_DELETECOMMAND_H
#define CPP2SERVER_DELETECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DeleteCommand : public AbstractCommand  {
    public:
        bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const override;
    };
}

#endif //CPP2SERVER_DELETECOMMAND_H
