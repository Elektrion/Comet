#pragma once

#include <string>

namespace comet {

	class Assets {
	public:
		static std::string loadFile(const std::string& filename);
		static std::string getAssetPath(const std::string& filename);
	};

}
