#pragma once

#include <string>
#include <optional>

namespace comet {

	class Assets {
	public:
		static std::optional<std::string> loadFile(const std::string& filename);
		static std::string getAssetPath(const std::string& filename);
	};

}
