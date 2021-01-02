#ifndef CPP2SERVER_DOWNLOADFILECOMMAND_H
#define CPP2SERVER_DOWNLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DownloadFileCommand : public AbstractCommand {
    public:
        explicit DownloadFileCommand(ClientConnection& clientConnection, FileSystemManager &syncManager);

        ~DownloadFileCommand() override = default;

        bool execute() override;
    };
}

#endif //CPP2SERVER_DOWNLOADFILECOMMAND_H
