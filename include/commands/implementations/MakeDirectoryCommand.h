#ifndef CPP2SERVER_MAKEDIRECTORYCOMMAND_H
#define CPP2SERVER_MAKEDIRECTORYCOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class MakeDirectoryCommand : public AbstractCommand {
    public:
        explicit MakeDirectoryCommand(cpp2::ClientConnection& clientConnection);

        ~MakeDirectoryCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_MAKEDIRECTORYCOMMAND_H
