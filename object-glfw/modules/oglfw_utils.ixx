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
#include <cassert>
#include <type_traits>
		

export module oglfw:utils;


//===========================================================================
export namespace oglfw::utils
{
    //=======================================================================
    // Forward declarations
    // 
    
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct OffsetT;

    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct RectT;

    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct SizeT;

    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct Vec2T;

    using Offset = OffsetT<int>;
    using Offsetf = OffsetT<double>;

    template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    using PosT = Vec2T<ComponentT>;
    using Pos = Vec2T<int>;
    using Posf = Vec2T<double>;
    using Posu = Vec2T<std::uint32_t>;

    using Rect = RectT<int>;
    using Rectf = RectT<double>;

    using Size = SizeT<int>;
    using Sizef = SizeT<double>;
    using Sizeu = SizeT<std::uint32_t>;

    using Vec2D = Vec2T<int>;
    using Vec2f = Vec2T<double>;
    using Vec2u = Vec2T<std::uint32_t>;


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct OffsetT
    {
        ComponentT dx{ ComponentT(0) };
        ComponentT dy{ ComponentT(0) };


        inline OffsetT() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic<T1>&& std::is_arithmetic<T2>
        inline OffsetT(const T1 dx_, const T2 dy_) noexcept
            : dx(ComponentT(dx_)), dy(ComponentT(dy_))
        {}

        template<typename T>
            requires std::is_arithmetic<T>
        inline OffsetT(const Vec2T<T>& vec) noexcept
            : dx(ComponentT(vec.x)), dy(ComponentT(vec.y))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline OffsetT(const OffsetT<T>& other) noexcept
            : dx(ComponentT(other.dx)), dy(ComponentT(dy))
        {}

        virtual inline ~OffsetT() noexcept = default;

        inline OffsetT(OffsetT&&) noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline OffsetT& operator= (const OffsetT<T>& other) noexcept
        {
            dx = ComponentT(other.dx);
            dy = ComponentT(other.dy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline OffsetT& operator= (const Vec2T<T>& vec) noexcept
        {
            dx = ComponentT(vec.x);
            dy = ComponentT(vec.y);
            return *this;
        }

        inline OffsetT& operator= (OffsetT&&) noexcept = default;

    };


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct RectT
    {
        ComponentT x_left{ ComponentT(0) };
        ComponentT x_right{ ComponentT(0) };
        ComponentT y_top{ ComponentT(0) };
        ComponentT y_bottom{ ComponentT(0) };

        inline RectT() noexcept = default;

        inline RectT(const ComponentT left, const ComponentT top, const ComponentT right, const ComponentT bottom) noexcept
            : x_left(std::min(left, right))
            , x_right(std::max(left, right))
            , y_top(std::min(top, bottom))
            , y_bottom(std::max(top, bottom))
        {}

        inline RectT(const PosT<ComponentT>& top_left_pos, const PosT<ComponentT>& bottom_right_pos) noexcept
            : x_left(std::min(top_left_pos.x, bottom_right_pos.x))
            , x_right(std::max(top_left_pos.x, bottom_right_pos.x))
            , y_top(std::min(top_left_pos.y, bottom_right_pos.y))
            , y_bottom(std::max(top_left_pos.y, bottom_right_pos.y))
        {}

        inline RectT(const PosT<ComponentT>& top_left_pos, const SizeT<ComponentT>& size) noexcept
            : x_left(top_left_pos.x)
            , x_right(top_left_pos.x + size.sx)
            , y_top(top_left_pos.y)
            , y_bottom(top_left_pos.y + size.sy)
        {}

        inline virtual ~RectT() noexcept = default;

        inline RectT(const RectT&) noexcept = default;
        inline RectT(RectT&&) noexcept = default;

        inline RectT& operator= (const RectT&) noexcept = default;
        inline RectT& operator= (RectT&&) noexcept = default;

        [[nodiscard]]
        inline const ComponentT height() const noexcept
        {
            return y_bottom - y_top;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        inline void move(const T1 x_offset, const T2 y_offset) noexcept
        {
            x_left += ComponentT(x_offset);
            x_right += ComponentT(x_offset);
            y_top += ComponentT(y_offset);
            y_bottom += ComponentT(y_offset);
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline void move(const OffsetT<T>& offset) noexcept
        {
            move(offset.dx, offset.dy);
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline void move(const Vec2T<T>& offset) noexcept
        {
            move(offset.x, offset.y);
        }

        [[nodiscard]]
        inline const PosT<ComponentT> pos() const noexcept
        {
            return PosT<ComponentT>(x_left, y_top);
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        inline void resize(const T1 new_width, const T2 new_height)
        {
            assert(new_width >= T1(0) && new_height >= T2(0));
            x_right = x_left + new_width;
            y_bottom = y_top + new_height;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void resize(const SizeT<T>& new_size) noexcept
        {
            x_right = x_left + new_size.sx;
            y_bottom = y_top + new_size.sy;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void resize(const Vec2T<T>& new_size) 
        {
            assert(new_size.x >= T(0) && new_size.y >= T(0));
            x_right = x_left + new_size.x;
            y_bottom = y_top + new_size.y;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const T scale)
        {
            assert(scale >= T(0));
            const ComponentT new_width{ scale * width() };
            const ComponentT new_height{ scale * height() };
            x_right = x_left + new_width;
            y_bottom = y_top + new_height;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline void scale(const T1 scale_x, const T2 scale_y)
        {
            assert(scale_x >= T1(0) && scale_y >= T2(0));
            const ComponentT new_width{ scale_x * width() };
            const ComponentT new_height{ scale_y * height() };
            x_right = x_left + new_width;
            y_bottom = y_top + new_height;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const OffsetT<T> scale)
        {
            assert(scale.dx >= T(0) && scale.dy >= T(0));
            const ComponentT new_width{ scale.dx * width() };
            const ComponentT new_height{ scale.dy * height() };
            x_right = x_left + new_width;
            y_bottom = y_top + new_height;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const Vec2T<T> scale)
        {
            assert(scale.x >= T(0) && scale.y >= T(0));
            const ComponentT new_width{ scale.x * width() };
            const ComponentT new_height{ scale.y * height() };
            x_right = x_left + new_width;
            y_bottom = y_top + new_height;
        }

        inline void set(const ComponentT left, const ComponentT top, const ComponentT right, const ComponentT bottom) noexcept
        {
            x_left = std::min(left, right);
            x_right = std::max(left, right);
            y_top = std::min(top, bottom);
            y_bottom = std::max(top, bottom);
        }

        inline void set(const PosT<ComponentT>& top_left_pos, const PosT<ComponentT>& bottom_right_pos) noexcept
        {
            x_left = std::min(top_left_pos.x, bottom_right_pos.x);
            x_right = std::max(top_left_pos.x, bottom_right_pos.x);
            y_top = std::min(top_left_pos.y, bottom_right_pos.y);
            y_bottom = std::max(top_left_pos.y, bottom_right_pos.y);
        }

        inline void set(const PosT<ComponentT>& top_left_pos, const SizeT<ComponentT>& size) noexcept
        {
            x_left = top_left_pos.x;
            x_right = top_left_pos.x + size.sx;
            y_top = top_left_pos.y;
            y_bottom = top_left_pos.y + size.sy;
        }

        inline void set_pos(const ComponentT left, const ComponentT top) noexcept
        {
            x_right += left - x_left;
            y_bottom += top - y_top;
            x_left = left;
            y_top = top;
        }

        inline void set_pos(const PosT<ComponentT>& new_pos) noexcept
        {
            set_pos(new_pos.x, new_pos.y);
        }

        [[nodiscard]]
        inline const SizeT<ComponentT> size() const noexcept
        {
            return SizeT<ComponentT>(width(), height());
        }

        [[nodiscard]]
        inline const ComponentT width() const noexcept
        {
            return x_right - x_left;
        }
    };


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct SizeT
    {
        ComponentT sx{ ComponentT(0) };
        ComponentT sy{ ComponentT(0) };


        inline SizeT() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline SizeT(const T1 sx_, const T2 sy_)
            : sx(ComponentT(sx_)), sy(ComponentT(sy_))
        {
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT(const SizeT<T>& other) noexcept
            : sx(ComponentT(other.sx)), sy(ComponentT(sy))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT(const Vec2T<T>& vec)
            : sx(ComponentT(vec.x)), sy(ComponentT(vec.y))
        {
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
        }

        virtual inline ~SizeT() noexcept = default;

        inline SizeT(SizeT&&) noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator= (const SizeT<T>& other) noexcept
        {
            sx = ComponentT(other.sx);
            sy = ComponentT(other.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator= (const Vec2T<T>& vec)
        {
            sx = ComponentT(vec.x);
            sy = ComponentT(vec.y);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        inline SizeT& operator= (SizeT&&) noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator+= (const SizeT<T>& other) noexcept
        {
            sx += ComponentT(other.sx);
            sy += ComponentT(other.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator+= (const Vec2T<T>& other)
        {
            sx += ComponentT(other.x);
            sy += ComponentT(other.y);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator+= (const OffsetT<T>& offset)
        {
            sx += ComponentT(offset.dx);
            sy += ComponentT(offset.dy);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const SizeT<T>& other)
        {
            sx -= ComponentT(other.sx);
            sy -= ComponentT(other.sy);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const Vec2T<T>& other)
        {
            sx -= ComponentT(other.x);
            sy -= ComponentT(other.y);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const OffsetT<T>& offset)
        {
            sx -= ComponentT(offset.dx);
            sy -= ComponentT(offset.dy);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline SizeT& operator*= (const T scaling) noexcept
        {
            assert(scaling >= ComponentT(0));
            sx *= scaling;
            sy *= scaling;
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline SizeT& operator/= (const T scaling)
        {
            assert(scaling > ComponentT(0));
            sx /= scaling;
            sy /= scaling;
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator+ (const SizeT<T>& other) noexcept
        {
            SizeT res{ *this };
            res += other;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator+ (const Vec2T<T>& vec) noexcept
        {
            SizeT res{ *this };
            res += vec;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator+ (const OffsetT<T>& offset) noexcept
        {
            SizeT res{ *this };
            res += offset;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        friend inline SizeT<T2> operator+ (const T1 offset, const SizeT<T2> size)
        {
            return size + offset;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator- (const SizeT<T>& other) noexcept
        {
            SizeT res{ *this };
            res -= other;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator- (const Vec2T<T>& vec) noexcept
        {
            SizeT res{ *this };
            res -= vec;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator- (const OffsetT<T>& offset) noexcept
        {
            SizeT res{ *this };
            res -= offset;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator* (const T scaling) noexcept
        {
            asssert(scaling > T(0));
            SizeT res{ *this };
            res *= scaling;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        friend inline SizeT<T2> operator* (const T1 scaling, const SizeT<T2> size)
        {
            return size * scaling;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT operator/ (const T scaling)
        {
            SizeT res{ *this };
            res /= scaling;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline void scale(const T1 sx, const T2 sy)
        {
            sx *= sx;
            sy *= sy;
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline void set(const T1 sx_, const T2 sy_)
        {
            sx = ComponentT(sx_);
            sy = ComponentT(sy_);
            assert(sx >= ComponentT(0) && sy >= ComponentT(0));
        }

    };


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct Vec2T
    {
        ComponentT x{ ComponentT(0) };
        ComponentT y{ ComponentT(0) };


        inline Vec2T() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic<T1> && std::is_arithmetic<T2>
        inline Vec2T(const T1 x_, const T2 y_) noexcept
            : x(ComponentT(x_)), y(ComponentT(y_))
        {}

        virtual inline ~Vec2T() noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const Vec2T<T>& other) noexcept
            : x(ComponentT(other.x)), y(ComponentT(y))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const SizeT<T>& size) noexcept
            : x(ComponentT(size.sx)), y(ComponentT(size.sy))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const OffsetT<T>& offset) noexcept
            : x(ComponentT(offset.dx)), y(ComponentT(offset.dy))
        {}

        inline Vec2T(Vec2T&&) noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator= (const Vec2T<T>& other) noexcept
        {
            x = ComponentT(other.x);
            y = ComponentT(other.y);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator= (const SizeT<T>& other) noexcept
        {
            x = ComponentT(other.sx);
            y = ComponentT(other.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator= (const OffsetT<T>& other) noexcept
        {
            x = ComponentT(other.dx);
            y = ComponentT(other.dy);
            return *this;
        }

        inline Vec2T& operator= (Vec2T&&) noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator+= (const Vec2T<T>& other) noexcept
        {
            x += ComponentT(other.x);
            y += ComponentT(other.y);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator+= (const SizeT<T>& offset) noexcept
        {
            x += ComponentT(offset.sx);
            y += ComponentT(offset.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator+= (const OffsetT<T>& offset) noexcept
        {
            x += ComponentT(offset.dx);
            y += ComponentT(offset.dy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator-= (const Vec2T<T>& other) noexcept
        {
            x -= ComponentT(other.x);
            y -= ComponentT(other.y);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator-= (const SizeT<T>& size) noexcept
        {
            x -= ComponentT(size.sx);
            y -= ComponentT(size.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T& operator-= (const OffsetT<T>& offset) noexcept
        {
            x -= ComponentT(offset.dx);
            y -= ComponentT(offset.dy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline Vec2T& operator*= (const T scaling) noexcept
        {
            assert(scaling > T(0));
            x *= scaling;
            y *= scaling;
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline Vec2T& operator/= (const T scaling) 
        {
            assert(scaling > T(0));
            x /= scaling;
            y /= scaling;
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator+ (const Vec2T<T>& other) noexcept
        {
            Vec2T res{ *this };
            res += other;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator+ (const SizeT<T>& size) noexcept
        {
            Vec2T res{ *this };
            res += size;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator+ (const OffsetT<T>& offset) noexcept
        {
            Vec2T res{ *this };
            res += offset;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        friend inline Vec2T<T2> operator+ (const SizeT<T1> size, const Vec2T<T2> vec)
        {
            return vec + size;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        friend inline Vec2T<T2> operator+ (const OffsetT<T1> offset, const Vec2T<T2> vec)
        {
            return vec + offset;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator- (const Vec2T<T>& other) noexcept
        {
            Vec2T res{ *this };
            res -= other;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator- (const SizeT<T>& size) noexcept
        {
            Vec2T res{ *this };
            res -= size;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator- (const OffsetT<T>& offset) noexcept
        {
            Vec2T res{ *this };
            res -= offset;
            return res;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator* (const T scaling) noexcept
        {
            asssert(scaling > T(0));
            Vec2T res{ *this };
            res *= scaling;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        friend inline Vec2T<T2> operator* (const T1 scaling, const Vec2T<T2> vec)
        {
            return vec * scaling;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T operator/ (const T scaling)
        {
            assert(scaling > ComponentT(0));
            Vec2T res{ *this };
            res /= scaling;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        inline void move(const T1 dx, const T2 dy)
        {
            x += ComponentT(dx);
            y += ComponentT(dy);
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void move(const OffsetT<T>& offset)
        {
            x += ComponentT(offset.dx);
            y += ComponentT(offset.dy);
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        inline void scale(const T1 sx, const T2 sy)
        {
            assert(sx > ComponentT(0) && sy > ComponentT(0));
            x *= sx;
            y *= sy;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const Vec2T<T>& vec)
        {
            scale(vec.x, vec.y);
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const SizeT<T>& size)
        {
            scale(size.sx, size.sy);
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline void scale(const OffsetT<T>& offset)
        {
            scale(offset.dx, offset.dy);
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        inline void set(const T1 x_, const T2 y_)
        {
            x = ComponentT(x);
            y = ComponentT(y);
        }

    };


}