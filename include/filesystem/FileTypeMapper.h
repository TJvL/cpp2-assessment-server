#ifndef CPP2SERVER_FILETYPEMAPPER_H
#define CPP2SERVER_FILETYPEMAPPER_H

namespace cpp2 {
    FileType getFileType(const std::filesystem::file_type fileType) {
        switch (fileType) {
            case std::filesystem::file_type::regular:
                return FileType::FILE;
            case std::filesystem::file_type::directory:
                return FileType::DIRECTORY;
            default:
                return FileType::OTHER;
        }
    }
}

#endif //CPP2SERVER_FILETYPEMAPPER_H
