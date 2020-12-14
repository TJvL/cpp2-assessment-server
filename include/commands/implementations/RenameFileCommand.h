#ifndef CPP2SERVER_RENAMEFILECOMMAND_H
#define CPP2SERVER_RENAMEFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class RenameFileCommand : public AbstractCommand {
    public:
        explicit RenameFileCommand(cpp2::ClientConnection& clientConnection);

        ~RenameFileCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_RENAMEFILECOMMAND_H
