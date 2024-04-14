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
        EContextRobustness      context_robustness{ EContextRobustness::NO_ROBUSTNESS };
        EContextReleaseBehavior context_release_behavior{ EContextReleaseBehavior::ANY_RELEASE_BEHAVIOR };
        EOpenGLProfile          opengl_profile{ EOpenGLProfile::OPENGL_ANY_POFILE };
        int                     context_version_major{ 1 };
        int                     context_version_minor{ 0 };
        bool                    opengl_forward_compatible{ false };
        bool                    context_debug{ false };
    };

}