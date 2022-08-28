#pragma once

#include <string>

#include "Comet/Core/Core.h"

namespace comet {

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;
	public:
		static Ref<Shader> create(const std::string& vertex_source, const std::string& fragment_source);
	};

}
