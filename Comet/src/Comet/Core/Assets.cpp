#include "cmt_pch.h"
#include "Assets.h"

#include "Comet/Core/Core.h"

namespace comet {

    std::optional<std::string> Assets::loadFile(const std::string& filename) {
        CMT_PROFILE_FUNCTION();

        std::ifstream in(getAssetPath(filename), std::ios::binary);
        if(!in) return {};

        std::string buffer;
        in.seekg(0, std::ios::end);
        buffer.resize(size_t(in.tellg()));
        in.seekg(0);
        in.read(buffer.data(), buffer.size());
        return buffer;
    }

    std::string Assets::getAssetPath(const std::string& filename) {
        return CMT_ASSETS_DIR + std::string("/") + filename;
    }

}
