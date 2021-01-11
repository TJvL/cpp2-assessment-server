#ifndef CPP2SERVER_ABSTRACTCOMMAND_H
#define CPP2SERVER_ABSTRACTCOMMAND_H

#include <type_traits>
#include "../communication/ClientConnection.h"
#include "../filesystem/FileSystemManager.h"

namespace cpp2 {
    class AbstractCommand {
    public:
        virtual ~AbstractCommand() = default;

        virtual bool execute(ClientConnection &clientConnection, const FileSystemManager &fileSystemManager) const = 0;

    protected:
        AbstractCommand() = default;
    };

    template<class C>
    concept ACommand = std::is_base_of<AbstractCommand, C>::value;
}

#endif //CPP2SERVER_ABSTRACTCOMMAND_H
