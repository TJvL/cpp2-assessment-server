#ifndef CPP2SERVER_DELETECOMMAND_H
#define CPP2SERVER_DELETECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DeleteCommand : public AbstractCommand  {
    public:
        explicit DeleteCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~DeleteCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_DELETECOMMAND_H
