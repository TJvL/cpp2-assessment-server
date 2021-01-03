#include <ctime>
#include <vector>
#include <sstream>
#include "../../include/filesystem/FileInfo.h"

namespace cpp2 {

    std::string FileInfo::toString() const {
        std::vector<char> buffer(20);
        std::strftime(buffer.data(), 20, "%Y-%m-%d %H:%M:%S", std::localtime(&lastModified));
        std::stringstream stringStream;
        stringStream << getFileTypeCharacter() << '|'
                     << fileName << '|'
                     << buffer.data() << '|'
                     << fileSize;
        return stringStream.str();
    }

    char FileInfo::getFileTypeCharacter() const {
        switch (fileType) {
            case FILE:
                return 'F';
            case DIRECTORY:
                return 'D';
            case OTHER:
            default:
                return '*';
        }
    }
}
