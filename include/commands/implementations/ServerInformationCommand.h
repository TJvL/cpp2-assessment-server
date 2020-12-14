#ifndef CPP2SERVER_SERVERINFORMATIONCOMMAND_H
#define CPP2SERVER_SERVERINFORMATIONCOMMAND_H

#include "../AbstractCommand.h"
#include "../../ClientConnection.h"

namespace cpp2 {
    class ServerInformationCommand : public AbstractCommand {
    public:
        explicit ServerInformationCommand(cpp2::ClientConnection& clientConnection);

        ~ServerInformationCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_SERVERINFORMATIONCOMMAND_H
