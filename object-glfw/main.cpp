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

#include <iostream>

import oglfw;


int main()
{
    oglfw::init::BaseLib my_glfw_lib;

    std::cout << std::hex << int(my_glfw_lib.get_inited_platform()) << std::endl;

    std::cout << "cocoa  : " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::COCOA)) << std::endl;
    std::cout << "stub   : " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::STUB)) << std::endl;
    std::cout << "wayland: " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::WAYLAND)) << std::endl;
    std::cout << "win32  : " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::WIN32)) << std::endl;
    std::cout << "x11    : " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::X11)) << std::endl;
    std::cout << "any    : " << int(my_glfw_lib.is_platform_supported(oglfw::init::EPlatform::ANY)) << std::endl;

    return 0;
}