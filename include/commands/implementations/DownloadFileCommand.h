#ifndef CPP2SERVER_DOWNLOADFILECOMMAND_H
#define CPP2SERVER_DOWNLOADFILECOMMAND_H

#include "../AbstractCommand.h"

namespace cpp2 {
    class DownloadFileCommand : public AbstractCommand {
    public:
        explicit DownloadFileCommand(cpp2::ClientConnection& clientConnection);

        ~DownloadFileCommand() override = default;

        void execute() override;
    };
}

#endif //CPP2SERVER_DOWNLOADFILECOMMAND_H
