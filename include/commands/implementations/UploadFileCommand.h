#ifndef CPP2SERVER_UPLOADFILECOMMAND_H
#define CPP2SERVER_UPLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class UploadFileCommand : public AbstractCommand {
    public:
        explicit UploadFileCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~UploadFileCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_UPLOADFILECOMMAND_H
