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


export module oglfw:init;



//===========================================================================
export namespace oglfw::init
{
    //=======================================================================
    // Forward declarations
    // 
    export enum class EAnglePlatformType;
    export enum class EPlatform;

    export class BaseLib;
    export class CocoaPlatformLib;
    export class StubPlatformLib;
    export class WaylandPlatformLib;
    export class Win32PlatformLib;
    export class X11PlatformLib;


    //=======================================================================
    export enum class EPlatform : int {
        UNKNOWN = -1,
        ANY = GLFW_ANY_PLATFORM,
        COCOA = GLFW_PLATFORM_COCOA,
        STUB = GLFW_PLATFORM_NULL,
        WAYLAND = GLFW_PLATFORM_WAYLAND,
        WIN32 = GLFW_PLATFORM_WIN32,
        X11 = GLFW_PLATFORM_X11,
    };

    export enum class EAnglePlatformType : int {
        D3D11 = GLFW_ANGLE_PLATFORM_TYPE_D3D11,
        D3D9 = GLFW_ANGLE_PLATFORM_TYPE_D3D9,
        METAL = GLFW_ANGLE_PLATFORM_TYPE_METAL,
        NONE = GLFW_ANGLE_PLATFORM_TYPE_NONE,
        OPENGL = GLFW_ANGLE_PLATFORM_TYPE_OPENGL,
        OPENGLES = GLFW_ANGLE_PLATFORM_TYPE_OPENGLES,
        VULKAN = GLFW_ANGLE_PLATFORM_TYPE_VULKAN,
    };


    //=======================================================================
    export class BaseLib
    {
    public:
        BaseLib(
            const EPlatform platform = EPlatform::ANY,
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true,
            const bool cocoa_changedir_resources = true,
            const bool cocoa_create_menu_icon = true,
            const bool wayland_user_libdecor = true,
            const bool x11_use_xcb_surface = true
        ) noexcept;

        inline virtual ~BaseLib() noexcept
        {
            // let's terminate the original GLFW library!
            glfwTerminate();
        }

        inline BaseLib(const BaseLib& other) noexcept = delete;
        inline BaseLib(BaseLib&& other) noexcept = delete;

        inline BaseLib& operator= (const BaseLib&) noexcept = delete;
        inline BaseLib& operator= (BaseLib&&) noexcept = delete;


        virtual void handle_init_error() noexcept
        {}

        [[nodiscard]]
        static inline EPlatform get_inited_platform() noexcept
        {
            return BaseLib::_already_inited ? EPlatform(glfwGetPlatform()) : EPlatform::UNKNOWN;
        }

        [[nodiscard]]
        static inline bool is_platform_supported(const EPlatform tested_platform) noexcept
        {
            return glfwPlatformSupported(int(tested_platform)) == GLFW_TRUE;
        }


    private:

        static inline bool _already_inited{ false };  //!< intialization stage status, set to true after first initialization

    };


    //=======================================================================
    export class CocoaPlatformLib : public BaseLib
    {
    public:
        inline CocoaPlatformLib(
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true,
            const bool cocoa_changedir_resources = true,
            const bool cocoa_create_menu_icon = true
        ) noexcept
            : BaseLib(EPlatform::COCOA, angle_platform_type, joystick_hat_as_buttons, cocoa_changedir_resources, cocoa_create_menu_icon)
        {}
    };

    //=======================================================================
    export class StubPlatformLib : public BaseLib
    {
    public:
        inline StubPlatformLib(
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true
        ) noexcept
            : BaseLib(EPlatform::ANY, angle_platform_type, joystick_hat_as_buttons)
        {}
    };

    //=======================================================================
    export class WaylandPlatformLib : public BaseLib
    {
    public:
        inline WaylandPlatformLib(
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true,
            const bool wayland_user_libdecor = true
        ) noexcept
            : BaseLib(EPlatform::WAYLAND, angle_platform_type, joystick_hat_as_buttons, wayland_user_libdecor)
        {}
    };

    //=======================================================================
    export class Win32PlatformLib : public BaseLib
    {
    public:
        inline Win32PlatformLib(
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true
        ) noexcept
            : BaseLib(EPlatform::WIN32, angle_platform_type, joystick_hat_as_buttons)
        {}
    };

    //=======================================================================
    export class X11PlatformLib : public BaseLib
    {
    public:
        inline X11PlatformLib(
            const EAnglePlatformType angle_platform_type = EAnglePlatformType::NONE,
            const bool joystick_hat_as_buttons = true
        ) noexcept
            : BaseLib(EPlatform::X11, angle_platform_type, joystick_hat_as_buttons)
        {}
    };

}