#ifndef CPP2SERVER_DELETEFILECOMMAND_H
#define CPP2SERVER_DELETEFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DeleteFileCommand : public AbstractCommand  {
    public:
        explicit DeleteFileCommand(cpp2::ClientConnection& clientConnection);

        ~DeleteFileCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_DELETEFILECOMMAND_H
