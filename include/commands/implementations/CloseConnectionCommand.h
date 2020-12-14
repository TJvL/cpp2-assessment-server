#ifndef CPP2SERVER_CLOSECONNECTIONCOMMAND_H
#define CPP2SERVER_CLOSECONNECTIONCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class CloseConnectionCommand : public AbstractCommand {
    public:
        explicit CloseConnectionCommand(cpp2::ClientConnection& clientConnection);

        ~CloseConnectionCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_CLOSECONNECTIONCOMMAND_H
