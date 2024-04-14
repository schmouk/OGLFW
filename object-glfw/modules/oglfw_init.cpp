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


module oglfw:init;

import :monitor;


//===========================================================================
namespace oglfw::init
{
    BaseLib::BaseLib(
        const EPlatform platform,
        const EAnglePlatformType angle_platform_type,
        const bool joystick_hat_as_buttons,
        const bool cocoa_changedir_resources,
        const bool cocoa_create_menu_icon,
        const bool wayland_user_libdecor,
        const bool x11_use_xcb_surface
    ) noexcept
    {
        // original library intialization should take place only once
        if (!this->_already_inited) {
            // so, before initializing the original GLFW library, let's first initialize hints
            if (platform != EPlatform::ANY && this->is_platform_supported(platform)) {
                glfwInitHint(GLFW_PLATFORM, int(platform));
            }

            if (angle_platform_type != EAnglePlatformType::NONE) {
                glfwInitHint(GLFW_ANGLE_PLATFORM_TYPE, int(angle_platform_type));
            }

            if (!joystick_hat_as_buttons) {
                glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
            }

            if (!cocoa_changedir_resources) {
                glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
            }
            
            if (!cocoa_create_menu_icon) {
                glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
            }
            
            if (!wayland_user_libdecor) {
                glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_FALSE);
            }
                
            if (!x11_use_xcb_surface) {
                glfwInitHint(GLFW_X11_XCB_VULKAN_SURFACE, GLFW_FALSE);

            }

            // then, let's initialize the original GLFW library
            if (!glfwInit()) {
                // and if not ok, let's call the initialization error handler
                handle_init_error();
            }

            // some stuff has to be done with monitors
            glfwSetMonitorCallback(oglfw::monitor::Monitors::monitor_callback);

            this->_already_inited = true;
        }
    }
}
