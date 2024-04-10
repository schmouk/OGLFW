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

#include <iostream>

#include "GLFW/glfw3.h"


export module oglfw:errors;



//===========================================================================
export namespace oglfw::err
{
    //=======================================================================
    // Forward declarations
    // 

    export struct BaseErrorHandler;
    export struct CoutErrorHandler;
    export class ErrorStatus;


    //=======================================================================
    export typedef void (*ErrorHandlerFunc)(int err_code, const char* err_descr);
    //export using ErrorHandlerFunc = GLFWerrorfun;



    //=======================================================================
    export struct BaseErrorHandler
    {
        inline BaseErrorHandler(ErrorHandlerFunc func) noexcept
        {
            glfwSetErrorCallback(func);
        }

    };


    //=======================================================================
    export struct CoutErrorHandler : public BaseErrorHandler
    {
        inline CoutErrorHandler() noexcept
            : BaseErrorHandler(this->handler)
        {}

        static inline void handler(int err_code, const char* err_descr) noexcept
        {
            std::cout << "!!! ERROR " << err_code << ": " << err_descr << std::endl;
        };

    };


    //=======================================================================
    export class ErrorStatus
    {
    public:
        static inline const int get_curent_error() noexcept
        {
            _last_error_code = glfwGetError(const_cast<const char**>(&_last_error_descr));
            return _last_error_code;
        }

        [[nodiscard]]
        static inline const int get_last_error_code() noexcept
        {
            return _last_error_code;
        }

        [[nodiscard]]
        static inline const char* get_last_error_descr() noexcept
        {
            return _last_error_descr;
        }

        [[nodiscard]]
        static inline const bool is_ok() noexcept
        {
            return get_curent_error() == GLFW_NO_ERROR;
        }

        [[nodiscard]]
        static inline const bool is_ok(const int error_code) noexcept
        {
            return error_code == GLFW_NO_ERROR;
        }

        [[nodiscard]]
        static inline const bool is_last_error_ok() noexcept
        {
            return get_last_error_code() == GLFW_NO_ERROR;
        }


    private:
        static inline int _last_error_code{ GLFW_NO_ERROR };
        static inline char* _last_error_descr{ nullptr };

    };
}