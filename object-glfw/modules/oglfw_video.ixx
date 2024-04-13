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

#include <vector>

#include "GLFW/glfw3.h"


export module oglfw:video;


//===========================================================================
export namespace oglfw::video
{
    //=======================================================================
    export using VideoMode = GLFWvidmode;
    /*
    * int width;                        // the resolution width of this video mode (in pixels)
    * int height;                       // the resolution height of this video mode (in pixels)
    * int redBits, greenBits, blueBits; // the depth of each color component, in bits per pixel
    * int refreshRate;                  // the value in Hz of the refreshing rate of this video mode
    */

    export using VideoModesList = std::vector<VideoMode>;


    export VideoModesList get_video_modes_list(const GLFWvidmode* vid_modes_list, const int vid_modes_count) noexcept
    {
        VideoModesList res;

        for (int i = 0; i < vid_modes_count; ++i)
            res.push_back(vid_modes_list[i]);

        return res;
    }

}