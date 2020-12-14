#ifndef CPP2SERVER_UPLOADFILECOMMAND_H
#define CPP2SERVER_UPLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class UploadFileCommand : public AbstractCommand {
    public:
        explicit UploadFileCommand(cpp2::ClientConnection& clientConnection);

        ~UploadFileCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_UPLOADFILECOMMAND_H
