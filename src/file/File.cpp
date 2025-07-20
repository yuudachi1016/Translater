#include "File.h"
#include <fstream>

std::string File::ReadFile(const std::string& filename)
{
    FILE* fp = nullptr;
    fp       = fopen(filename.data(), "rb");
    if (!fp) return std::string();

    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
    rewind(fp);
    std::string fileBin;
    fileBin.resize(fileSize);
    fread((char*)fileBin.data(), 1, fileSize, fp);
    fclose(fp);
    return fileBin;
}

void File::WriteFile(const std::string& filename, const std::string& fileBin)
{
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) return;
    ofs.write((char*)fileBin.data(), fileBin.size());
}
