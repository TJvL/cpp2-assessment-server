#ifndef CPP2SERVER_ABSTRACTCOMMAND_H
#define CPP2SERVER_ABSTRACTCOMMAND_H

#include <type_traits>
#include "../ClientConnection.h"

namespace cpp2 {
    class AbstractCommand {
    public:
        virtual ~AbstractCommand() = default;

        virtual void execute() = 0;

    protected:
        AbstractCommand(ClientConnection& clientConnection) : clientConnection(clientConnection) {};

        ClientConnection& clientConnection;
    };

    template<class C>
    concept ACommand = std::is_base_of<AbstractCommand, C>::value;
}

#endif //CPP2SERVER_ABSTRACTCOMMAND_H
