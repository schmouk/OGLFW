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

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "GLFW/glfw3.h"


export module oglfw:window;

import :context;
import :errors;
import :monitor;
import :utils;
import :video;


//===========================================================================
export namespace oglfw::wndw
{
    //=======================================================================
    // Forward declarations
    // 
    export class Window;
    export class DecoratedWindow;
    export class ScreenWindow;

    using WindowHints = std::uint32_t;

    export enum class EWindowHints : WindowHints
    {
        AUTO_ICONIFY             = 1 << 0,
        CENTER_CURSOR            = 1 << 1,
        COCOA_FRAME_NAME         = 1 << 2,
        COCOA_GRAPHICS_SWITCHING = 1 << 3,
        CONTEXT_DEBUG            = 1 << 4,
        CONTEXT_NO_ERROR         = 1 << 5,
        DECORATED                = 1 << 6,
        DOUBLE_BUFFER            = 1 << 7,
        FLOATING                 = 1 << 8,
        FOCUS_ON_SHOW            = 1 << 9,
        FOCUSED                  = 1 << 10,
        MAXIMIZED                = 1 << 11,
        MOUSE_PASSTHROUGH        = 1 << 12,
        OPENGL_FORWARD_COMPAT    = 1 << 13,
        RESIZABLE                = 1 << 14,
        SCALE_FRAMEBUFFER        = 1 << 15,
        SCALE_TO_MONITOR         = 1 << 16,
        SRGB_CAPABLE             = 1 << 17,
        STEREO                   = 1 << 18,
        TRANSPARENT_FRAMEBUFFER  = 1 << 19,
        VISIBLE                  = 1 << 20,
        WIN32_KEYBOARD_MENU      = 1 << 21,
        WIN32_SHOWDEFAULT        = 1 << 22
    };


    //=======================================================================
    export class Window
    {
    public:
    
        Window(const int width, const int height) noexcept;

        Window(const int width, const int height, const std::string& title) noexcept;

        Window(const int width, const int height, Window& sharing_window) noexcept;

        Window(const int width, const int height, const std::string& title, Window& sharing_window) noexcept;

        Window(const int width, const int height, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept;

        Window(oglfw::monitor::Monitor& monitor) noexcept;

        Window(const std::string& title, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const int width, const int height, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;

        Window(const WindowHints window_hints, const oglfw::context::Context& context, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept;


        virtual ~Window() noexcept;
        

        Window(const Window&) = delete;
        Window(Window&&) = delete;


        inline void clear_close_flag() const noexcept
        {
            if (this->is_ok()) {
                glfwSetWindowShouldClose(this->get_handle(), GLFW_FALSE);
            }
        }


        static inline void close_callback(GLFWwindow* window_hndl) noexcept
        {
            // TODO: implement this
        }


        inline GLFWwindow* get_handle() const noexcept
        {
            return _window_ptr;
        }
    

        inline void* get_user_pointer() const noexcept
        {
            if (this->is_ok()) [[likely]]
                return glfwGetWindowUserPointer(this->get_handle());
            else
                return nullptr;
        }


        inline const bool is_close_flag_down() const noexcept
        {
            return !is_close_flag_up();
        }


        inline const bool is_close_flag_up() const noexcept
        {
            return this->is_ok() && glfwWindowShouldClose(this->get_handle());
        }


        inline const bool is_currently_full_screen() const noexcept
        {
            return is_ok() && glfwGetWindowMonitor(this->get_handle()) != nullptr;
        }


        const inline bool is_ok() const noexcept
        {
            return _window_ptr != nullptr;
        }


        const bool reset_all_windows_default_hints() const noexcept;


        const bool reset_default_hints() const noexcept;


        inline void set_close_flag() const noexcept
        {
            if (this->is_ok()) {
                glfwSetWindowShouldClose(get_handle(), GLFW_TRUE);
            }
        }


        const bool set_full_screen(
            const oglfw::monitor::Monitor& monitor,
            const int x_left,
            const int y_top,
            const int width,
            const int height,
            const int refresh_rate = GLFW_DONT_CARE) const noexcept;

        const bool set_full_screen(const oglfw::monitor::Monitor& monitor) const noexcept;

        const bool set_full_screen(const oglfw::monitor::Monitor& monitor, const int refresh_rate) const noexcept;

        const bool set_user_pointer(void* pointer) const noexcept;


        inline const bool set_windowed_mode(
            const int x_left,
            const int y_top,
            const int width,
            const int height) const noexcept
        {
            set_full_screen(oglfw::monitor::NULL_MONITOR, x_left, y_top, width, height, GLFW_DONT_CARE);
        }


    protected:
        GLFWwindow* _window_ptr{ nullptr };


    private:
        inline GLFWwindow* _create_full_screen(const std::string& title, const oglfw::monitor::Monitor& monitor) noexcept
        {
            oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return glfwCreateWindow(video_mode.width, video_mode.height, title.c_str(), monitor.get_handle(), nullptr);
        }

        inline GLFWwindow* _create_full_screen(const std::string& title, const oglfw::monitor::Monitor& monitor, const Window& sharing_window) noexcept
        {
            oglfw::video::VideoMode video_mode{ monitor.get_current_video_mode() };
            return glfwCreateWindow(video_mode.width, video_mode.height, title.c_str(), monitor.get_handle(), sharing_window.get_handle());
        }

        void _set_hints(const WindowHints hints, const oglfw::context::Context& context) noexcept;

        inline void _set_user_ptr() noexcept
        {
            if (this->is_ok())
                glfwSetWindowUserPointer(this->get_handle(), this);
        }
    

        struct _WindowsList : public std::vector<Window*>
        {
            using MyContainerClass = std::vector<Window*>;


            inline _WindowsList() noexcept
                : MyContainerClass()
            {};

            virtual inline ~_WindowsList() noexcept = default;

            Window* find(GLFWwindow* window_hndl) const noexcept
            {
                auto it = std::find_if(this->begin(), this->end(), [window_hndl](Window* w) { return w->get_handle() == window_hndl; });
                if (it != this->end()) [[likely]]
                    return *it;
                else [[unlikely]]
                    return nullptr;
            }

            inline void push_back(Window* window_ptr) noexcept
            {
                if (window_ptr && window_ptr->is_ok())
                    MyContainerClass::push_back(window_ptr);
            }

            inline void remove(Window* window_ptr) noexcept
            {
                std::erase(*this, window_ptr);
            }

        };

        static _WindowsList _windows_list;

    };


    //=======================================================================
    export class DecoratedWindow : public Window
    {
    public:

        inline DecoratedWindow(const int width, const int height) noexcept
            : Window(width, height)
        {}

        inline DecoratedWindow(const int width, const int height, const std::string& title) noexcept
            : Window(width, height, title)
        {}

        inline DecoratedWindow(const int width, const int height, Window& sharing_window) noexcept
            : Window(width, height, sharing_window)
        {}

        inline DecoratedWindow(const int width, const int height, const std::string& title, Window& sharing_window) noexcept
            : Window(width, height, title, sharing_window)
        {}

        inline virtual ~DecoratedWindow() noexcept = default;


    protected:

    };


    //=======================================================================
    export class ScreenWindow : public Window
    {
    public:

        inline ScreenWindow(const int width, const int height, oglfw::monitor::Monitor& monitor) noexcept
            : Window(width, height, monitor)
        {}

        inline ScreenWindow(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
            : Window(width, height, title, monitor)
        {}

        inline ScreenWindow(oglfw::monitor::Monitor& monitor) noexcept
            : Window(monitor)
        {}

        inline ScreenWindow(const std::string& title, oglfw::monitor::Monitor& monitor) noexcept
            : Window(title, monitor)
        {}

        inline ScreenWindow(const int width, const int height, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
            : Window(width, height, monitor, sharing_window)
        {}

        inline ScreenWindow(const int width, const int height, const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
            : Window(width, height, title, monitor, sharing_window)
        {}

        inline ScreenWindow(oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
            : Window(monitor, sharing_window)
        {}

        inline ScreenWindow(const std::string& title, oglfw::monitor::Monitor& monitor, Window& sharing_window) noexcept
            : Window(title, monitor, sharing_window)
        {}


        inline virtual ~ScreenWindow() noexcept = default;


    protected:

    };


}