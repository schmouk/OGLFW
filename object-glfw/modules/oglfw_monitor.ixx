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
#include <vector>

#include "GLFW/glfw3.h"


export module oglfw:monitor;

import :utils;
import :video;


//===========================================================================
export namespace oglfw::monitor
{
    //=======================================================================
    // Forward declarations
    // 
    export class Monitor;
    export class Monitors;

    //export Monitor NULL_MONITOR;


    // types wrappers
    using MonitorsList = std::vector<Monitor>;


    //=======================================================================
    export class Monitor final
    {
    public:

        class GammaRamp final
        {
        public:
            inline GammaRamp() noexcept = default;

            inline GammaRamp(const Monitor& monitor) noexcept
                : _monitor_ptr(&monitor)
                , _ramp_ptr(const_cast<GLFWgammaramp*>(glfwGetGammaRamp(monitor.get_handle())))
            {}

            inline ~GammaRamp() noexcept = default;

            inline GammaRamp(const GammaRamp&) noexcept = default;
            inline GammaRamp(GammaRamp&&) noexcept = default;

            inline GammaRamp& operator=(const GammaRamp&) noexcept = default;
            inline GammaRamp& operator=(GammaRamp&&) noexcept = default;

            [[nodiscard]]
            inline const GLFWgammaramp* get_handle() const noexcept
            {
                return _ramp_ptr;
            }

            [[nodiscard]]
            inline const unsigned int get_size() const noexcept
            {
                return is_ok() ? _ramp_ptr->size : 0;
            }

            [[nodiscard]]
            inline const bool is_ok() const noexcept
            {
                return _ramp_ptr != nullptr;
            }

            const bool set(std::vector<unsigned short>& red,
                std::vector<unsigned short>& green,
                std::vector<unsigned short>& blue) noexcept;

            inline const bool set_current_ramp() noexcept
            {
                _ramp_ptr = const_cast<GLFWgammaramp*>(glfwGetGammaRamp(_monitor_ptr->get_handle()));
                return is_ok();
            }


        private:
            GLFWgammaramp* _ramp_ptr{ nullptr };
            const Monitor* _monitor_ptr{ nullptr };
        };


        inline Monitor(GLFWmonitor* monitor_ptr) noexcept
            : _monitor_ptr(monitor_ptr)
        {
            if (monitor_ptr) {
                glfwSetMonitorUserPointer(monitor_ptr, static_cast<void*>(this));
                just_connected();
            }
        }


        inline Monitor(const Monitor&) noexcept = default;
        inline Monitor(Monitor&&) noexcept = default;

        inline virtual ~Monitor() noexcept = default;

        inline const oglfw::video::VideoModesList& get_available_video_modes() const noexcept
        {
            return _available_video_modes;
        }

        inline const oglfw::utils::Sizef& get_content_scale() const noexcept
        {
            return _content_scaling;
        }

        inline const double get_content_x_scale() const noexcept
        {
            return _content_scaling.sx;
        }

        inline const double get_content_y_scale() const noexcept
        {
            return _content_scaling.sy;
        }

        inline GammaRamp& get_current_gamma_ramp() noexcept
        {
            return _current_gamma_ramp;
        }

        inline const GammaRamp& get_current_gamma_ramp() const noexcept
        {
            return _current_gamma_ramp;
        }

        inline const oglfw::video::VideoMode& get_current_video_mode() const noexcept
        {
            return _current_video_mode;
        }

        inline GLFWmonitor* get_handle() const noexcept
        {
            return _monitor_ptr;
        }

        inline const std::string& get_name() const noexcept
        {
            return _name;
        }

        inline const int get_physical_height_mm() const noexcept
        {
            return _physical_size.sy;
        }

        inline const utils::Sizeu get_physical_size_mm() const noexcept
        {
            return _physical_size;
        }

        inline const int get_physical_width_mm() const noexcept
        {
            return _physical_size.sx;
        }

        inline const int get_pixel_blue_depth() const noexcept
        {
            return _current_video_mode.blueBits;
        }

        inline const int get_pixel_green_depth() const noexcept
        {
            return _current_video_mode.greenBits;
        }

        inline const int get_pixel_red_depth() const noexcept
        {
            return _current_video_mode.redBits;
        }

        inline const int get_resolution_height() const noexcept
        {
            return _current_video_mode.height;
        }

        inline const int get_resolution_width() const noexcept
        {
            return _current_video_mode.width;
        }

        inline const int get_video_refresh_rate() const noexcept
        {
            return _current_video_mode.refreshRate;
        }

        inline const oglfw::utils::Pos& get_virtual_pos() const noexcept
        {
            return _virtual_pos;
        }

        inline const oglfw::utils::Rect& get_work_area() const noexcept
        {
            return _work_area;
        }

        inline const bool is_ok() const noexcept
        {
            return _monitor_ptr != nullptr;
        }

        void just_connected();

        void just_disconnected()
        {}

        inline void set_gamma_exponent(float gamma_value)
        {
            if (is_ok())
                glfwSetGamma(_monitor_ptr, gamma_value);
        }


    private:
        oglfw::video::VideoModesList _available_video_modes{};
        oglfw::video::VideoMode _current_video_mode{};

        GammaRamp _current_gamma_ramp{};

        std::string _name{};

        oglfw::utils::Sizef _content_scaling{};

        oglfw::utils::Size _physical_size{};
        oglfw::utils::Pos _virtual_pos{};
        oglfw::utils::Rect _work_area{};

        GLFWmonitor* _monitor_ptr{ nullptr };

    };


    //=======================================================================
    export class Monitors : public std::vector<Monitor>
    {
    public:

        static void monitor_callback(GLFWmonitor* monitor, int event) noexcept;

        [[nodiscard]]
        static inline Monitor get_primary_monitor() noexcept
        {
            return Monitor(glfwGetPrimaryMonitor());
        }

        static void evaluate_monitors_list() noexcept;

        [[nodiscard]]
        static MonitorsList& get_monitors_list() noexcept;


    private:
        static inline MonitorsList _monitors_list{};

    };


    //=======================================================================
    export Monitor NULL_MONITOR(nullptr);

}