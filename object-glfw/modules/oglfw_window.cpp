/*
MIT License

Copyright (c) 2024 Philippe Schmouker, ph.schmouker (at) gmail.com

Permission is hereby granted,  free of charge,  to any person obtaining a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction,  including without limitation the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies of the Software,  and  to  permit  persons  to  whom  the  Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND,  EXPRESS  OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT  SHALL  THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT  OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

module;
#include <string>

#include "GLFW/glfw3.h"


module oglfw:window;

import :context;
import :errors;
import :monitor;


//===========================================================================
namespace oglfw::wndw
{

    Window::Window(const int width, const int height) noexcept
    {
        _window_ptr = glfwCreateWindow(width, height, "", nullptr, nullptr);
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const int width, const int height, const std::string& title) noexcept
    {
        _window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        _set_user_ptr();
        _windows_list.push_back(this);
    }


    Window::Window(const int width, const int height, Window& sharing_window) noexcept
    {
        _window_ptr = glfwCreateWindow(width, height, "", nullptr, sharing_window.get_handle());
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const int width, const int height, const std::string& title, Window& sharing_window) noexcept
    {
        _window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, sharing_window.get_handle());
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const int width, const int height, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = glfwCreateWindow(width, height, "", monitor.get_handle(), nullptr);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = glfwCreateWindow(width, height, title.c_str(), monitor.get_handle(), nullptr);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(oglfw::monitor::Monitor& monitor) noexcept
    {
        _window_ptr = _create_full_screen("", monitor);
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
    {
        _window_ptr = _create_full_screen(title, monitor);
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const int width, const int height, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = glfwCreateWindow(width, height, "", monitor.get_handle(), sharing_window.get_handle());
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = glfwCreateWindow(width, height, title.c_str(), monitor.get_handle(), sharing_window.get_handle());
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = _create_full_screen("", monitor, sharing_window);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _window_ptr = _create_full_screen(title, monitor, sharing_window);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height) noexcept
    {
        _set_hints(window_hints, context);
        _window_ptr = glfwCreateWindow(width, height, "", nullptr, nullptr);
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title) noexcept
    {
        _set_hints(window_hints, context);
        _window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, Window& sharing_window) noexcept
    {
        _set_hints(window_hints, context);
        _window_ptr = glfwCreateWindow(width, height, "", nullptr, sharing_window.get_handle());
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, Window& sharing_window) noexcept
    {
        _set_hints(window_hints, context);
        _window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, sharing_window.get_handle());
        _set_user_ptr();
        _windows_list.push_back(this);
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = glfwCreateWindow(width, height, "", monitor.get_handle(), nullptr);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = glfwCreateWindow(width, height, title.c_str(), monitor.get_handle(), nullptr);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = _create_full_screen("", monitor);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = _create_full_screen(title, monitor);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = glfwCreateWindow(width, height, "", monitor.get_handle(), sharing_window.get_handle());
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = glfwCreateWindow(width, height, title.c_str(), monitor.get_handle(), sharing_window.get_handle());
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = _create_full_screen("", monitor, sharing_window);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }

    Window::Window(const WindowHints window_hints, const oglfw::context::Context& context, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            _set_hints(window_hints, context);
            _window_ptr = _create_full_screen(title, monitor, sharing_window);
            _set_user_ptr();
            _windows_list.push_back(this);
        }
        else [[unlikely]] {
            _window_ptr = nullptr;
        }
    }


    Window::~Window() noexcept
    {
        if (_window_ptr != nullptr) {
            this->_windows_list.remove(this);
            glfwDestroyWindow(this->_window_ptr);
        }
    }


    void Window::clear_min_size_limits() noexcept
    {
        if (this->is_ok()) {
            this->_min_size.width = this->_MIN_WIDTH;
            this->_min_size.height = this->_MIN_HEIGHT;
            glfwSetWindowSizeLimits(this->get_handle(), GLFW_DONT_CARE, GLFW_DONT_CARE, this->_max_size.width, this->_max_size.height);
        }
    }


    void Window::clear_max_size_limits() noexcept
    {
        if (this->is_ok()) {
            this->_max_size.width = this->_MAX_WIDTH;
            this->_max_size.height = this->_MAX_HEIGHT;
            glfwSetWindowSizeLimits(this->get_handle(), this->_min_size.width, this->_min_size.height, GLFW_DONT_CARE, GLFW_DONT_CARE);
        }
    }


    void Window::clear_size_limits() noexcept
    {
        if (this->is_ok()) {
            this->_min_size.width = this->_MIN_WIDTH;
            this->_min_size.height = this->_MIN_HEIGHT;
            this->_max_size.width = this->_MAX_WIDTH;
            this->_max_size.height = this->_MAX_HEIGHT;
            glfwSetWindowSizeLimits(this->get_handle(), GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
        }
    }


    void Window::close_callback(GLFWwindow* window_hndl) noexcept
    {
        auto window_ptr{ Window::_windows_list.find(window_hndl) };

        if (window_ptr != nullptr) {
            window_ptr->_close_window();
        }
    }


    void Window::get_frame_thickness(int& left, int& top, int& right, int& bottom) noexcept
    {
        if (this->is_ok()) [[likely]] {
            glfwGetWindowFrameSize(this->get_handle(), &left, &top, &right, &bottom);
        }
        else [[unlikely]] {
            left = right = top = bottom = 0;
        }
    }


    oglfw::utils::Size Window::get_size() const noexcept
    {
        if (this->is_ok()) [[likely]] {
            int width, height;
            glfwGetWindowSize(this->get_handle(), &width, &height);
            return oglfw::utils::Size(int(width), int(height));
        }
        else [[unlikely]] {
            return oglfw::utils::Size(0, 0);
        }
    }


    const bool Window::reset_all_windows_default_hints() const noexcept
    {
        if (this->is_ok()) [[likely]] {
            glfwDefaultWindowHints();
            return oglfw::err::ErrorStatus::is_ok();
        }
        else [[unlikely]]
            return false;
    }


    const bool Window::reset_default_hints() const noexcept
    {
        if (this->is_ok()) [[likely]] {
            // TODO: implement this
            // ...
            return oglfw::err::ErrorStatus::is_ok();
        }
        else [[unlikely]]
            return false;
    }


    void Window::resize_callback(GLFWwindow* window_hndl, int width, int height) noexcept
    {
        auto window_ptr{ Window::_windows_list.find(window_hndl) };

        if (window_ptr != nullptr) {
            window_ptr->_resize(width, height);
        }
    }


    void Window::_set_all_callbacks(GLFWwindow* window_hndl) noexcept
    {
        if (window_hndl != nullptr) {
            glfwSetWindowCloseCallback(window_hndl, Window::close_callback);
            glfwSetWindowSizeCallback(window_hndl, Window::resize_callback);
        }
    }


    const bool Window::set_full_screen(
        const oglfw::monitor::Monitor& monitor,
        const int x_left,
        const int y_top,
        const int width,
        const int height,
        const int refresh_rate) const noexcept
    {
        if (this->is_ok()) [[likely]] {
            glfwSetWindowMonitor(this->get_handle(), monitor.get_handle(), x_left, y_top, width, height, refresh_rate);
            return oglfw::err::ErrorStatus::is_ok();
        }
        else [[unlikely]] {
            return false;
        }
    }


    const bool Window::set_full_screen(const oglfw::monitor::Monitor& monitor) const noexcept
    {
        if (this->is_ok()) [[likely]] {
            const oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return set_full_screen(monitor, 0, 0, video_mode.width, video_mode.height, video_mode.refreshRate);
        }
        else [[unlikely]] {
            return false;
        }
    }


    const bool Window::set_full_screen(const oglfw::monitor::Monitor& monitor, const int refresh_rate) const noexcept
    {
        if (this->is_ok()) [[likely]] {
            const oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return set_full_screen(monitor, 0, 0, video_mode.width, video_mode.height, refresh_rate);
        }
        else [[unlikely]] {
            return false;
        }
    }


    void Window::set_max_size(int max_width, int max_height)
    {
        if (this->is_ok()){
            this->_max_size = std::move(oglfw::utils::Size(max_width, max_height));
            glfwSetWindowSizeLimits(this->get_handle(), GLFW_DONT_CARE, GLFW_DONT_CARE, max_width, max_height);
        }
    }


    void Window::set_min_size(int min_width, int min_height)
    {
        if (this->is_ok()) {
            this->_min_size = std::move(oglfw::utils::Size(min_width, min_height));
            glfwSetWindowSizeLimits(this->get_handle(), min_width, min_height, GLFW_DONT_CARE, GLFW_DONT_CARE);
        }
    }


    void Window::set_size_limits(int min_width, int min_height, int max_width, int max_height)
    {
        if (this->is_ok()) {
            this->_min_size = std::move(oglfw::utils::Size(min_width, min_height));
            this->_max_size = std::move(oglfw::utils::Size(max_width, max_height));
            glfwSetWindowSizeLimits(this->get_handle(), min_width, min_height, max_width, max_height);
        }
    }


    const bool Window::set_user_pointer(void* pointer) const noexcept
    {
        if (this->is_ok()) [[likely]] {
            glfwSetWindowUserPointer(this->get_handle(), pointer);
            return oglfw::err::ErrorStatus::is_ok();
        }
        else [[unlikely]]
            return false;
    }


    GLFWwindow* Window::_create_full_screen(const std::string& title, const oglfw::monitor::Monitor& monitor) const noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return glfwCreateWindow(video_mode.width, video_mode.height, title.c_str(), monitor.get_handle(), nullptr);
            }
        else [[unlikely]]
            return nullptr;
    }


    GLFWwindow* Window::_create_full_screen(const std::string& title, const oglfw::monitor::Monitor& monitor, const Window& sharing_window) const noexcept
    {
        if (monitor.is_ok()) [[likely]] {
            oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return glfwCreateWindow(video_mode.width, video_mode.height, title.c_str(), monitor.get_handle(), sharing_window.get_handle());
            }
        else [[unlikely]]
            return nullptr;
    }



    void Window::_set_hints(const WindowHints hints, const oglfw::context::Context& context) noexcept
    {
        // TODO: implement this

    }


    Window::_WindowsList Window::_windows_list{};

}