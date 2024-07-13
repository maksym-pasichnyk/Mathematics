//
// Created by Maksym Pasichnyk on 01.06.2024.
//
#pragma once

#include <cmath>
#include <utility>

#define DEFINE_COMPONENT(name, component)                                   \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    template<typename Self> requires(component < Len)                       \
    constexpr auto __##name##__(this Self const& self) -> T {               \
        return self.__fields[component];                                    \
    }                                                                       \
    template<typename U> requires(component < Len)                          \
    constexpr void __##name##__(this Self& self, U&& u) {                   \
        self.__fields[component] = static_cast<U&&>(u);                     \
    }

#define DEFINE_SWIZZLE_2(name, comp1, comp2)                                \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    constexpr auto __##name##__(this Self const& self) -> vec_t<T, 2> {     \
        return { self[comp1], self[comp2] };                                \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 2> const& u) {    \
        static_assert(                                                      \
            comp1 != comp2,                                                 \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self[comp1] = u[0];                                                 \
        self[comp2] = u[1];                                                 \
    }
#define DEFINE_SWIZZLE_3(name, comp1, comp2, comp3)                         \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    constexpr auto __##name##__(this Self const& self) -> vec_t<T, 3> {     \
        return { self[comp1], self[comp2], self[comp3] };                   \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 3> const& u) {    \
        static_assert(                                                      \
            (comp1 != comp2) && (comp2 != comp3),                           \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self[comp1] = u[0];                                                 \
        self[comp2] = u[1];                                                 \
        self[comp3] = u[2];                                                 \
    }
#define DEFINE_SWIZZLE_4(name, comp1, comp2, comp3, comp4)                  \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    constexpr auto __##name##__(this Self const& self) -> vec_t<T, 4> {     \
        return { self[comp1], self[comp2], self[comp3], self[comp4] };      \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 4> const& u) {    \
        static_assert(                                                      \
            (comp1 != comp2) && (comp2 != comp3) && (comp3 != comp4),       \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self[comp1] = u[0];                                                 \
        self[comp2] = u[1];                                                 \
        self[comp3] = u[2];                                                 \
        self[comp4] = u[3];                                                 \
    }

namespace math {
    template<typename T, typename U>
    using forward_like_t = std::conditional_t<
        std::is_rvalue_reference_v<T&&>,
        std::add_rvalue_reference_t<
            std::conditional_t<
                std::is_const_v<std::remove_reference_t<T>>,
                std::add_const_t<std::remove_reference_t<U>>,
                std::remove_const_t<std::remove_reference_t<U>>
            >
        >,
        std::add_lvalue_reference_t<
            std::conditional_t<
                std::is_const_v<std::remove_reference_t<T>>,
                std::add_const_t<std::remove_reference_t<U>>,
                std::remove_const_t<std::remove_reference_t<U>>
            >
        >
    >;

    template<typename T, size_t Len, typename = std::make_index_sequence<Len>>
    struct vec_impl;

    template<typename T, size_t Cols, size_t Rows, typename = std::make_index_sequence<Cols>, typename = std::make_index_sequence<Rows>>
    struct mat_impl;

    template<typename T, size_t Len>
    struct vec_t {
        using Self = vec_t;

        T __fields[Len];

        friend constexpr auto operator<=>(Self const& $1, Self const& $2) = default;

        template<typename Self>
        constexpr auto operator[](this Self&& self, size_t i) -> forward_like_t<Self, T> {
            return static_cast<forward_like_t<Self, T>>(self.__fields[i]);
        }

        friend constexpr auto operator+(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::add($1, $2);
        }
        friend constexpr auto operator-(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::sub($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::mul($1, $2);
        }
        friend constexpr auto operator/(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::div($1, $2);
        }
        friend constexpr auto operator%(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::mod($1, $2);
        }
        friend constexpr auto operator<<(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::shl($1, $2);
        }
        friend constexpr auto operator>>(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::shr($1, $2);
        }
        friend constexpr auto operator&(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::band($1, $2);
        }
        friend constexpr auto operator|(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::bor($1, $2);
        }
        friend constexpr auto operator^(Self const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::bxor($1, $2);
        }
        friend constexpr auto operator+(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::add($1, $2);
        }
        friend constexpr auto operator-(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::sub($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::mul($1, $2);
        }
        friend constexpr auto operator/(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::div($1, $2);
        }
        friend constexpr auto operator%(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::mod($1, $2);
        }
        friend constexpr auto operator<<(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::shl($1, $2);
        }
        friend constexpr auto operator>>(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::shr($1, $2);
        }
        friend constexpr auto operator&(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::band($1, $2);
        }
        friend constexpr auto operator|(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::bor($1, $2);
        }
        friend constexpr auto operator^(Self const& $1, T const& $2) -> Self {
            return vec_impl<T, Len>::bxor($1, $2);
        }
        friend constexpr auto operator+(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::add($1, $2);
        }
        friend constexpr auto operator-(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::sub($1, $2);
        }
        friend constexpr auto operator*(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::mul($1, $2);
        }
        friend constexpr auto operator/(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::div($1, $2);
        }
        friend constexpr auto operator%(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::mod($1, $2);
        }
        friend constexpr auto operator<<(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::shl($1, $2);
        }
        friend constexpr auto operator>>(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::shr($1, $2);
        }
        friend constexpr auto operator&(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::band($1, $2);
        }
        friend constexpr auto operator|(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::bor($1, $2);
        }
        friend constexpr auto operator^(T const& $1, Self const& $2) -> Self {
            return vec_impl<T, Len>::bxor($1, $2);
        }

        DEFINE_COMPONENT(x, 0);
        DEFINE_COMPONENT(y, 1);
        DEFINE_COMPONENT(z, 2);
        DEFINE_COMPONENT(w, 3);
        DEFINE_SWIZZLE_2(xx, 0,0);
        DEFINE_SWIZZLE_2(xy, 0,1);
        DEFINE_SWIZZLE_2(xz, 0,2);
        DEFINE_SWIZZLE_2(xw, 0,3);
        DEFINE_SWIZZLE_2(yx, 1,0);
        DEFINE_SWIZZLE_2(yy, 1,1);
        DEFINE_SWIZZLE_2(yz, 1,2);
        DEFINE_SWIZZLE_2(yw, 1,3);
        DEFINE_SWIZZLE_2(zx, 2,0);
        DEFINE_SWIZZLE_2(zy, 2,1);
        DEFINE_SWIZZLE_2(zz, 2,2);
        DEFINE_SWIZZLE_2(zw, 2,3);
        DEFINE_SWIZZLE_2(wx, 3,0);
        DEFINE_SWIZZLE_2(wy, 3,1);
        DEFINE_SWIZZLE_2(wz, 3,2);
        DEFINE_SWIZZLE_2(ww, 3,3);
        DEFINE_SWIZZLE_3(xxx, 0,0,0);
        DEFINE_SWIZZLE_3(xxy, 0,0,1);
        DEFINE_SWIZZLE_3(xxz, 0,0,2);
        DEFINE_SWIZZLE_3(xxw, 0,0,3);
        DEFINE_SWIZZLE_3(xyx, 0,1,0);
        DEFINE_SWIZZLE_3(xyy, 0,1,1);
        DEFINE_SWIZZLE_3(xyz, 0,1,2);
        DEFINE_SWIZZLE_3(xyw, 0,1,3);
        DEFINE_SWIZZLE_3(xzx, 0,2,0);
        DEFINE_SWIZZLE_3(xzy, 0,2,1);
        DEFINE_SWIZZLE_3(xzz, 0,2,2);
        DEFINE_SWIZZLE_3(xzw, 0,2,3);
        DEFINE_SWIZZLE_3(xwx, 0,3,0);
        DEFINE_SWIZZLE_3(xwy, 0,3,1);
        DEFINE_SWIZZLE_3(xwz, 0,3,2);
        DEFINE_SWIZZLE_3(xww, 0,3,3);
        DEFINE_SWIZZLE_3(yxx, 1,0,0);
        DEFINE_SWIZZLE_3(yxy, 1,0,1);
        DEFINE_SWIZZLE_3(yxz, 1,0,2);
        DEFINE_SWIZZLE_3(yxw, 1,0,3);
        DEFINE_SWIZZLE_3(yyx, 1,1,0);
        DEFINE_SWIZZLE_3(yyy, 1,1,1);
        DEFINE_SWIZZLE_3(yyz, 1,1,2);
        DEFINE_SWIZZLE_3(yyw, 1,1,3);
        DEFINE_SWIZZLE_3(yzx, 1,2,0);
        DEFINE_SWIZZLE_3(yzy, 1,2,1);
        DEFINE_SWIZZLE_3(yzz, 1,2,2);
        DEFINE_SWIZZLE_3(yzw, 1,2,3);
        DEFINE_SWIZZLE_3(ywx, 1,3,0);
        DEFINE_SWIZZLE_3(ywy, 1,3,1);
        DEFINE_SWIZZLE_3(ywz, 1,3,2);
        DEFINE_SWIZZLE_3(yww, 1,3,3);
        DEFINE_SWIZZLE_3(zxx, 2,0,0);
        DEFINE_SWIZZLE_3(zxy, 2,0,1);
        DEFINE_SWIZZLE_3(zxz, 2,0,2);
        DEFINE_SWIZZLE_3(zxw, 2,0,3);
        DEFINE_SWIZZLE_3(zyx, 2,1,0);
        DEFINE_SWIZZLE_3(zyy, 2,1,1);
        DEFINE_SWIZZLE_3(zyz, 2,1,2);
        DEFINE_SWIZZLE_3(zyw, 2,1,3);
        DEFINE_SWIZZLE_3(zzx, 2,2,0);
        DEFINE_SWIZZLE_3(zzy, 2,2,1);
        DEFINE_SWIZZLE_3(zzz, 2,2,2);
        DEFINE_SWIZZLE_3(zzw, 2,2,3);
        DEFINE_SWIZZLE_3(zwx, 2,3,0);
        DEFINE_SWIZZLE_3(zwy, 2,3,1);
        DEFINE_SWIZZLE_3(zwz, 2,3,2);
        DEFINE_SWIZZLE_3(zww, 2,3,3);
        DEFINE_SWIZZLE_3(wxx, 3,0,0);
        DEFINE_SWIZZLE_3(wxy, 3,0,1);
        DEFINE_SWIZZLE_3(wxz, 3,0,2);
        DEFINE_SWIZZLE_3(wxw, 3,0,3);
        DEFINE_SWIZZLE_3(wyx, 3,1,0);
        DEFINE_SWIZZLE_3(wyy, 3,1,1);
        DEFINE_SWIZZLE_3(wyz, 3,1,2);
        DEFINE_SWIZZLE_3(wyw, 3,1,3);
        DEFINE_SWIZZLE_3(wzx, 3,2,0);
        DEFINE_SWIZZLE_3(wzy, 3,2,1);
        DEFINE_SWIZZLE_3(wzz, 3,2,2);
        DEFINE_SWIZZLE_3(wzw, 3,2,3);
        DEFINE_SWIZZLE_3(wwx, 3,3,0);
        DEFINE_SWIZZLE_3(wwy, 3,3,1);
        DEFINE_SWIZZLE_3(wwz, 3,3,2);
        DEFINE_SWIZZLE_3(www, 3,3,3);
        DEFINE_SWIZZLE_4(xxxx, 0,0,0,0);
        DEFINE_SWIZZLE_4(xxxy, 0,0,0,1);
        DEFINE_SWIZZLE_4(xxxz, 0,0,0,2);
        DEFINE_SWIZZLE_4(xxxw, 0,0,0,3);
        DEFINE_SWIZZLE_4(xxyx, 0,0,1,0);
        DEFINE_SWIZZLE_4(xxyy, 0,0,1,1);
        DEFINE_SWIZZLE_4(xxyz, 0,0,1,2);
        DEFINE_SWIZZLE_4(xxyw, 0,0,1,3);
        DEFINE_SWIZZLE_4(xxzx, 0,0,2,0);
        DEFINE_SWIZZLE_4(xxzy, 0,0,2,1);
        DEFINE_SWIZZLE_4(xxzz, 0,0,2,2);
        DEFINE_SWIZZLE_4(xxzw, 0,0,2,3);
        DEFINE_SWIZZLE_4(xxwx, 0,0,3,0);
        DEFINE_SWIZZLE_4(xxwy, 0,0,3,1);
        DEFINE_SWIZZLE_4(xxwz, 0,0,3,2);
        DEFINE_SWIZZLE_4(xxww, 0,0,3,3);
        DEFINE_SWIZZLE_4(xyxx, 0,1,0,0);
        DEFINE_SWIZZLE_4(xyxy, 0,1,0,1);
        DEFINE_SWIZZLE_4(xyxz, 0,1,0,2);
        DEFINE_SWIZZLE_4(xyxw, 0,1,0,3);
        DEFINE_SWIZZLE_4(xyyx, 0,1,1,0);
        DEFINE_SWIZZLE_4(xyyy, 0,1,1,1);
        DEFINE_SWIZZLE_4(xyyz, 0,1,1,2);
        DEFINE_SWIZZLE_4(xyyw, 0,1,1,3);
        DEFINE_SWIZZLE_4(xyzx, 0,1,2,0);
        DEFINE_SWIZZLE_4(xyzy, 0,1,2,1);
        DEFINE_SWIZZLE_4(xyzz, 0,1,2,2);
        DEFINE_SWIZZLE_4(xyzw, 0,1,2,3);
        DEFINE_SWIZZLE_4(xywx, 0,1,3,0);
        DEFINE_SWIZZLE_4(xywy, 0,1,3,1);
        DEFINE_SWIZZLE_4(xywz, 0,1,3,2);
        DEFINE_SWIZZLE_4(xyww, 0,1,3,3);
        DEFINE_SWIZZLE_4(xzxx, 0,2,0,0);
        DEFINE_SWIZZLE_4(xzxy, 0,2,0,1);
        DEFINE_SWIZZLE_4(xzxz, 0,2,0,2);
        DEFINE_SWIZZLE_4(xzxw, 0,2,0,3);
        DEFINE_SWIZZLE_4(xzyx, 0,2,1,0);
        DEFINE_SWIZZLE_4(xzyy, 0,2,1,1);
        DEFINE_SWIZZLE_4(xzyz, 0,2,1,2);
        DEFINE_SWIZZLE_4(xzyw, 0,2,1,3);
        DEFINE_SWIZZLE_4(xzzx, 0,2,2,0);
        DEFINE_SWIZZLE_4(xzzy, 0,2,2,1);
        DEFINE_SWIZZLE_4(xzzz, 0,2,2,2);
        DEFINE_SWIZZLE_4(xzzw, 0,2,2,3);
        DEFINE_SWIZZLE_4(xzwx, 0,2,3,0);
        DEFINE_SWIZZLE_4(xzwy, 0,2,3,1);
        DEFINE_SWIZZLE_4(xzwz, 0,2,3,2);
        DEFINE_SWIZZLE_4(xzww, 0,2,3,3);
        DEFINE_SWIZZLE_4(xwxx, 0,3,0,0);
        DEFINE_SWIZZLE_4(xwxy, 0,3,0,1);
        DEFINE_SWIZZLE_4(xwxz, 0,3,0,2);
        DEFINE_SWIZZLE_4(xwxw, 0,3,0,3);
        DEFINE_SWIZZLE_4(xwyx, 0,3,1,0);
        DEFINE_SWIZZLE_4(xwyy, 0,3,1,1);
        DEFINE_SWIZZLE_4(xwyz, 0,3,1,2);
        DEFINE_SWIZZLE_4(xwyw, 0,3,1,3);
        DEFINE_SWIZZLE_4(xwzx, 0,3,2,0);
        DEFINE_SWIZZLE_4(xwzy, 0,3,2,1);
        DEFINE_SWIZZLE_4(xwzz, 0,3,2,2);
        DEFINE_SWIZZLE_4(xwzw, 0,3,2,3);
        DEFINE_SWIZZLE_4(xwwx, 0,3,3,0);
        DEFINE_SWIZZLE_4(xwwy, 0,3,3,1);
        DEFINE_SWIZZLE_4(xwwz, 0,3,3,2);
        DEFINE_SWIZZLE_4(xwww, 0,3,3,3);
        DEFINE_SWIZZLE_4(yxxx, 1,0,0,0);
        DEFINE_SWIZZLE_4(yxxy, 1,0,0,1);
        DEFINE_SWIZZLE_4(yxxz, 1,0,0,2);
        DEFINE_SWIZZLE_4(yxxw, 1,0,0,3);
        DEFINE_SWIZZLE_4(yxyx, 1,0,1,0);
        DEFINE_SWIZZLE_4(yxyy, 1,0,1,1);
        DEFINE_SWIZZLE_4(yxyz, 1,0,1,2);
        DEFINE_SWIZZLE_4(yxyw, 1,0,1,3);
        DEFINE_SWIZZLE_4(yxzx, 1,0,2,0);
        DEFINE_SWIZZLE_4(yxzy, 1,0,2,1);
        DEFINE_SWIZZLE_4(yxzz, 1,0,2,2);
        DEFINE_SWIZZLE_4(yxzw, 1,0,2,3);
        DEFINE_SWIZZLE_4(yxwx, 1,0,3,0);
        DEFINE_SWIZZLE_4(yxwy, 1,0,3,1);
        DEFINE_SWIZZLE_4(yxwz, 1,0,3,2);
        DEFINE_SWIZZLE_4(yxww, 1,0,3,3);
        DEFINE_SWIZZLE_4(yyxx, 1,1,0,0);
        DEFINE_SWIZZLE_4(yyxy, 1,1,0,1);
        DEFINE_SWIZZLE_4(yyxz, 1,1,0,2);
        DEFINE_SWIZZLE_4(yyxw, 1,1,0,3);
        DEFINE_SWIZZLE_4(yyyx, 1,1,1,0);
        DEFINE_SWIZZLE_4(yyyy, 1,1,1,1);
        DEFINE_SWIZZLE_4(yyyz, 1,1,1,2);
        DEFINE_SWIZZLE_4(yyyw, 1,1,1,3);
        DEFINE_SWIZZLE_4(yyzx, 1,1,2,0);
        DEFINE_SWIZZLE_4(yyzy, 1,1,2,1);
        DEFINE_SWIZZLE_4(yyzz, 1,1,2,2);
        DEFINE_SWIZZLE_4(yyzw, 1,1,2,3);
        DEFINE_SWIZZLE_4(yywx, 1,1,3,0);
        DEFINE_SWIZZLE_4(yywy, 1,1,3,1);
        DEFINE_SWIZZLE_4(yywz, 1,1,3,2);
        DEFINE_SWIZZLE_4(yyww, 1,1,3,3);
        DEFINE_SWIZZLE_4(yzxx, 1,2,0,0);
        DEFINE_SWIZZLE_4(yzxy, 1,2,0,1);
        DEFINE_SWIZZLE_4(yzxz, 1,2,0,2);
        DEFINE_SWIZZLE_4(yzxw, 1,2,0,3);
        DEFINE_SWIZZLE_4(yzyx, 1,2,1,0);
        DEFINE_SWIZZLE_4(yzyy, 1,2,1,1);
        DEFINE_SWIZZLE_4(yzyz, 1,2,1,2);
        DEFINE_SWIZZLE_4(yzyw, 1,2,1,3);
        DEFINE_SWIZZLE_4(yzzx, 1,2,2,0);
        DEFINE_SWIZZLE_4(yzzy, 1,2,2,1);
        DEFINE_SWIZZLE_4(yzzz, 1,2,2,2);
        DEFINE_SWIZZLE_4(yzzw, 1,2,2,3);
        DEFINE_SWIZZLE_4(yzwx, 1,2,3,0);
        DEFINE_SWIZZLE_4(yzwy, 1,2,3,1);
        DEFINE_SWIZZLE_4(yzwz, 1,2,3,2);
        DEFINE_SWIZZLE_4(yzww, 1,2,3,3);
        DEFINE_SWIZZLE_4(ywxx, 1,3,0,0);
        DEFINE_SWIZZLE_4(ywxy, 1,3,0,1);
        DEFINE_SWIZZLE_4(ywxz, 1,3,0,2);
        DEFINE_SWIZZLE_4(ywxw, 1,3,0,3);
        DEFINE_SWIZZLE_4(ywyx, 1,3,1,0);
        DEFINE_SWIZZLE_4(ywyy, 1,3,1,1);
        DEFINE_SWIZZLE_4(ywyz, 1,3,1,2);
        DEFINE_SWIZZLE_4(ywyw, 1,3,1,3);
        DEFINE_SWIZZLE_4(ywzx, 1,3,2,0);
        DEFINE_SWIZZLE_4(ywzy, 1,3,2,1);
        DEFINE_SWIZZLE_4(ywzz, 1,3,2,2);
        DEFINE_SWIZZLE_4(ywzw, 1,3,2,3);
        DEFINE_SWIZZLE_4(ywwx, 1,3,3,0);
        DEFINE_SWIZZLE_4(ywwy, 1,3,3,1);
        DEFINE_SWIZZLE_4(ywwz, 1,3,3,2);
        DEFINE_SWIZZLE_4(ywww, 1,3,3,3);
        DEFINE_SWIZZLE_4(zxxx, 2,0,0,0);
        DEFINE_SWIZZLE_4(zxxy, 2,0,0,1);
        DEFINE_SWIZZLE_4(zxxz, 2,0,0,2);
        DEFINE_SWIZZLE_4(zxxw, 2,0,0,3);
        DEFINE_SWIZZLE_4(zxyx, 2,0,1,0);
        DEFINE_SWIZZLE_4(zxyy, 2,0,1,1);
        DEFINE_SWIZZLE_4(zxyz, 2,0,1,2);
        DEFINE_SWIZZLE_4(zxyw, 2,0,1,3);
        DEFINE_SWIZZLE_4(zxzx, 2,0,2,0);
        DEFINE_SWIZZLE_4(zxzy, 2,0,2,1);
        DEFINE_SWIZZLE_4(zxzz, 2,0,2,2);
        DEFINE_SWIZZLE_4(zxzw, 2,0,2,3);
        DEFINE_SWIZZLE_4(zxwx, 2,0,3,0);
        DEFINE_SWIZZLE_4(zxwy, 2,0,3,1);
        DEFINE_SWIZZLE_4(zxwz, 2,0,3,2);
        DEFINE_SWIZZLE_4(zxww, 2,0,3,3);
        DEFINE_SWIZZLE_4(zyxx, 2,1,0,0);
        DEFINE_SWIZZLE_4(zyxy, 2,1,0,1);
        DEFINE_SWIZZLE_4(zyxz, 2,1,0,2);
        DEFINE_SWIZZLE_4(zyxw, 2,1,0,3);
        DEFINE_SWIZZLE_4(zyyx, 2,1,1,0);
        DEFINE_SWIZZLE_4(zyyy, 2,1,1,1);
        DEFINE_SWIZZLE_4(zyyz, 2,1,1,2);
        DEFINE_SWIZZLE_4(zyyw, 2,1,1,3);
        DEFINE_SWIZZLE_4(zyzx, 2,1,2,0);
        DEFINE_SWIZZLE_4(zyzy, 2,1,2,1);
        DEFINE_SWIZZLE_4(zyzz, 2,1,2,2);
        DEFINE_SWIZZLE_4(zyzw, 2,1,2,3);
        DEFINE_SWIZZLE_4(zywx, 2,1,3,0);
        DEFINE_SWIZZLE_4(zywy, 2,1,3,1);
        DEFINE_SWIZZLE_4(zywz, 2,1,3,2);
        DEFINE_SWIZZLE_4(zyww, 2,1,3,3);
        DEFINE_SWIZZLE_4(zzxx, 2,2,0,0);
        DEFINE_SWIZZLE_4(zzxy, 2,2,0,1);
        DEFINE_SWIZZLE_4(zzxz, 2,2,0,2);
        DEFINE_SWIZZLE_4(zzxw, 2,2,0,3);
        DEFINE_SWIZZLE_4(zzyx, 2,2,1,0);
        DEFINE_SWIZZLE_4(zzyy, 2,2,1,1);
        DEFINE_SWIZZLE_4(zzyz, 2,2,1,2);
        DEFINE_SWIZZLE_4(zzyw, 2,2,1,3);
        DEFINE_SWIZZLE_4(zzzx, 2,2,2,0);
        DEFINE_SWIZZLE_4(zzzy, 2,2,2,1);
        DEFINE_SWIZZLE_4(zzzz, 2,2,2,2);
        DEFINE_SWIZZLE_4(zzzw, 2,2,2,3);
        DEFINE_SWIZZLE_4(zzwx, 2,2,3,0);
        DEFINE_SWIZZLE_4(zzwy, 2,2,3,1);
        DEFINE_SWIZZLE_4(zzwz, 2,2,3,2);
        DEFINE_SWIZZLE_4(zzww, 2,2,3,3);
        DEFINE_SWIZZLE_4(zwxx, 2,3,0,0);
        DEFINE_SWIZZLE_4(zwxy, 2,3,0,1);
        DEFINE_SWIZZLE_4(zwxz, 2,3,0,2);
        DEFINE_SWIZZLE_4(zwxw, 2,3,0,3);
        DEFINE_SWIZZLE_4(zwyx, 2,3,1,0);
        DEFINE_SWIZZLE_4(zwyy, 2,3,1,1);
        DEFINE_SWIZZLE_4(zwyz, 2,3,1,2);
        DEFINE_SWIZZLE_4(zwyw, 2,3,1,3);
        DEFINE_SWIZZLE_4(zwzx, 2,3,2,0);
        DEFINE_SWIZZLE_4(zwzy, 2,3,2,1);
        DEFINE_SWIZZLE_4(zwzz, 2,3,2,2);
        DEFINE_SWIZZLE_4(zwzw, 2,3,2,3);
        DEFINE_SWIZZLE_4(zwwx, 2,3,3,0);
        DEFINE_SWIZZLE_4(zwwy, 2,3,3,1);
        DEFINE_SWIZZLE_4(zwwz, 2,3,3,2);
        DEFINE_SWIZZLE_4(zwww, 2,3,3,3);
        DEFINE_SWIZZLE_4(wxxx, 3,0,0,0);
        DEFINE_SWIZZLE_4(wxxy, 3,0,0,1);
        DEFINE_SWIZZLE_4(wxxz, 3,0,0,2);
        DEFINE_SWIZZLE_4(wxxw, 3,0,0,3);
        DEFINE_SWIZZLE_4(wxyx, 3,0,1,0);
        DEFINE_SWIZZLE_4(wxyy, 3,0,1,1);
        DEFINE_SWIZZLE_4(wxyz, 3,0,1,2);
        DEFINE_SWIZZLE_4(wxyw, 3,0,1,3);
        DEFINE_SWIZZLE_4(wxzx, 3,0,2,0);
        DEFINE_SWIZZLE_4(wxzy, 3,0,2,1);
        DEFINE_SWIZZLE_4(wxzz, 3,0,2,2);
        DEFINE_SWIZZLE_4(wxzw, 3,0,2,3);
        DEFINE_SWIZZLE_4(wxwx, 3,0,3,0);
        DEFINE_SWIZZLE_4(wxwy, 3,0,3,1);
        DEFINE_SWIZZLE_4(wxwz, 3,0,3,2);
        DEFINE_SWIZZLE_4(wxww, 3,0,3,3);
        DEFINE_SWIZZLE_4(wyxx, 3,1,0,0);
        DEFINE_SWIZZLE_4(wyxy, 3,1,0,1);
        DEFINE_SWIZZLE_4(wyxz, 3,1,0,2);
        DEFINE_SWIZZLE_4(wyxw, 3,1,0,3);
        DEFINE_SWIZZLE_4(wyyx, 3,1,1,0);
        DEFINE_SWIZZLE_4(wyyy, 3,1,1,1);
        DEFINE_SWIZZLE_4(wyyz, 3,1,1,2);
        DEFINE_SWIZZLE_4(wyyw, 3,1,1,3);
        DEFINE_SWIZZLE_4(wyzx, 3,1,2,0);
        DEFINE_SWIZZLE_4(wyzy, 3,1,2,1);
        DEFINE_SWIZZLE_4(wyzz, 3,1,2,2);
        DEFINE_SWIZZLE_4(wyzw, 3,1,2,3);
        DEFINE_SWIZZLE_4(wywx, 3,1,3,0);
        DEFINE_SWIZZLE_4(wywy, 3,1,3,1);
        DEFINE_SWIZZLE_4(wywz, 3,1,3,2);
        DEFINE_SWIZZLE_4(wyww, 3,1,3,3);
        DEFINE_SWIZZLE_4(wzxx, 3,2,0,0);
        DEFINE_SWIZZLE_4(wzxy, 3,2,0,1);
        DEFINE_SWIZZLE_4(wzxz, 3,2,0,2);
        DEFINE_SWIZZLE_4(wzxw, 3,2,0,3);
        DEFINE_SWIZZLE_4(wzyx, 3,2,1,0);
        DEFINE_SWIZZLE_4(wzyy, 3,2,1,1);
        DEFINE_SWIZZLE_4(wzyz, 3,2,1,2);
        DEFINE_SWIZZLE_4(wzyw, 3,2,1,3);
        DEFINE_SWIZZLE_4(wzzx, 3,2,2,0);
        DEFINE_SWIZZLE_4(wzzy, 3,2,2,1);
        DEFINE_SWIZZLE_4(wzzz, 3,2,2,2);
        DEFINE_SWIZZLE_4(wzzw, 3,2,2,3);
        DEFINE_SWIZZLE_4(wzwx, 3,2,3,0);
        DEFINE_SWIZZLE_4(wzwy, 3,2,3,1);
        DEFINE_SWIZZLE_4(wzwz, 3,2,3,2);
        DEFINE_SWIZZLE_4(wzww, 3,2,3,3);
        DEFINE_SWIZZLE_4(wwxx, 3,3,0,0);
        DEFINE_SWIZZLE_4(wwxy, 3,3,0,1);
        DEFINE_SWIZZLE_4(wwxz, 3,3,0,2);
        DEFINE_SWIZZLE_4(wwxw, 3,3,0,3);
        DEFINE_SWIZZLE_4(wwyx, 3,3,1,0);
        DEFINE_SWIZZLE_4(wwyy, 3,3,1,1);
        DEFINE_SWIZZLE_4(wwyz, 3,3,1,2);
        DEFINE_SWIZZLE_4(wwyw, 3,3,1,3);
        DEFINE_SWIZZLE_4(wwzx, 3,3,2,0);
        DEFINE_SWIZZLE_4(wwzy, 3,3,2,1);
        DEFINE_SWIZZLE_4(wwzz, 3,3,2,2);
        DEFINE_SWIZZLE_4(wwzw, 3,3,2,3);
        DEFINE_SWIZZLE_4(wwwx, 3,3,3,0);
        DEFINE_SWIZZLE_4(wwwy, 3,3,3,1);
        DEFINE_SWIZZLE_4(wwwz, 3,3,3,2);
        DEFINE_SWIZZLE_4(wwww, 3,3,3,3);
    };

    template<typename T, size_t Cols, size_t Rows>
    struct mat_t {
        using Self = mat_t;

        vec_t<T, Rows> __columns[Cols];

        constexpr auto col(this Self const& self, size_t i) -> vec_t<T, Rows> {
            return mat_impl<T, Cols, Rows>::col(self, i);
        }
        constexpr auto row(this Self const& self, size_t i) -> vec_t<T, Cols> {
            return mat_impl<T, Cols, Rows>::row(self, i);
        }
        friend constexpr auto operator*(Self const& $1, Self const& $2) -> Self {
            return mat_impl<T, Cols, Rows>::mul($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, vec_t<T, Cols> const& $2) -> vec_t<T, Cols> {
            return mat_impl<T, Cols, Rows>::mul($1, $2);
        }
        friend constexpr auto operator*(vec_t<T, Cols> const& $1, Self const& $2) -> vec_t<T, Cols> {
            return mat_impl<T, Cols, Rows>::mul($1, $2);
        }
    };

    template<size_t Len, typename T, size_t... I>
    struct vec_impl<T, Len, std::index_sequence<I...>> {
        using Self = vec_t<T, Len>;

        inline static constexpr auto add(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] + $2[I]) ... };
        }
        inline static constexpr auto sub(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] - $2[I]) ... };
        }
        inline static constexpr auto mul(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] * $2[I]) ... };
        }
        inline static constexpr auto div(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] / $2[I]) ... };
        }
        inline static constexpr auto mod(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] % $2[I]) ... };
        }
        inline static constexpr auto shl(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] << $2[I]) ... };
        }
        inline static constexpr auto shr(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] >> $2[I]) ... };
        }
        inline static constexpr auto band(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] & $2[I]) ... };
        }
        inline static constexpr auto bor(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] | $2[I]) ... };
        }
        inline static constexpr auto bxor(Self const& $1, Self const& $2) -> Self {
            return { ($1[I] ^ $2[I]) ... };
        }
        inline static constexpr auto add(Self const& $1, T const& $2) -> Self {
            return { ($1[I] + $2) ... };
        }
        inline static constexpr auto sub(Self const& $1, T const& $2) -> Self {
            return { ($1[I] - $2) ... };
        }
        inline static constexpr auto mul(Self const& $1, T const& $2) -> Self {
            return { ($1[I] * $2) ... };
        }
        inline static constexpr auto div(Self const& $1, T const& $2) -> Self {
            return { ($1[I] / $2) ... };
        }
        inline static constexpr auto mod(Self const& $1, T const& $2) -> Self {
            return { ($1[I] % $2) ... };
        }
        inline static constexpr auto shl(Self const& $1, T const& $2) -> Self {
            return { ($1[I] << $2) ... };
        }
        inline static constexpr auto shr(Self const& $1, T const& $2) -> Self {
            return { ($1[I] >> $2) ... };
        }
        inline static constexpr auto band(Self const& $1, T const& $2) -> Self {
            return { ($1[I] & $2) ... };
        }
        inline static constexpr auto bor(Self const& $1, T const& $2) -> Self {
            return { ($1[I] | $2) ... };
        }
        inline static constexpr auto bxor(Self const& $1, T const& $2) -> Self {
            return { ($1[I] ^ $2) ... };
        }
        inline static constexpr auto add(T const& $1, Self const& $2) -> Self {
            return { ($1 + $2[I]) ... };
        }
        inline static constexpr auto sub(T const& $1, Self const& $2) -> Self {
            return { ($1 - $2[I]) ... };
        }
        inline static constexpr auto mul(T const& $1, Self const& $2) -> Self {
            return { ($1 * $2[I]) ... };
        }
        inline static constexpr auto div(T const& $1, Self const& $2) -> Self {
            return { ($1 / $2[I]) ... };
        }
        inline static constexpr auto mod(T const& $1, Self const& $2) -> Self {
            return { ($1 % $2[I]) ... };
        }
        inline static constexpr auto shl(T const& $1, Self const& $2) -> Self {
            return { ($1 << $2[I]) ... };
        }
        inline static constexpr auto shr(T const& $1, Self const& $2) -> Self {
            return { ($1 >> $2[I]) ... };
        }
        inline static constexpr auto band(T const& $1, Self const& $2) -> Self {
            return { ($1 & $2[I]) ... };
        }
        inline static constexpr auto bor(T const& $1, Self const& $2) -> Self {
            return { ($1 | $2[I]) ... };
        }
        inline static constexpr auto bxor(T const& $1, Self const& $2) -> Self {
            return { ($1 ^ $2[I]) ... };
        }
        inline static constexpr auto dot(Self const& $1, Self const& $2) -> T {
            return (($1[I] * $2[I]) + ...);
        }
        inline static constexpr auto csum(Self const& $1) -> T {
            return ($1[I] + ...);
        }

        template<typename U>
        inline static constexpr auto cast(Self const& self) -> vec_t<U, Len> {
            return {static_cast<U>(self[I])...};
        }
        inline static constexpr auto floor(Self const& self) -> Self {
            return {std::floor(self[I])...};
        }
        inline static constexpr auto ceil(Self const& self) -> Self {
            return {std::ceil(self[I])...};
        }
        inline static constexpr auto round(Self const& self) -> Self {
            return {std::round(self[I])...};
        }
        inline static constexpr auto abs(Self const& $1) -> Self {
            return {std::abs($1[I])...};
        }
        inline static constexpr auto min(Self const& $1, Self const& $2) -> Self {
            return {($1[I] < $2[I] ? $1[I] : $2[I])...};
        }
        inline static constexpr auto max(Self const& $1, Self const& $2) -> Self {
            return {($1[I] > $2[I] ? $1[I] : $2[I])...};
        }
    };

    template<typename T, size_t Cols, size_t Rows, size_t... Ci, size_t... Ri>
    struct mat_impl<T, Cols, Rows, std::index_sequence<Ci...>, std::index_sequence<Ri...>> {
        using Self = mat_t<T, Cols, Rows>;

        inline static constexpr auto col(Self const& self, size_t i) -> vec_t<T, Rows> {
            return self.__columns[i];
        }
        inline static constexpr auto row(Self const& self, size_t i) -> vec_t<T, Cols> {
            return {self.__columns[Ci][i]...};
        }
        inline static constexpr auto mul(Self const& $1, Self const& $2) -> Self {
            return { $1 * $2.__columns[Ci]... };
        }
        inline static constexpr auto mul(Self const& $1, vec_t<T, Cols> const& $2) -> vec_t<T, Cols> {
            return (($1.__columns[Ci] * $2[Ci]) + ...);
        }
        inline static constexpr auto mul(vec_t<T, Cols> const& $1, Self const& $2) -> vec_t<T, Cols> {
            return (($1[Ci] * $2.row(Ri)) + ...);
        }
    };

    template<size_t Len, typename T>
    inline static constexpr auto dot(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> T {
        return vec_impl<T, Len>::dot($1, $2);
    }
    template<size_t Len, typename T>
    inline static constexpr auto csum(vec_t<T, Len> const& $1) -> T {
        return vec_impl<T, Len>::csum($1);
    }
    template<typename U, size_t Len, typename T>
    inline static constexpr auto cast(vec_t<T, Len> const& $1) -> vec_t<U, Len> {
        return vec_impl<T, Len>::template cast<U>($1);
    }
    template<size_t Len, std::floating_point T>
    inline static constexpr auto floor(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::floor($1);
    }
    template<size_t Len, std::floating_point T>
    inline static constexpr auto ceil(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::ceil($1);
    }
    template<size_t Len, std::floating_point T>
    inline static constexpr auto round(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::round($1);
    }
    template<size_t Len, typename T>
    inline static constexpr auto abs(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::abs($1);
    }
    template<size_t Len, typename T>
    inline static constexpr auto min(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> vec_t<T, Len> {
        return vec_impl<T, Len>::min($1, $2);
    }
    template<size_t Len, typename T>
    inline static constexpr auto max(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> vec_t<T, Len> {
        return vec_impl<T, Len>::max($1, $2);
    }

    template<typename T>
    inline static constexpr auto mat2x2(mat_t<T, 3, 3> const& $1) -> mat_t<T, 2, 2> {
        return {
            $1.__columns[0].xy,
            $1.__columns[1].xy,
        };
    }

    template<typename T>
    inline static constexpr auto mat3x3(mat_t<T, 4, 4> const& $1) -> mat_t<T, 3, 3> {
        return {
            $1.__columns[0].xyz,
            $1.__columns[1].xyz,
            $1.__columns[2].xyz,
        };
    }

    template<std::floating_point T>
    inline static constexpr auto inverse(mat_t<T, 4, 4> const& $1) -> mat_t<T, 4, 4> {
        vec_t<T, 4> A = $1.row(0);
        vec_t<T, 4> B = $1.row(1);
        vec_t<T, 4> C = $1.row(2);
        vec_t<T, 4> D = $1.row(3);

        vec_t<T, 4> C2211 = C.zzyy;
        vec_t<T, 4> B2211 = B.zzyy;
        vec_t<T, 4> A2211 = A.zzyy;
        vec_t<T, 4> D3332 = D.wwwz;
        vec_t<T, 4> C3332 = C.wwwz;
        vec_t<T, 4> B3332 = B.wwwz;
        vec_t<T, 4> D2211 = D.zzyy;
        vec_t<T, 4> A3332 = A.wwwz;
        vec_t<T, 4> B1000 = B.yxxx;
        vec_t<T, 4> A1000 = A.yxxx;
        vec_t<T, 4> C1000 = C.yxxx;
        vec_t<T, 4> D1000 = D.yxxx;

        vec_t<T, 4> $00 = C2211 * D3332 - D2211 * C3332;
        vec_t<T, 4> $01 = B2211 * D3332 - D2211 * B3332;
        vec_t<T, 4> $02 = B2211 * C3332 - C2211 * B3332;
        vec_t<T, 4> $03 = A2211 * D3332 - D2211 * A3332;
        vec_t<T, 4> $04 = A2211 * C3332 - C2211 * A3332;
        vec_t<T, 4> $05 = A2211 * B3332 - B2211 * A3332;

        vec_t<T, 4> m00 = (B1000 * $00 - C1000 * $01 + D1000 * $02) * vec_t<T, 4>{+1, -1, +1, -1};
        vec_t<T, 4> m01 = (A1000 * $00 - C1000 * $03 + D1000 * $04) * vec_t<T, 4>{-1, +1, -1, +1};
        vec_t<T, 4> m02 = (A1000 * $01 - B1000 * $03 + D1000 * $05) * vec_t<T, 4>{+1, -1, +1, -1};
        vec_t<T, 4> m03 = (A1000 * $02 - B1000 * $04 + C1000 * $05) * vec_t<T, 4>{-1, +1, -1, +1};

        T det = dot(A, m00);
        return {
            m00 / det,
            m01 / det,
            m02 / det,
            m03 / det
        };
    }

    using i8vec2 = math::vec_t<int8_t, 2>;
    using i8vec3 = math::vec_t<int8_t, 3>;
    using i8vec4 = math::vec_t<int8_t, 4>;
    using i16vec2 = math::vec_t<int16_t, 2>;
    using i16vec3 = math::vec_t<int16_t, 3>;
    using i16vec4 = math::vec_t<int16_t, 4>;
    using i32vec2 = math::vec_t<int32_t, 2>;
    using i32vec3 = math::vec_t<int32_t, 3>;
    using i32vec4 = math::vec_t<int32_t, 4>;
    using i64vec2 = math::vec_t<int64_t, 2>;
    using i64vec3 = math::vec_t<int64_t, 3>;
    using i64vec4 = math::vec_t<int64_t, 4>;

    using u8vec2 = math::vec_t<uint8_t, 2>;
    using u8vec3 = math::vec_t<uint8_t, 3>;
    using u8vec4 = math::vec_t<uint8_t, 4>;
    using u16vec2 = math::vec_t<uint16_t, 2>;
    using u16vec3 = math::vec_t<uint16_t, 3>;
    using u16vec4 = math::vec_t<uint16_t, 4>;
    using u32vec2 = math::vec_t<uint32_t, 2>;
    using u32vec3 = math::vec_t<uint32_t, 3>;
    using u32vec4 = math::vec_t<uint32_t, 4>;
    using u64vec2 = math::vec_t<uint64_t, 2>;
    using u64vec3 = math::vec_t<uint64_t, 3>;
    using u64vec4 = math::vec_t<uint64_t, 4>;

    using f32vec2 = math::vec_t<float_t, 2>;
    using f32vec3 = math::vec_t<float_t, 3>;
    using f32vec4 = math::vec_t<float_t, 4>;
    using f64vec2 = math::vec_t<double_t, 2>;
    using f64vec3 = math::vec_t<double_t, 3>;
    using f64vec4 = math::vec_t<double_t, 4>;

    using f32mat2x2 = math::mat_t<float_t, 2, 2>;
    using f32mat3x3 = math::mat_t<float_t, 3, 3>;
    using f32mat4x4 = math::mat_t<float_t, 4, 4>;

    using f64mat2x2 = math::mat_t<double_t, 2, 2>;
    using f64mat3x3 = math::mat_t<double_t, 3, 3>;
    using f64mat4x4 = math::mat_t<double_t, 4, 4>;
}

#undef DEFINE_COMPONENT
#undef DEFINE_SWIZZLE_2
#undef DEFINE_SWIZZLE_3
#undef DEFINE_SWIZZLE_4