#ifndef CPP2SERVER_SERVERINFORMATIONCOMMAND_H
#define CPP2SERVER_SERVERINFORMATIONCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class ServerInformationCommand : public AbstractCommand {
    public:
        explicit ServerInformationCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~ServerInformationCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_SERVERINFORMATIONCOMMAND_H
