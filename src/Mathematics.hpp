//
// Created by Maksym Pasichnyk on 01.06.2024.
//
#pragma once

#include <cmath>
#include <utility>

#define DEFINE_COMPONENT(name, component)                                       \
    __declspec(property(                                                        \
        get = __##name##__,                                                     \
        put = __##name##__                                                      \
    )) struct {} name;                                                          \
    template<typename Self> requires(component < N)                             \
    constexpr auto __##name##__(this Self const& self) -> T {                   \
        return self.__fields[component];                                        \
    }                                                                           \
    template<typename U> requires(component < N)                                \
    constexpr void __##name##__(this Self& self, U&& u) {                       \
        self.__fields[component] = static_cast<U&&>(u);                         \
    }

#define DEFINE_RO_SWIZZLE(name, ...)                            \
    __declspec(property(get = __##name##__)) struct {} name;    \
    constexpr auto __##name##__(this Self const& self) {        \
        return swizzle<__VA_ARGS__>(self);                      \
    }

namespace math {
    template<typename T, typename U>
    using forward_like_t = std::conditional_t<
        std::is_rvalue_reference_v<T>,
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

    template<size_t N, typename T, typename = std::make_index_sequence<N>>
    struct vec_impl;

    template<size_t C, size_t R, typename T, typename = std::make_index_sequence<C>, typename = std::make_index_sequence<R>>
    struct mat_impl;

    template<size_t N, typename T>
    struct vec_t {
        using Self = vec_t;

        T __fields[N];

        friend constexpr auto operator<=>(Self const& $1, Self const& $2) = default;

        template<typename Self>
        constexpr auto operator[](this Self&& self, size_t i) -> forward_like_t<Self, T> {
            return static_cast<forward_like_t<Self, T>>(self.__fields[i]);
        }

        friend constexpr auto operator+(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::add($1, $2);
        }
        friend constexpr auto operator-(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::sub($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::mul($1, $2);
        }
        friend constexpr auto operator/(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::div($1, $2);
        }
        friend constexpr auto operator%(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::mod($1, $2);
        }
        friend constexpr auto operator<<(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::shl($1, $2);
        }
        friend constexpr auto operator>>(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::shr($1, $2);
        }
        friend constexpr auto operator&(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::band($1, $2);
        }
        friend constexpr auto operator|(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::bor($1, $2);
        }
        friend constexpr auto operator^(Self const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::bxor($1, $2);
        }
        friend constexpr auto operator+(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::add($1, $2);
        }
        friend constexpr auto operator-(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::sub($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::mul($1, $2);
        }
        friend constexpr auto operator/(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::div($1, $2);
        }
        friend constexpr auto operator%(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::mod($1, $2);
        }
        friend constexpr auto operator<<(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::shl($1, $2);
        }
        friend constexpr auto operator>>(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::shr($1, $2);
        }
        friend constexpr auto operator&(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::band($1, $2);
        }
        friend constexpr auto operator|(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::bor($1, $2);
        }
        friend constexpr auto operator^(Self const& $1, T const& $2) -> Self {
            return vec_impl<N, T>::bxor($1, $2);
        }
        friend constexpr auto operator+(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::add($1, $2);
        }
        friend constexpr auto operator-(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::sub($1, $2);
        }
        friend constexpr auto operator*(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::mul($1, $2);
        }
        friend constexpr auto operator/(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::div($1, $2);
        }
        friend constexpr auto operator%(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::mod($1, $2);
        }
        friend constexpr auto operator<<(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::shl($1, $2);
        }
        friend constexpr auto operator>>(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::shr($1, $2);
        }
        friend constexpr auto operator&(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::band($1, $2);
        }
        friend constexpr auto operator|(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::bor($1, $2);
        }
        friend constexpr auto operator^(T const& $1, Self const& $2) -> Self {
            return vec_impl<N, T>::bxor($1, $2);
        }

        DEFINE_COMPONENT(x, 0);
        DEFINE_COMPONENT(y, 1);
        DEFINE_COMPONENT(z, 2);
        DEFINE_COMPONENT(w, 3);
        DEFINE_RO_SWIZZLE(xx, 0,0);
        DEFINE_RO_SWIZZLE(xy, 0,1);
        DEFINE_RO_SWIZZLE(xz, 0,2);
        DEFINE_RO_SWIZZLE(xw, 0,3);
        DEFINE_RO_SWIZZLE(yx, 1,0);
        DEFINE_RO_SWIZZLE(yy, 1,1);
        DEFINE_RO_SWIZZLE(yz, 1,2);
        DEFINE_RO_SWIZZLE(yw, 1,3);
        DEFINE_RO_SWIZZLE(zx, 2,0);
        DEFINE_RO_SWIZZLE(zy, 2,1);
        DEFINE_RO_SWIZZLE(zz, 2,2);
        DEFINE_RO_SWIZZLE(zw, 2,3);
        DEFINE_RO_SWIZZLE(wx, 3,0);
        DEFINE_RO_SWIZZLE(wy, 3,1);
        DEFINE_RO_SWIZZLE(wz, 3,2);
        DEFINE_RO_SWIZZLE(ww, 3,3);
        DEFINE_RO_SWIZZLE(xxx, 0,0,0);
        DEFINE_RO_SWIZZLE(xxy, 0,0,1);
        DEFINE_RO_SWIZZLE(xxz, 0,0,2);
        DEFINE_RO_SWIZZLE(xxw, 0,0,3);
        DEFINE_RO_SWIZZLE(xyx, 0,1,0);
        DEFINE_RO_SWIZZLE(xyy, 0,1,1);
        DEFINE_RO_SWIZZLE(xyz, 0,1,2);
        DEFINE_RO_SWIZZLE(xyw, 0,1,3);
        DEFINE_RO_SWIZZLE(xzx, 0,2,0);
        DEFINE_RO_SWIZZLE(xzy, 0,2,1);
        DEFINE_RO_SWIZZLE(xzz, 0,2,2);
        DEFINE_RO_SWIZZLE(xzw, 0,2,3);
        DEFINE_RO_SWIZZLE(xwx, 0,3,0);
        DEFINE_RO_SWIZZLE(xwy, 0,3,1);
        DEFINE_RO_SWIZZLE(xwz, 0,3,2);
        DEFINE_RO_SWIZZLE(xww, 0,3,3);
        DEFINE_RO_SWIZZLE(yxx, 1,0,0);
        DEFINE_RO_SWIZZLE(yxy, 1,0,1);
        DEFINE_RO_SWIZZLE(yxz, 1,0,2);
        DEFINE_RO_SWIZZLE(yxw, 1,0,3);
        DEFINE_RO_SWIZZLE(yyx, 1,1,0);
        DEFINE_RO_SWIZZLE(yyy, 1,1,1);
        DEFINE_RO_SWIZZLE(yyz, 1,1,2);
        DEFINE_RO_SWIZZLE(yyw, 1,1,3);
        DEFINE_RO_SWIZZLE(yzx, 1,2,0);
        DEFINE_RO_SWIZZLE(yzy, 1,2,1);
        DEFINE_RO_SWIZZLE(yzz, 1,2,2);
        DEFINE_RO_SWIZZLE(yzw, 1,2,3);
        DEFINE_RO_SWIZZLE(ywx, 1,3,0);
        DEFINE_RO_SWIZZLE(ywy, 1,3,1);
        DEFINE_RO_SWIZZLE(ywz, 1,3,2);
        DEFINE_RO_SWIZZLE(yww, 1,3,3);
        DEFINE_RO_SWIZZLE(zxx, 2,0,0);
        DEFINE_RO_SWIZZLE(zxy, 2,0,1);
        DEFINE_RO_SWIZZLE(zxz, 2,0,2);
        DEFINE_RO_SWIZZLE(zxw, 2,0,3);
        DEFINE_RO_SWIZZLE(zyx, 2,1,0);
        DEFINE_RO_SWIZZLE(zyy, 2,1,1);
        DEFINE_RO_SWIZZLE(zyz, 2,1,2);
        DEFINE_RO_SWIZZLE(zyw, 2,1,3);
        DEFINE_RO_SWIZZLE(zzx, 2,2,0);
        DEFINE_RO_SWIZZLE(zzy, 2,2,1);
        DEFINE_RO_SWIZZLE(zzz, 2,2,2);
        DEFINE_RO_SWIZZLE(zzw, 2,2,3);
        DEFINE_RO_SWIZZLE(zwx, 2,3,0);
        DEFINE_RO_SWIZZLE(zwy, 2,3,1);
        DEFINE_RO_SWIZZLE(zwz, 2,3,2);
        DEFINE_RO_SWIZZLE(zww, 2,3,3);
        DEFINE_RO_SWIZZLE(wxx, 3,0,0);
        DEFINE_RO_SWIZZLE(wxy, 3,0,1);
        DEFINE_RO_SWIZZLE(wxz, 3,0,2);
        DEFINE_RO_SWIZZLE(wxw, 3,0,3);
        DEFINE_RO_SWIZZLE(wyx, 3,1,0);
        DEFINE_RO_SWIZZLE(wyy, 3,1,1);
        DEFINE_RO_SWIZZLE(wyz, 3,1,2);
        DEFINE_RO_SWIZZLE(wyw, 3,1,3);
        DEFINE_RO_SWIZZLE(wzx, 3,2,0);
        DEFINE_RO_SWIZZLE(wzy, 3,2,1);
        DEFINE_RO_SWIZZLE(wzz, 3,2,2);
        DEFINE_RO_SWIZZLE(wzw, 3,2,3);
        DEFINE_RO_SWIZZLE(wwx, 3,3,0);
        DEFINE_RO_SWIZZLE(wwy, 3,3,1);
        DEFINE_RO_SWIZZLE(wwz, 3,3,2);
        DEFINE_RO_SWIZZLE(www, 3,3,3);
        DEFINE_RO_SWIZZLE(xxxx, 0,0,0,0);
        DEFINE_RO_SWIZZLE(xxxy, 0,0,0,1);
        DEFINE_RO_SWIZZLE(xxxz, 0,0,0,2);
        DEFINE_RO_SWIZZLE(xxxw, 0,0,0,3);
        DEFINE_RO_SWIZZLE(xxyx, 0,0,1,0);
        DEFINE_RO_SWIZZLE(xxyy, 0,0,1,1);
        DEFINE_RO_SWIZZLE(xxyz, 0,0,1,2);
        DEFINE_RO_SWIZZLE(xxyw, 0,0,1,3);
        DEFINE_RO_SWIZZLE(xxzx, 0,0,2,0);
        DEFINE_RO_SWIZZLE(xxzy, 0,0,2,1);
        DEFINE_RO_SWIZZLE(xxzz, 0,0,2,2);
        DEFINE_RO_SWIZZLE(xxzw, 0,0,2,3);
        DEFINE_RO_SWIZZLE(xxwx, 0,0,3,0);
        DEFINE_RO_SWIZZLE(xxwy, 0,0,3,1);
        DEFINE_RO_SWIZZLE(xxwz, 0,0,3,2);
        DEFINE_RO_SWIZZLE(xxww, 0,0,3,3);
        DEFINE_RO_SWIZZLE(xyxx, 0,1,0,0);
        DEFINE_RO_SWIZZLE(xyxy, 0,1,0,1);
        DEFINE_RO_SWIZZLE(xyxz, 0,1,0,2);
        DEFINE_RO_SWIZZLE(xyxw, 0,1,0,3);
        DEFINE_RO_SWIZZLE(xyyx, 0,1,1,0);
        DEFINE_RO_SWIZZLE(xyyy, 0,1,1,1);
        DEFINE_RO_SWIZZLE(xyyz, 0,1,1,2);
        DEFINE_RO_SWIZZLE(xyyw, 0,1,1,3);
        DEFINE_RO_SWIZZLE(xyzx, 0,1,2,0);
        DEFINE_RO_SWIZZLE(xyzy, 0,1,2,1);
        DEFINE_RO_SWIZZLE(xyzz, 0,1,2,2);
        DEFINE_RO_SWIZZLE(xyzw, 0,1,2,3);
        DEFINE_RO_SWIZZLE(xywx, 0,1,3,0);
        DEFINE_RO_SWIZZLE(xywy, 0,1,3,1);
        DEFINE_RO_SWIZZLE(xywz, 0,1,3,2);
        DEFINE_RO_SWIZZLE(xyww, 0,1,3,3);
        DEFINE_RO_SWIZZLE(xzxx, 0,2,0,0);
        DEFINE_RO_SWIZZLE(xzxy, 0,2,0,1);
        DEFINE_RO_SWIZZLE(xzxz, 0,2,0,2);
        DEFINE_RO_SWIZZLE(xzxw, 0,2,0,3);
        DEFINE_RO_SWIZZLE(xzyx, 0,2,1,0);
        DEFINE_RO_SWIZZLE(xzyy, 0,2,1,1);
        DEFINE_RO_SWIZZLE(xzyz, 0,2,1,2);
        DEFINE_RO_SWIZZLE(xzyw, 0,2,1,3);
        DEFINE_RO_SWIZZLE(xzzx, 0,2,2,0);
        DEFINE_RO_SWIZZLE(xzzy, 0,2,2,1);
        DEFINE_RO_SWIZZLE(xzzz, 0,2,2,2);
        DEFINE_RO_SWIZZLE(xzzw, 0,2,2,3);
        DEFINE_RO_SWIZZLE(xzwx, 0,2,3,0);
        DEFINE_RO_SWIZZLE(xzwy, 0,2,3,1);
        DEFINE_RO_SWIZZLE(xzwz, 0,2,3,2);
        DEFINE_RO_SWIZZLE(xzww, 0,2,3,3);
        DEFINE_RO_SWIZZLE(xwxx, 0,3,0,0);
        DEFINE_RO_SWIZZLE(xwxy, 0,3,0,1);
        DEFINE_RO_SWIZZLE(xwxz, 0,3,0,2);
        DEFINE_RO_SWIZZLE(xwxw, 0,3,0,3);
        DEFINE_RO_SWIZZLE(xwyx, 0,3,1,0);
        DEFINE_RO_SWIZZLE(xwyy, 0,3,1,1);
        DEFINE_RO_SWIZZLE(xwyz, 0,3,1,2);
        DEFINE_RO_SWIZZLE(xwyw, 0,3,1,3);
        DEFINE_RO_SWIZZLE(xwzx, 0,3,2,0);
        DEFINE_RO_SWIZZLE(xwzy, 0,3,2,1);
        DEFINE_RO_SWIZZLE(xwzz, 0,3,2,2);
        DEFINE_RO_SWIZZLE(xwzw, 0,3,2,3);
        DEFINE_RO_SWIZZLE(xwwx, 0,3,3,0);
        DEFINE_RO_SWIZZLE(xwwy, 0,3,3,1);
        DEFINE_RO_SWIZZLE(xwwz, 0,3,3,2);
        DEFINE_RO_SWIZZLE(xwww, 0,3,3,3);
        DEFINE_RO_SWIZZLE(yxxx, 1,0,0,0);
        DEFINE_RO_SWIZZLE(yxxy, 1,0,0,1);
        DEFINE_RO_SWIZZLE(yxxz, 1,0,0,2);
        DEFINE_RO_SWIZZLE(yxxw, 1,0,0,3);
        DEFINE_RO_SWIZZLE(yxyx, 1,0,1,0);
        DEFINE_RO_SWIZZLE(yxyy, 1,0,1,1);
        DEFINE_RO_SWIZZLE(yxyz, 1,0,1,2);
        DEFINE_RO_SWIZZLE(yxyw, 1,0,1,3);
        DEFINE_RO_SWIZZLE(yxzx, 1,0,2,0);
        DEFINE_RO_SWIZZLE(yxzy, 1,0,2,1);
        DEFINE_RO_SWIZZLE(yxzz, 1,0,2,2);
        DEFINE_RO_SWIZZLE(yxzw, 1,0,2,3);
        DEFINE_RO_SWIZZLE(yxwx, 1,0,3,0);
        DEFINE_RO_SWIZZLE(yxwy, 1,0,3,1);
        DEFINE_RO_SWIZZLE(yxwz, 1,0,3,2);
        DEFINE_RO_SWIZZLE(yxww, 1,0,3,3);
        DEFINE_RO_SWIZZLE(yyxx, 1,1,0,0);
        DEFINE_RO_SWIZZLE(yyxy, 1,1,0,1);
        DEFINE_RO_SWIZZLE(yyxz, 1,1,0,2);
        DEFINE_RO_SWIZZLE(yyxw, 1,1,0,3);
        DEFINE_RO_SWIZZLE(yyyx, 1,1,1,0);
        DEFINE_RO_SWIZZLE(yyyy, 1,1,1,1);
        DEFINE_RO_SWIZZLE(yyyz, 1,1,1,2);
        DEFINE_RO_SWIZZLE(yyyw, 1,1,1,3);
        DEFINE_RO_SWIZZLE(yyzx, 1,1,2,0);
        DEFINE_RO_SWIZZLE(yyzy, 1,1,2,1);
        DEFINE_RO_SWIZZLE(yyzz, 1,1,2,2);
        DEFINE_RO_SWIZZLE(yyzw, 1,1,2,3);
        DEFINE_RO_SWIZZLE(yywx, 1,1,3,0);
        DEFINE_RO_SWIZZLE(yywy, 1,1,3,1);
        DEFINE_RO_SWIZZLE(yywz, 1,1,3,2);
        DEFINE_RO_SWIZZLE(yyww, 1,1,3,3);
        DEFINE_RO_SWIZZLE(yzxx, 1,2,0,0);
        DEFINE_RO_SWIZZLE(yzxy, 1,2,0,1);
        DEFINE_RO_SWIZZLE(yzxz, 1,2,0,2);
        DEFINE_RO_SWIZZLE(yzxw, 1,2,0,3);
        DEFINE_RO_SWIZZLE(yzyx, 1,2,1,0);
        DEFINE_RO_SWIZZLE(yzyy, 1,2,1,1);
        DEFINE_RO_SWIZZLE(yzyz, 1,2,1,2);
        DEFINE_RO_SWIZZLE(yzyw, 1,2,1,3);
        DEFINE_RO_SWIZZLE(yzzx, 1,2,2,0);
        DEFINE_RO_SWIZZLE(yzzy, 1,2,2,1);
        DEFINE_RO_SWIZZLE(yzzz, 1,2,2,2);
        DEFINE_RO_SWIZZLE(yzzw, 1,2,2,3);
        DEFINE_RO_SWIZZLE(yzwx, 1,2,3,0);
        DEFINE_RO_SWIZZLE(yzwy, 1,2,3,1);
        DEFINE_RO_SWIZZLE(yzwz, 1,2,3,2);
        DEFINE_RO_SWIZZLE(yzww, 1,2,3,3);
        DEFINE_RO_SWIZZLE(ywxx, 1,3,0,0);
        DEFINE_RO_SWIZZLE(ywxy, 1,3,0,1);
        DEFINE_RO_SWIZZLE(ywxz, 1,3,0,2);
        DEFINE_RO_SWIZZLE(ywxw, 1,3,0,3);
        DEFINE_RO_SWIZZLE(ywyx, 1,3,1,0);
        DEFINE_RO_SWIZZLE(ywyy, 1,3,1,1);
        DEFINE_RO_SWIZZLE(ywyz, 1,3,1,2);
        DEFINE_RO_SWIZZLE(ywyw, 1,3,1,3);
        DEFINE_RO_SWIZZLE(ywzx, 1,3,2,0);
        DEFINE_RO_SWIZZLE(ywzy, 1,3,2,1);
        DEFINE_RO_SWIZZLE(ywzz, 1,3,2,2);
        DEFINE_RO_SWIZZLE(ywzw, 1,3,2,3);
        DEFINE_RO_SWIZZLE(ywwx, 1,3,3,0);
        DEFINE_RO_SWIZZLE(ywwy, 1,3,3,1);
        DEFINE_RO_SWIZZLE(ywwz, 1,3,3,2);
        DEFINE_RO_SWIZZLE(ywww, 1,3,3,3);
        DEFINE_RO_SWIZZLE(zxxx, 2,0,0,0);
        DEFINE_RO_SWIZZLE(zxxy, 2,0,0,1);
        DEFINE_RO_SWIZZLE(zxxz, 2,0,0,2);
        DEFINE_RO_SWIZZLE(zxxw, 2,0,0,3);
        DEFINE_RO_SWIZZLE(zxyx, 2,0,1,0);
        DEFINE_RO_SWIZZLE(zxyy, 2,0,1,1);
        DEFINE_RO_SWIZZLE(zxyz, 2,0,1,2);
        DEFINE_RO_SWIZZLE(zxyw, 2,0,1,3);
        DEFINE_RO_SWIZZLE(zxzx, 2,0,2,0);
        DEFINE_RO_SWIZZLE(zxzy, 2,0,2,1);
        DEFINE_RO_SWIZZLE(zxzz, 2,0,2,2);
        DEFINE_RO_SWIZZLE(zxzw, 2,0,2,3);
        DEFINE_RO_SWIZZLE(zxwx, 2,0,3,0);
        DEFINE_RO_SWIZZLE(zxwy, 2,0,3,1);
        DEFINE_RO_SWIZZLE(zxwz, 2,0,3,2);
        DEFINE_RO_SWIZZLE(zxww, 2,0,3,3);
        DEFINE_RO_SWIZZLE(zyxx, 2,1,0,0);
        DEFINE_RO_SWIZZLE(zyxy, 2,1,0,1);
        DEFINE_RO_SWIZZLE(zyxz, 2,1,0,2);
        DEFINE_RO_SWIZZLE(zyxw, 2,1,0,3);
        DEFINE_RO_SWIZZLE(zyyx, 2,1,1,0);
        DEFINE_RO_SWIZZLE(zyyy, 2,1,1,1);
        DEFINE_RO_SWIZZLE(zyyz, 2,1,1,2);
        DEFINE_RO_SWIZZLE(zyyw, 2,1,1,3);
        DEFINE_RO_SWIZZLE(zyzx, 2,1,2,0);
        DEFINE_RO_SWIZZLE(zyzy, 2,1,2,1);
        DEFINE_RO_SWIZZLE(zyzz, 2,1,2,2);
        DEFINE_RO_SWIZZLE(zyzw, 2,1,2,3);
        DEFINE_RO_SWIZZLE(zywx, 2,1,3,0);
        DEFINE_RO_SWIZZLE(zywy, 2,1,3,1);
        DEFINE_RO_SWIZZLE(zywz, 2,1,3,2);
        DEFINE_RO_SWIZZLE(zyww, 2,1,3,3);
        DEFINE_RO_SWIZZLE(zzxx, 2,2,0,0);
        DEFINE_RO_SWIZZLE(zzxy, 2,2,0,1);
        DEFINE_RO_SWIZZLE(zzxz, 2,2,0,2);
        DEFINE_RO_SWIZZLE(zzxw, 2,2,0,3);
        DEFINE_RO_SWIZZLE(zzyx, 2,2,1,0);
        DEFINE_RO_SWIZZLE(zzyy, 2,2,1,1);
        DEFINE_RO_SWIZZLE(zzyz, 2,2,1,2);
        DEFINE_RO_SWIZZLE(zzyw, 2,2,1,3);
        DEFINE_RO_SWIZZLE(zzzx, 2,2,2,0);
        DEFINE_RO_SWIZZLE(zzzy, 2,2,2,1);
        DEFINE_RO_SWIZZLE(zzzz, 2,2,2,2);
        DEFINE_RO_SWIZZLE(zzzw, 2,2,2,3);
        DEFINE_RO_SWIZZLE(zzwx, 2,2,3,0);
        DEFINE_RO_SWIZZLE(zzwy, 2,2,3,1);
        DEFINE_RO_SWIZZLE(zzwz, 2,2,3,2);
        DEFINE_RO_SWIZZLE(zzww, 2,2,3,3);
        DEFINE_RO_SWIZZLE(zwxx, 2,3,0,0);
        DEFINE_RO_SWIZZLE(zwxy, 2,3,0,1);
        DEFINE_RO_SWIZZLE(zwxz, 2,3,0,2);
        DEFINE_RO_SWIZZLE(zwxw, 2,3,0,3);
        DEFINE_RO_SWIZZLE(zwyx, 2,3,1,0);
        DEFINE_RO_SWIZZLE(zwyy, 2,3,1,1);
        DEFINE_RO_SWIZZLE(zwyz, 2,3,1,2);
        DEFINE_RO_SWIZZLE(zwyw, 2,3,1,3);
        DEFINE_RO_SWIZZLE(zwzx, 2,3,2,0);
        DEFINE_RO_SWIZZLE(zwzy, 2,3,2,1);
        DEFINE_RO_SWIZZLE(zwzz, 2,3,2,2);
        DEFINE_RO_SWIZZLE(zwzw, 2,3,2,3);
        DEFINE_RO_SWIZZLE(zwwx, 2,3,3,0);
        DEFINE_RO_SWIZZLE(zwwy, 2,3,3,1);
        DEFINE_RO_SWIZZLE(zwwz, 2,3,3,2);
        DEFINE_RO_SWIZZLE(zwww, 2,3,3,3);
        DEFINE_RO_SWIZZLE(wxxx, 3,0,0,0);
        DEFINE_RO_SWIZZLE(wxxy, 3,0,0,1);
        DEFINE_RO_SWIZZLE(wxxz, 3,0,0,2);
        DEFINE_RO_SWIZZLE(wxxw, 3,0,0,3);
        DEFINE_RO_SWIZZLE(wxyx, 3,0,1,0);
        DEFINE_RO_SWIZZLE(wxyy, 3,0,1,1);
        DEFINE_RO_SWIZZLE(wxyz, 3,0,1,2);
        DEFINE_RO_SWIZZLE(wxyw, 3,0,1,3);
        DEFINE_RO_SWIZZLE(wxzx, 3,0,2,0);
        DEFINE_RO_SWIZZLE(wxzy, 3,0,2,1);
        DEFINE_RO_SWIZZLE(wxzz, 3,0,2,2);
        DEFINE_RO_SWIZZLE(wxzw, 3,0,2,3);
        DEFINE_RO_SWIZZLE(wxwx, 3,0,3,0);
        DEFINE_RO_SWIZZLE(wxwy, 3,0,3,1);
        DEFINE_RO_SWIZZLE(wxwz, 3,0,3,2);
        DEFINE_RO_SWIZZLE(wxww, 3,0,3,3);
        DEFINE_RO_SWIZZLE(wyxx, 3,1,0,0);
        DEFINE_RO_SWIZZLE(wyxy, 3,1,0,1);
        DEFINE_RO_SWIZZLE(wyxz, 3,1,0,2);
        DEFINE_RO_SWIZZLE(wyxw, 3,1,0,3);
        DEFINE_RO_SWIZZLE(wyyx, 3,1,1,0);
        DEFINE_RO_SWIZZLE(wyyy, 3,1,1,1);
        DEFINE_RO_SWIZZLE(wyyz, 3,1,1,2);
        DEFINE_RO_SWIZZLE(wyyw, 3,1,1,3);
        DEFINE_RO_SWIZZLE(wyzx, 3,1,2,0);
        DEFINE_RO_SWIZZLE(wyzy, 3,1,2,1);
        DEFINE_RO_SWIZZLE(wyzz, 3,1,2,2);
        DEFINE_RO_SWIZZLE(wyzw, 3,1,2,3);
        DEFINE_RO_SWIZZLE(wywx, 3,1,3,0);
        DEFINE_RO_SWIZZLE(wywy, 3,1,3,1);
        DEFINE_RO_SWIZZLE(wywz, 3,1,3,2);
        DEFINE_RO_SWIZZLE(wyww, 3,1,3,3);
        DEFINE_RO_SWIZZLE(wzxx, 3,2,0,0);
        DEFINE_RO_SWIZZLE(wzxy, 3,2,0,1);
        DEFINE_RO_SWIZZLE(wzxz, 3,2,0,2);
        DEFINE_RO_SWIZZLE(wzxw, 3,2,0,3);
        DEFINE_RO_SWIZZLE(wzyx, 3,2,1,0);
        DEFINE_RO_SWIZZLE(wzyy, 3,2,1,1);
        DEFINE_RO_SWIZZLE(wzyz, 3,2,1,2);
        DEFINE_RO_SWIZZLE(wzyw, 3,2,1,3);
        DEFINE_RO_SWIZZLE(wzzx, 3,2,2,0);
        DEFINE_RO_SWIZZLE(wzzy, 3,2,2,1);
        DEFINE_RO_SWIZZLE(wzzz, 3,2,2,2);
        DEFINE_RO_SWIZZLE(wzzw, 3,2,2,3);
        DEFINE_RO_SWIZZLE(wzwx, 3,2,3,0);
        DEFINE_RO_SWIZZLE(wzwy, 3,2,3,1);
        DEFINE_RO_SWIZZLE(wzwz, 3,2,3,2);
        DEFINE_RO_SWIZZLE(wzww, 3,2,3,3);
        DEFINE_RO_SWIZZLE(wwxx, 3,3,0,0);
        DEFINE_RO_SWIZZLE(wwxy, 3,3,0,1);
        DEFINE_RO_SWIZZLE(wwxz, 3,3,0,2);
        DEFINE_RO_SWIZZLE(wwxw, 3,3,0,3);
        DEFINE_RO_SWIZZLE(wwyx, 3,3,1,0);
        DEFINE_RO_SWIZZLE(wwyy, 3,3,1,1);
        DEFINE_RO_SWIZZLE(wwyz, 3,3,1,2);
        DEFINE_RO_SWIZZLE(wwyw, 3,3,1,3);
        DEFINE_RO_SWIZZLE(wwzx, 3,3,2,0);
        DEFINE_RO_SWIZZLE(wwzy, 3,3,2,1);
        DEFINE_RO_SWIZZLE(wwzz, 3,3,2,2);
        DEFINE_RO_SWIZZLE(wwzw, 3,3,2,3);
        DEFINE_RO_SWIZZLE(wwwx, 3,3,3,0);
        DEFINE_RO_SWIZZLE(wwwy, 3,3,3,1);
        DEFINE_RO_SWIZZLE(wwwz, 3,3,3,2);
        DEFINE_RO_SWIZZLE(wwww, 3,3,3,3);
    };

    template<size_t C, size_t R, typename T>
    struct mat_t {
        using Self = mat_t;

        vec_t<R, T> __columns[C];

        constexpr auto col(this Self const& self, size_t i) -> vec_t<R, T> {
            return mat_impl<C, R, T>::col(self, i);
        }
        constexpr auto row(this Self const& self, size_t i) -> vec_t<C, T> {
            return mat_impl<C, R, T>::row(self, i);
        }
        friend constexpr auto operator*(Self const& $1, Self const& $2) -> Self {
            return mat_impl<C, R, T>::mul($1, $2);
        }
        friend constexpr auto operator*(Self const& $1, vec_t<C, T> const& $2) -> vec_t<C, T> {
            return mat_impl<C, R, T>::mul($1, $2);
        }
        friend constexpr auto operator*(vec_t<C, T> const& $1, Self const& $2) -> vec_t<C, T> {
            return mat_impl<C, R, T>::mul($1, $2);
        }
    };

    template<size_t N, typename T, size_t... I>
    struct vec_impl<N, T, std::index_sequence<I...>> {
        using Self = vec_t<N, T>;

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
        inline static constexpr auto cast(Self const& self) -> vec_t<N, U> {
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

    template<size_t C, size_t R, typename T, size_t... Ci, size_t... Ri>
    struct mat_impl<C, R, T, std::index_sequence<Ci...>, std::index_sequence<Ri...>> {
        using Self = mat_t<C, R, T>;

        inline static constexpr auto col(Self const& self, size_t i) -> vec_t<R, T> {
            return self.__columns[i];
        }
        inline static constexpr auto row(Self const& self, size_t i) -> vec_t<C, T> {
            return { self.__columns[Ci][i]... };
        }
        inline static constexpr auto mul(Self const& $1, Self const& $2) -> Self {
            return { $1 * $2.__columns[Ci]... };
        }
        inline static constexpr auto mul(Self const& $1, vec_t<C, T> const& $2) -> vec_t<C, T> {
            return (($1.__columns[Ci] * $2[Ci]) + ...);
        }
        inline static constexpr auto mul(vec_t<C, T> const& $1, Self const& $2) -> vec_t<C, T> {
            return (($1[Ci] * $2.row(Ri)) + ...);
        }
    };

    template<size_t N, typename T>
    inline static constexpr auto dot(vec_t<N, T> const& $1, vec_t<N, T> const& $2) -> T {
        return vec_impl<N, T>::dot($1, $2);
    }
    template<size_t N, typename T>
    inline static constexpr auto csum(vec_t<N, T> const& $1) -> T {
        return vec_impl<N, T>::csum($1);
    }
    template<typename U, size_t N, typename T>
    inline static constexpr auto cast(vec_t<N, T> const& $1) -> vec_t<N, U> {
        return vec_impl<N, T>::template cast<U>($1);
    }
    template<size_t N, std::floating_point T>
    inline static constexpr auto floor(vec_t<N, T> const& $1) -> vec_t<N, T> {
        return vec_impl<N, T>::floor($1);
    }
    template<size_t N, std::floating_point T>
    inline static constexpr auto ceil(vec_t<N, T> const& $1) -> vec_t<N, T> {
        return vec_impl<N, T>::ceil($1);
    }
    template<size_t N, std::floating_point T>
    inline static constexpr auto round(vec_t<N, T> const& $1) -> vec_t<N, T> {
        return vec_impl<N, T>::round($1);
    }
    template<size_t N, typename T>
    inline static constexpr auto abs(vec_t<N, T> const& $1) -> vec_t<N, T> {
        return vec_impl<N, T>::abs($1);
    }
    template<size_t N, typename T>
    inline static constexpr auto min(vec_t<N, T> const& $1, vec_t<N, T> const& $2) -> vec_t<N, T> {
        return vec_impl<N, T>::min($1, $2);
    }
    template<size_t N, typename T>
    inline static constexpr auto max(vec_t<N, T> const& $1, vec_t<N, T> const& $2) -> vec_t<N, T> {
        return vec_impl<N, T>::max($1, $2);
    }
    template<size_t... I, size_t N, typename T> requires ((I < N) && ...)
    inline static constexpr auto swizzle(vec_t<N, T> const& $1) -> vec_t<sizeof...(I), T> {
        return {$1[I]...};
    }

    template<typename T>
    inline static constexpr auto mat2x2(mat_t<3, 3, T> const& $1) -> mat_t<2, 2, T> {
        return {
            swizzle<0, 1>($1.col(0)),
            swizzle<0, 1>($1.col(1))
        };
    }

    template<typename T>
    inline static constexpr auto mat3x3(mat_t<4, 4, T> const& $1) -> mat_t<3, 3, T> {
        return {
            swizzle<0, 1, 2>($1.col(0)),
            swizzle<0, 1, 2>($1.col(1)),
            swizzle<0, 1, 2>($1.col(2)),
        };
    }

    template<std::floating_point T>
    inline static constexpr auto inverse(mat_t<4, 4, T> const& $1) -> mat_t<4, 4, T> {
        vec_t<4, T> A = $1.row(0);
        vec_t<4, T> B = $1.row(1);
        vec_t<4, T> C = $1.row(2);
        vec_t<4, T> D = $1.row(3);

        vec_t<4, T> C2211 = swizzle<2, 2, 1, 1>(C);
        vec_t<4, T> B2211 = swizzle<2, 2, 1, 1>(B);
        vec_t<4, T> A2211 = swizzle<2, 2, 1, 1>(A);
        vec_t<4, T> D3332 = swizzle<3, 3, 3, 2>(D);
        vec_t<4, T> C3332 = swizzle<3, 3, 3, 2>(C);
        vec_t<4, T> B3332 = swizzle<3, 3, 3, 2>(B);
        vec_t<4, T> D2211 = swizzle<2, 2, 1, 1>(D);
        vec_t<4, T> A3332 = swizzle<3, 3, 3, 2>(A);
        vec_t<4, T> B1000 = swizzle<1, 0, 0, 0>(B);
        vec_t<4, T> A1000 = swizzle<1, 0, 0, 0>(A);
        vec_t<4, T> C1000 = swizzle<1, 0, 0, 0>(C);
        vec_t<4, T> D1000 = swizzle<1, 0, 0, 0>(D);

        vec_t<4, T> $00 = C2211 * D3332 - D2211 * C3332;
        vec_t<4, T> $01 = B2211 * D3332 - D2211 * B3332;
        vec_t<4, T> $02 = B2211 * C3332 - C2211 * B3332;
        vec_t<4, T> $03 = A2211 * D3332 - D2211 * A3332;
        vec_t<4, T> $04 = A2211 * C3332 - C2211 * A3332;
        vec_t<4, T> $05 = A2211 * B3332 - B2211 * A3332;

        vec_t<4, T> m00 = (B1000 * $00 - C1000 * $01 + D1000 * $02) * vec_t<4, T>{+1, -1, +1, -1};
        vec_t<4, T> m01 = (A1000 * $00 - C1000 * $03 + D1000 * $04) * vec_t<4, T>{-1, +1, -1, +1};
        vec_t<4, T> m02 = (A1000 * $01 - B1000 * $03 + D1000 * $05) * vec_t<4, T>{+1, -1, +1, -1};
        vec_t<4, T> m03 = (A1000 * $02 - B1000 * $04 + C1000 * $05) * vec_t<4, T>{-1, +1, -1, +1};

        T det = dot(A, m00);
        return {
            m00 / det,
            m01 / det,
            m02 / det,
            m03 / det
        };
    }

    using i8vec2 = math::vec_t<2, int8_t>;
    using i8vec3 = math::vec_t<3, int8_t>;
    using i8vec4 = math::vec_t<4, int8_t>;
    using i16vec2 = math::vec_t<2, int16_t>;
    using i16vec3 = math::vec_t<3, int16_t>;
    using i16vec4 = math::vec_t<4, int16_t>;
    using i32vec2 = math::vec_t<2, int32_t>;
    using i32vec3 = math::vec_t<3, int32_t>;
    using i32vec4 = math::vec_t<4, int32_t>;
    using i64vec2 = math::vec_t<2, int64_t>;
    using i64vec3 = math::vec_t<3, int64_t>;
    using i64vec4 = math::vec_t<4, int64_t>;

    using u8vec2 = math::vec_t<2, uint8_t>;
    using u8vec3 = math::vec_t<3, uint8_t>;
    using u8vec4 = math::vec_t<4, uint8_t>;
    using u16vec2 = math::vec_t<2, uint16_t>;
    using u16vec3 = math::vec_t<3, uint16_t>;
    using u16vec4 = math::vec_t<4, uint16_t>;
    using u32vec2 = math::vec_t<2, uint32_t>;
    using u32vec3 = math::vec_t<3, uint32_t>;
    using u32vec4 = math::vec_t<4, uint32_t>;
    using u64vec2 = math::vec_t<2, uint64_t>;
    using u64vec3 = math::vec_t<3, uint64_t>;
    using u64vec4 = math::vec_t<4, uint64_t>;

    using f32vec2 = math::vec_t<2, float_t>;
    using f32vec3 = math::vec_t<3, float_t>;
    using f32vec4 = math::vec_t<4, float_t>;
    using f64vec2 = math::vec_t<2, double_t>;
    using f64vec3 = math::vec_t<3, double_t>;
    using f64vec4 = math::vec_t<4, double_t>;
}

#undef DEFINE_COMPONENT
#undef DEFINE_RO_SWIZZLE