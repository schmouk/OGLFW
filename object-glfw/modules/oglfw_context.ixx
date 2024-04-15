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


export module oglfw:context;


//===========================================================================
export namespace oglfw::context
{
    //=======================================================================
    // Forward declarations
    // 
    export struct Context;
    export struct EGLContext;
    export struct OpenGLCompatProfileContext;
    export struct OpenGLCoreProfileContext;
    export struct OpenGLESContext;
    export struct OSMesaContext;

    export enum class EClientApi;
    export enum class EContextCreationApi;
    export enum class EContextReleaseBehavior;
    export enum class EContextRobustness;
    export enum class EOpenGLProfile;


    //=======================================================================
    export enum class EClientApi : int
    {
        OPENGL = GLFW_OPENGL_API,
        OPENGL_ES = GLFW_OPENGL_ES_API,
        NO_API = GLFW_NO_API
    };


    export enum class EContextCreationApi : int
    {
        NATIVE_CONTEXT = GLFW_NATIVE_CONTEXT_API,
        EGL_CONTEXT = GLFW_EGL_CONTEXT_API,
        OSMESA_CONTEXT = GLFW_OSMESA_CONTEXT_API
    };


    export enum class EContextReleaseBehavior : int
    {
        ANY_RELEASE_BEHAVIOR = GLFW_ANY_RELEASE_BEHAVIOR,
        RELEASE_BEHAVIOR_FLUSH = GLFW_RELEASE_BEHAVIOR_FLUSH,
        RELEASE_BEHAVIOR_NONE = GLFW_RELEASE_BEHAVIOR_NONE
    };


    export enum class EContextRobustness : int
    {
        NO_ROBUSTNESS = GLFW_NO_ROBUSTNESS,
        NO_RESET_NOTIF = GLFW_NO_RESET_NOTIFICATION,
        LOSE_CONTEXT_ON_RESET = GLFW_LOSE_CONTEXT_ON_RESET
    };


    export enum class EOpenGLProfile : int
    {
        OPENGL_ANY_POFILE = GLFW_OPENGL_ANY_PROFILE,
        OPENGL_COMPAT_PROFILE = GLFW_OPENGL_COMPAT_PROFILE,
        OPENGL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE
    };


    //=======================================================================
    export struct Context
    {
        EClientApi              client_api{ EClientApi::OPENGL };
        EContextCreationApi     context_creation_api{ EContextCreationApi::NATIVE_CONTEXT };
        EContextReleaseBehavior context_release_behavior{ EContextReleaseBehavior::ANY_RELEASE_BEHAVIOR };
        EContextRobustness      context_robustness{ EContextRobustness::NO_ROBUSTNESS };
        EOpenGLProfile          opengl_profile{ EOpenGLProfile::OPENGL_ANY_POFILE };
        int                     context_version_major{ 1 };
        int                     context_version_minor{ 0 };
        bool                    context_debug{ false };
        bool                    opengl_forward_compatible{ false };

        inline void clr_context_debug() noexcept
        {
            context_debug = false;
        }

        inline void clr_opengl_forward_compatible() noexcept
        {
            opengl_forward_compatible = false;
        }

        inline void set(const EClientApi client_api_) noexcept
        {
            client_api = client_api_;
        }

        inline void set(const EContextCreationApi context_creation_api_) noexcept
        {
            context_creation_api = context_creation_api_;
        }

        inline void set(const EContextReleaseBehavior context_release_behavior_) noexcept
        {
            context_release_behavior = context_release_behavior_;
        }

        inline void set(const EContextRobustness context_robustness_) noexcept
        {
            context_robustness = context_robustness_;
        }

        inline void set(const EOpenGLProfile opengl_profile_) noexcept
        {
            opengl_profile = opengl_profile_;
        }

        inline void set_context_debug() noexcept
        {
            context_debug = true;
        }

        inline void set_opengl_forward_compatible() noexcept
        {
            opengl_forward_compatible = true;
        }

        inline void set_version(const int version_major_, const int version_minor_) noexcept
        {
            context_version_major = version_major_;
            context_version_minor = version_minor_;
        }

    };


    //===========================================================================
    export struct EGLContext : public Context
    {
        inline EGLContext() noexcept
            : Context()
        {
            context_creation_api = EContextCreationApi::EGL_CONTEXT;
        }

        inline EGLContext(const Context& context_) noexcept
            : Context(context_)
        {
            context_creation_api = EContextCreationApi::EGL_CONTEXT;
        }

    };


    //===========================================================================
    export struct OpenGLCompatProfileContext : public Context
    {
        inline OpenGLCompatProfileContext() noexcept
            : Context()
        {
            opengl_profile = EOpenGLProfile::OPENGL_COMPAT_PROFILE;
        }

        inline OpenGLCompatProfileContext(const Context& context_) noexcept
            : Context(context_)
        {
            opengl_profile = EOpenGLProfile::OPENGL_COMPAT_PROFILE;
        }

    };


    //===========================================================================
    export struct OpenGLCoreProfileContext : public Context
    {
        inline OpenGLCoreProfileContext() noexcept
            : Context()
        {
            opengl_profile = EOpenGLProfile::OPENGL_CORE_PROFILE;
        }

        inline OpenGLCoreProfileContext(const Context& context_) noexcept
            : Context(context_)
        {
            opengl_profile = EOpenGLProfile::OPENGL_CORE_PROFILE;
        }

    };


    //===========================================================================
    export struct OpenGLESContext : public Context
    {
        inline OpenGLESContext() noexcept
            : Context()
        {
            client_api = EClientApi::OPENGL_ES;
        }

        inline OpenGLESContext(const Context& context_) noexcept
            : Context(context_)
        {
            client_api = EClientApi::OPENGL_ES;
        }

    };


    //===========================================================================
    export struct OSMesaContext : public Context
    {
        inline OSMesaContext() noexcept
            : Context()
        {
            context_creation_api = EContextCreationApi::OSMESA_CONTEXT;
        }

        inline OSMesaContext(const Context& context_) noexcept
            : Context(context_)
        {
            context_creation_api = EContextCreationApi::OSMESA_CONTEXT;
        }

    };

}