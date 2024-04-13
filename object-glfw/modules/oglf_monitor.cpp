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

#include "GLFW/glfw3.h"


module oglfw:monitor;

import oglfw;


//===========================================================================
namespace oglfw::monitor
{
    const bool Monitor::GammaRamp::set(
        std::vector<unsigned short>& red,
        std::vector<unsigned short>& green,
        std::vector<unsigned short>& blue) noexcept
    {
        if (red.size() != green.size() || red.size() != blue.size() || green.size() != blue.size())
            return false;

        if (_ramp_ptr == nullptr) {
            if (!set_current_ramp())
                return false;
        }

        _ramp_ptr->size = (unsigned int)red.size();
        _ramp_ptr->red = red.data();
        _ramp_ptr->green = green.data();
        _ramp_ptr->blue = blue.data();

        glfwSetGammaRamp(_monitor_ptr->get_handle(), _ramp_ptr);
        return true;
    }



    void Monitor::just_connected()
    {
        // sets the current video mode
        _current_video_mode = *(const_cast<oglfw::video::VideoMode*>(glfwGetVideoMode(_monitor_ptr)));

        // sets the available video modes
        int vid_modes_count;
        const GLFWvidmode* vid_modes_list{ glfwGetVideoModes(_monitor_ptr, &vid_modes_count) };
        _available_video_modes = oglfw::video::get_video_modes_list(vid_modes_list, vid_modes_count);

        // sets the physical size of this monitor (in mm)
        glfwGetMonitorPhysicalSize(_monitor_ptr, &_physical_size.sx, &_physical_size.sy);

        // sets the content scaling
        float h, w;
        glfwGetMonitorContentScale(_monitor_ptr, &w, &h);
        _content_scaling.set(double(h), double(w));

        // sets the virtual position of this monitor on the virtualdesktop, in screen coordinates
        glfwGetMonitorPos(_monitor_ptr, &_virtual_pos.x, &_virtual_pos.y);

        // sets the work area of this monitor, in screen coordinates
        int xpos, ypos, width, height;
        glfwGetMonitorWorkarea(_monitor_ptr, &xpos, &ypos, &width, &height);
        _work_area.set_pos(xpos, ypos);
        _work_area.resize(width, height);

        // sets the name of this monitor
        _name = glfwGetMonitorName(_monitor_ptr);

        // sets the gamma ramp of this monitor
        _current_gamma_ramp = GammaRamp(*this);
    }


    void Monitors::monitor_callback(GLFWmonitor* monitor, int event) noexcept
    {
        Monitor* monitor_ptr{ static_cast<Monitor*>(glfwGetMonitorUserPointer(monitor)) };

        if (event == GLFW_CONNECTED) {
            monitor_ptr->just_connected();
        }
        else if (event == GLFW_DISCONNECTED) {
            monitor_ptr->just_disconnected();
        }
    }


    void  Monitors::evaluate_monitors_list() noexcept
    {
        int monitors_count;
        GLFWmonitor** monitors_list{ glfwGetMonitors(&monitors_count) };

        _monitors_list.clear();
        for (int i = 0; i < monitors_count; ++i)
            _monitors_list.push_back(Monitor(monitors_list[i]));
    }


    MonitorsList& Monitors::get_monitors_list() noexcept
    {
        if (_monitors_list.empty())
            evaluate_monitors_list();

        return _monitors_list;
    }

}