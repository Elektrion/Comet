#include "cmt_pch.h"
#include "WindowsWindow.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Comet/Core/Application.h"

#include "Comet/Event/KeyEvent.h"
#include "Comet/Event/MouseEvent.h"
#include "Comet/Event/WindowEvent.h"

namespace comet {

	WindowsWindow::WindowsWindow(const WindowProperties& props) {
		CMT_PROFILE_FUNCTION();

		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		CMT_PROFILE_FUNCTION();

		shutdown();
	}

	void WindowsWindow::setVsync(bool vsync) {
		CMT_PROFILE_FUNCTION();

		data.vsync = vsync;
		glfwSwapInterval(vsync ? 1 : 0);
	}

	void WindowsWindow::setMinimized(bool minimized) {
		CMT_PROFILE_FUNCTION();

		data.minimized = minimized;
		if(minimized)
			glfwIconifyWindow(window);
		else
			glfwRestoreWindow(window);
	}

	void WindowsWindow::setMaximized(bool maximized) {
		CMT_PROFILE_FUNCTION();

		data.maximized = maximized;
		if(maximized)
			glfwMaximizeWindow(window);
		else
			glfwRestoreWindow(window);
	}

	void WindowsWindow::beginImGui() {
		CMT_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// setup docspace
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiID dockspace_id = ImGui::GetID("Comet");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("File")) {
				if(ImGui::MenuItem("Close", nullptr))
					Application::get()->close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void WindowsWindow::endImGui() {
		CMT_PROFILE_FUNCTION();

		// end dockspace
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void WindowsWindow::onUpdate(Timestep dt) {
		CMT_PROFILE_FUNCTION();

		context->swapBuffers();
		{
			CMT_PROFILE_SCOPE("WindowsWindow::opUpdate - poll events");

			glfwPollEvents();
		}
	}

	void WindowsWindow::setEventCallback(EventCallbackFn callback) {
		data.event_callback = callback;
	}

	static int glfw_window_count = 0;

	static void glfwErrorCallback(int error, const char* description) {
		CMT_CORE_ERROR("glfw error: {0}, {1}", error, description);
	}

	void WindowsWindow::init(const WindowProperties& props) {
		CMT_PROFILE_FUNCTION();

		if(glfw_window_count == 0) {
			CMT_PROFILE_SCOPE("WindowsWindow::init - init glfw");

			int success = glfwInit();
			CMT_CORE_ASSERT(success == GLFW_TRUE, "Failed to initialize glfw!");
			glfwSetErrorCallback(glfwErrorCallback);
			glfw_window_count++;
		}

		{
			CMT_PROFILE_SCOPE("WindowsWindow::init - create glfw window");

#if defined(CMT_USE_OPENGL_4_5)
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#else
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
			CMT_CORE_ASSERT(window, "Failed to create the glfw window!");
			data.width = props.width;
			data.height = props.height;
			data.title = props.title;
			data.vsync = props.vsync;
			data.minimized = false;
			data.maximized = false;
		}
		
		context = GraphicsContext::create(window);
		context->init();

		setVsync(data.vsync);

		glfwSetWindowUserPointer(window, &data);

		{
			CMT_PROFILE_SCOPE("WindowsWindow::init - set glfw callbacks");

			// window callbacks

			glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowClosedEvent e;
				data->event_callback(e);
			});

			glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->width = uint32_t(width);
				data->height = uint32_t(height);

				WindowResizedEvent e{ data->width, data->height };
				data->event_callback(e);
			});

			glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->minimized = iconified == GLFW_TRUE;

				WindowMinimizedEvent e{ data->minimized };
				data->event_callback(e);
			});

			glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->maximized = maximized == GLFW_TRUE;

				WindowMaximizedEvent e{ data->maximized };
				data->event_callback(e);
			});

			// key callbacks

			glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				if(action == GLFW_PRESS) {
					KeyPressedEvent e{ uint32_t(key) };
					data->event_callback(e);
				}
				else if(action == GLFW_REPEAT) {
					KeyPressedEvent e{ uint32_t(key), true };
					data->event_callback(e);
				}
				else {
					KeyReleasedEvent e{ uint32_t(key) };
					data->event_callback(e);
				}
			});

			glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				KeyTypedEvent e{ codepoint };
				data->event_callback(e);
			});

			// mouse callbacks

			glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				if(action == GLFW_PRESS) {
					MouseButtonPressedEvent e{ uint32_t(button) };
					data->event_callback(e);
				}
				else {
					MouseButtonReleasedEvent e{ uint32_t(button) };
					data->event_callback(e);
				}
			});

			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent e{ int32_t(xpos), int32_t(ypos) };
				data->event_callback(e);
			});

			glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent e{ int32_t(xoffset), int32_t(yoffset) };
				data->event_callback(e);
			});
		}

		{
			CMT_PROFILE_SCOPE("WindowsWindow::init - init imgui");

			// imgui setup

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 150 core");
		}
	}

	void WindowsWindow::shutdown() {
		CMT_PROFILE_FUNCTION();

		{
			CMT_PROFILE_SCOPE("WindowsWindow::shutdown - shutdown imgui");

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		{
			CMT_PROFILE_SCOPE("WindowsWindow::shutdown - destroy glfw window");

			glfwDestroyWindow(window);
			window = nullptr;
			glfw_window_count--;
		}

		if(glfw_window_count == 0) {
			CMT_PROFILE_SCOPE("WindowsWindow::shutdown - terminate glfw");

			glfwTerminate();
		}
	}

}
