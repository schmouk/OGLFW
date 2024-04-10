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
    struct SizeT;

    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct Vec2T;

    using Offset = OffsetT<int>;
    using Offsetf = OffsetT<double>;

    using Pos = Vec2T<int>;
    using Posf = Vec2T<double>;
    using Posu = Vec2T<std::uint32_t>;

    using Size = Vec2T<std::uint32_t>;
    using Sizef = Vec2T<double>;
    using Sizeu = Size;

    using Vec2D = Vec2T<int>;
    using Vec2f = Vec2T<double>;
    using Vec2u = Vec2T<std::uint32_t>;


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct OffsetT
    {
        ComponentT dx{ ComponenT(0) };
        ComponentT dy{ ComponenT(0) };


        inline OffsetT() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic<T1>&& std::is_arithmetic<T2>
        inline OffsetT(const T1 dx_, const T2 dy_) noexcept
            : dx(ComponenT(dx_)), dy(ComponenT(dy_))
        {}

        template<typename T>
            requires std::is_arithmetic<T>
        inline OffsetT(const Vec2T<T>& vec) noexcept
            : dx(ComponentT(vec.x)), dy(ComponentT(vec.y))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline OffsetT(const OffsetT<T>& other) noexcept
            : dx(ComponenT(other.dx)), dy(ComponentT(dy))
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
    struct SizeT
    {
        ComponentT sx{ ComponenT(0) };
        ComponentT sy{ ComponenT(0) };


        inline SizeT() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic<T1>&& std::is_arithmetic<T2>
        inline SizeT(const T1 sx_, const T2 sy_) noexcept
            : sx(ComponenT(sx_)), sy(ComponenT(sy_))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT(const SizeT<T>& other) noexcept
            : sx(ComponenT(other.sx)), sy(ComponentT(sy))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT(const Vec2T<T>& vec) noexcept
            : sx(ComponenT(vec.x)), sy(ComponentT(vec.y))
        {}

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
        inline SizeT& operator= (const Vec2T<T>& vec) noexcept
        {
            sx = ComponentT(vec.x);
            sy = ComponentT(vec.y);
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
        inline SizeT& operator+= (const Vec2T<T>& other) noexcept
        {
            sx += ComponentT(other.x);
            sy += ComponentT(other.y);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator+= (const OffsetT<T>& offset) noexcept
        {
            sx += ComponentT(offset.dx);
            sy += ComponentT(offset.dy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const SizeT<T>& other) noexcept
        {
            sx -= ComponentT(other.sx);
            sy -= ComponentT(other.sy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const Vec2T<T>& other) noexcept
        {
            sx -= ComponentT(other.x);
            sy -= ComponentT(other.y);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline SizeT& operator-= (const OffsetT<T>& offset) noexcept
        {
            sx -= ComponentT(offset.dx);
            sy -= ComponentT(offset.dy);
            return *this;
        }

        template<typename T>
            requires std::is_arithmetic<T>
        inline SizeT& operator*= (const T scaling) noexcept
        {
            assert(scaling > ComponentT(0));
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
            assert(scaling > T(0));
            SizeT res{ *this };
            res /= scaling;
            return res;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline void scale(const T1 sx, const T2 sy)
        {
            assert(sx > T1(0) && sy > T2(0));
            sx *= sx;
            sy *= sy;
        }

        template<typename T1, typename T2>
            requires std::is_arithmetic_v<T1>&& std::is_arithmetic_v<T2>
        inline void set(const T1 sx_, const T2 sy_)
        {
            sx = ComponentT(sx);
            sy = ComponentT(sy);
        }

    };


    //=======================================================================
    export template<typename ComponentT>
        requires std::is_arithmetic_v<ComponentT>
    struct Vec2T
    {
        ComponentT x{ ComponenT(0) };
        ComponentT y{ ComponenT(0) };


        inline Vec2T() noexcept = default;

        template<typename T1, typename T2>
            requires std::is_arithmetic<T1> && std::is_arithmetic<T2>
        inline Vec2T(const T1 x_, const T2 y_) noexcept
            : x(ComponenT(x_)), y(ComponenT(y_))
        {}

        virtual inline ~Vec2T() noexcept = default;

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const Vec2T<T>& other) noexcept
            : x(ComponenT(other.x)), y(ComponentT(y))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const SizeT<T>& size) noexcept
            : x(ComponenT(size.sx)), y(ComponentT(size.sy))
        {}

        template<typename T>
            requires std::is_arithmetic_v<T>
        inline Vec2T(const OffsetT<T>& offset) noexcept
            : x(ComponenT(offset.dx)), y(ComponentT(offset.dy))
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