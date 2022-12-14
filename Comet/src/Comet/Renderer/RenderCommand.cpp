#include "cmt_pch.h"
#include "RenderCommand.h"

namespace comet {

	Scope<RenderAPI> RenderCommand::render_api = nullptr;

	void RenderCommand::init() {
		render_api = RenderAPI::create();
	}

}
