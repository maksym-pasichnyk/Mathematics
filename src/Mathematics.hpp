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
        return vec_t<T, 2>{                                                 \
            self.__fields[comp1],                                           \
            self.__fields[comp2],                                           \
        };                                                                  \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 2> const& u) {    \
        static_assert(                                                      \
            comp1 != comp2,                                                 \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self.__fields[comp1] = u[0];                                        \
        self.__fields[comp2] = u[1];                                        \
    }
#define DEFINE_SWIZZLE_3(name, comp1, comp2, comp3)                         \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    constexpr auto __##name##__(this Self const& self) -> vec_t<T, 3> {     \
        return vec_t<T, 3>{                                                 \
            self.__fields[comp1],                                           \
            self.__fields[comp2],                                           \
            self.__fields[comp3],                                           \
        };                                                                  \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 3> const& u) {    \
        static_assert(                                                      \
            (comp1 != comp2) && (comp2 != comp3),                           \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self.__fields[comp1] = u[0];                                        \
        self.__fields[comp2] = u[1];                                        \
        self.__fields[comp3] = u[2];                                        \
    }
#define DEFINE_SWIZZLE_4(name, comp1, comp2, comp3, comp4)                  \
    __declspec(property(                                                    \
        get = __##name##__,                                                 \
        put = __##name##__                                                  \
    )) struct {} name;                                                      \
    constexpr auto __##name##__(this Self const& self) -> vec_t<T, 4> {     \
        return vec_t<T, 4>{                                                 \
            self.__fields[comp1],                                           \
            self.__fields[comp2],                                           \
            self.__fields[comp3],                                           \
            self.__fields[comp4],                                           \
        };                                                                  \
    }                                                                       \
    constexpr void __##name##__(this Self& self, vec_t<T, 4> const& u) {    \
        static_assert(                                                      \
            (comp1 != comp2) && (comp2 != comp3) && (comp3 != comp4),       \
            "vector is not assignable (contains duplicate components)"      \
        );                                                                  \
        self.__fields[comp1] = u[0];                                        \
        self.__fields[comp2] = u[1];                                        \
        self.__fields[comp3] = u[2];                                        \
        self.__fields[comp4] = u[3];                                        \
    }

#define DEFINE_PROPERTIES(x, y, z, w)       \
    DEFINE_COMPONENT(x, 0)                  \
    DEFINE_COMPONENT(y, 1)                  \
    DEFINE_COMPONENT(z, 2)                  \
    DEFINE_COMPONENT(w, 3)                  \
    DEFINE_SWIZZLE_2(x##y, 0,1)             \
    DEFINE_SWIZZLE_2(x##z, 0,2)             \
    DEFINE_SWIZZLE_2(x##w, 0,3)             \
    DEFINE_SWIZZLE_2(y##x, 1,0)             \
    DEFINE_SWIZZLE_2(y##y, 1,1)             \
    DEFINE_SWIZZLE_2(y##z, 1,2)             \
    DEFINE_SWIZZLE_2(y##w, 1,3)             \
    DEFINE_SWIZZLE_2(z##x, 2,0)             \
    DEFINE_SWIZZLE_2(z##y, 2,1)             \
    DEFINE_SWIZZLE_2(z##z, 2,2)             \
    DEFINE_SWIZZLE_2(z##w, 2,3)             \
    DEFINE_SWIZZLE_2(w##x, 3,0)             \
    DEFINE_SWIZZLE_2(w##y, 3,1)             \
    DEFINE_SWIZZLE_2(w##z, 3,2)             \
    DEFINE_SWIZZLE_2(w##w, 3,3)             \
    DEFINE_SWIZZLE_3(x##x##x, 0,0,0)        \
    DEFINE_SWIZZLE_3(x##x##y, 0,0,1)        \
    DEFINE_SWIZZLE_3(x##x##z, 0,0,2)        \
    DEFINE_SWIZZLE_3(x##x##w, 0,0,3)        \
    DEFINE_SWIZZLE_3(x##y##x, 0,1,0)        \
    DEFINE_SWIZZLE_3(x##y##y, 0,1,1)        \
    DEFINE_SWIZZLE_3(x##y##z, 0,1,2)        \
    DEFINE_SWIZZLE_3(x##y##w, 0,1,3)        \
    DEFINE_SWIZZLE_3(x##z##x, 0,2,0)        \
    DEFINE_SWIZZLE_3(x##z##y, 0,2,1)        \
    DEFINE_SWIZZLE_3(x##z##z, 0,2,2)        \
    DEFINE_SWIZZLE_3(x##z##w, 0,2,3)        \
    DEFINE_SWIZZLE_3(x##w##x, 0,3,0)        \
    DEFINE_SWIZZLE_3(x##w##y, 0,3,1)        \
    DEFINE_SWIZZLE_3(x##w##z, 0,3,2)        \
    DEFINE_SWIZZLE_3(x##w##w, 0,3,3)        \
    DEFINE_SWIZZLE_3(y##x##x, 1,0,0)        \
    DEFINE_SWIZZLE_3(y##x##y, 1,0,1)        \
    DEFINE_SWIZZLE_3(y##x##z, 1,0,2)        \
    DEFINE_SWIZZLE_3(y##x##w, 1,0,3)        \
    DEFINE_SWIZZLE_3(y##y##x, 1,1,0)        \
    DEFINE_SWIZZLE_3(y##y##y, 1,1,1)        \
    DEFINE_SWIZZLE_3(y##y##z, 1,1,2)        \
    DEFINE_SWIZZLE_3(y##y##w, 1,1,3)        \
    DEFINE_SWIZZLE_3(y##z##x, 1,2,0)        \
    DEFINE_SWIZZLE_3(y##z##y, 1,2,1)        \
    DEFINE_SWIZZLE_3(y##z##z, 1,2,2)        \
    DEFINE_SWIZZLE_3(y##z##w, 1,2,3)        \
    DEFINE_SWIZZLE_3(y##w##x, 1,3,0)        \
    DEFINE_SWIZZLE_3(y##w##y, 1,3,1)        \
    DEFINE_SWIZZLE_3(y##w##z, 1,3,2)        \
    DEFINE_SWIZZLE_3(y##w##w, 1,3,3)        \
    DEFINE_SWIZZLE_3(z##x##x, 2,0,0)        \
    DEFINE_SWIZZLE_3(z##x##y, 2,0,1)        \
    DEFINE_SWIZZLE_3(z##x##z, 2,0,2)        \
    DEFINE_SWIZZLE_3(z##x##w, 2,0,3)        \
    DEFINE_SWIZZLE_3(z##y##x, 2,1,0)        \
    DEFINE_SWIZZLE_3(z##y##y, 2,1,1)        \
    DEFINE_SWIZZLE_3(z##y##z, 2,1,2)        \
    DEFINE_SWIZZLE_3(z##y##w, 2,1,3)        \
    DEFINE_SWIZZLE_3(z##z##x, 2,2,0)        \
    DEFINE_SWIZZLE_3(z##z##y, 2,2,1)        \
    DEFINE_SWIZZLE_3(z##z##z, 2,2,2)        \
    DEFINE_SWIZZLE_3(z##z##w, 2,2,3)        \
    DEFINE_SWIZZLE_3(z##w##x, 2,3,0)        \
    DEFINE_SWIZZLE_3(z##w##y, 2,3,1)        \
    DEFINE_SWIZZLE_3(z##w##z, 2,3,2)        \
    DEFINE_SWIZZLE_3(z##w##w, 2,3,3)        \
    DEFINE_SWIZZLE_3(w##x##x, 3,0,0)        \
    DEFINE_SWIZZLE_3(w##x##y, 3,0,1)        \
    DEFINE_SWIZZLE_3(w##x##z, 3,0,2)        \
    DEFINE_SWIZZLE_3(w##x##w, 3,0,3)        \
    DEFINE_SWIZZLE_3(w##y##x, 3,1,0)        \
    DEFINE_SWIZZLE_3(w##y##y, 3,1,1)        \
    DEFINE_SWIZZLE_3(w##y##z, 3,1,2)        \
    DEFINE_SWIZZLE_3(w##y##w, 3,1,3)        \
    DEFINE_SWIZZLE_3(w##z##x, 3,2,0)        \
    DEFINE_SWIZZLE_3(w##z##y, 3,2,1)        \
    DEFINE_SWIZZLE_3(w##z##z, 3,2,2)        \
    DEFINE_SWIZZLE_3(w##z##w, 3,2,3)        \
    DEFINE_SWIZZLE_3(w##w##x, 3,3,0)        \
    DEFINE_SWIZZLE_3(w##w##y, 3,3,1)        \
    DEFINE_SWIZZLE_3(w##w##z, 3,3,2)        \
    DEFINE_SWIZZLE_3(w##w##w, 3,3,3)        \
    DEFINE_SWIZZLE_4(x##x##x##x, 0,0,0,0)   \
    DEFINE_SWIZZLE_4(x##x##x##y, 0,0,0,1)   \
    DEFINE_SWIZZLE_4(x##x##x##z, 0,0,0,2)   \
    DEFINE_SWIZZLE_4(x##x##x##w, 0,0,0,3)   \
    DEFINE_SWIZZLE_4(x##x##y##x, 0,0,1,0)   \
    DEFINE_SWIZZLE_4(x##x##y##y, 0,0,1,1)   \
    DEFINE_SWIZZLE_4(x##x##y##z, 0,0,1,2)   \
    DEFINE_SWIZZLE_4(x##x##y##w, 0,0,1,3)   \
    DEFINE_SWIZZLE_4(x##x##z##x, 0,0,2,0)   \
    DEFINE_SWIZZLE_4(x##x##z##y, 0,0,2,1)   \
    DEFINE_SWIZZLE_4(x##x##z##z, 0,0,2,2)   \
    DEFINE_SWIZZLE_4(x##x##z##w, 0,0,2,3)   \
    DEFINE_SWIZZLE_4(x##x##w##x, 0,0,3,0)   \
    DEFINE_SWIZZLE_4(x##x##w##y, 0,0,3,1)   \
    DEFINE_SWIZZLE_4(x##x##w##z, 0,0,3,2)   \
    DEFINE_SWIZZLE_4(x##x##w##w, 0,0,3,3)   \
    DEFINE_SWIZZLE_4(x##y##x##x, 0,1,0,0)   \
    DEFINE_SWIZZLE_4(x##y##x##y, 0,1,0,1)   \
    DEFINE_SWIZZLE_4(x##y##x##z, 0,1,0,2)   \
    DEFINE_SWIZZLE_4(x##y##x##w, 0,1,0,3)   \
    DEFINE_SWIZZLE_4(x##y##y##x, 0,1,1,0)   \
    DEFINE_SWIZZLE_4(x##y##y##y, 0,1,1,1)   \
    DEFINE_SWIZZLE_4(x##y##y##z, 0,1,1,2)   \
    DEFINE_SWIZZLE_4(x##y##y##w, 0,1,1,3)   \
    DEFINE_SWIZZLE_4(x##y##z##x, 0,1,2,0)   \
    DEFINE_SWIZZLE_4(x##y##z##y, 0,1,2,1)   \
    DEFINE_SWIZZLE_4(x##y##z##z, 0,1,2,2)   \
    DEFINE_SWIZZLE_4(x##y##z##w, 0,1,2,3)   \
    DEFINE_SWIZZLE_4(x##y##w##x, 0,1,3,0)   \
    DEFINE_SWIZZLE_4(x##y##w##y, 0,1,3,1)   \
    DEFINE_SWIZZLE_4(x##y##w##z, 0,1,3,2)   \
    DEFINE_SWIZZLE_4(x##y##w##w, 0,1,3,3)   \
    DEFINE_SWIZZLE_4(x##z##x##x, 0,2,0,0)   \
    DEFINE_SWIZZLE_4(x##z##x##y, 0,2,0,1)   \
    DEFINE_SWIZZLE_4(x##z##x##z, 0,2,0,2)   \
    DEFINE_SWIZZLE_4(x##z##x##w, 0,2,0,3)   \
    DEFINE_SWIZZLE_4(x##z##y##x, 0,2,1,0)   \
    DEFINE_SWIZZLE_4(x##z##y##y, 0,2,1,1)   \
    DEFINE_SWIZZLE_4(x##z##y##z, 0,2,1,2)   \
    DEFINE_SWIZZLE_4(x##z##y##w, 0,2,1,3)   \
    DEFINE_SWIZZLE_4(x##z##z##x, 0,2,2,0)   \
    DEFINE_SWIZZLE_4(x##z##z##y, 0,2,2,1)   \
    DEFINE_SWIZZLE_4(x##z##z##z, 0,2,2,2)   \
    DEFINE_SWIZZLE_4(x##z##z##w, 0,2,2,3)   \
    DEFINE_SWIZZLE_4(x##z##w##x, 0,2,3,0)   \
    DEFINE_SWIZZLE_4(x##z##w##y, 0,2,3,1)   \
    DEFINE_SWIZZLE_4(x##z##w##z, 0,2,3,2)   \
    DEFINE_SWIZZLE_4(x##z##w##w, 0,2,3,3)   \
    DEFINE_SWIZZLE_4(x##w##x##x, 0,3,0,0)   \
    DEFINE_SWIZZLE_4(x##w##x##y, 0,3,0,1)   \
    DEFINE_SWIZZLE_4(x##w##x##z, 0,3,0,2)   \
    DEFINE_SWIZZLE_4(x##w##x##w, 0,3,0,3)   \
    DEFINE_SWIZZLE_4(x##w##y##x, 0,3,1,0)   \
    DEFINE_SWIZZLE_4(x##w##y##y, 0,3,1,1)   \
    DEFINE_SWIZZLE_4(x##w##y##z, 0,3,1,2)   \
    DEFINE_SWIZZLE_4(x##w##y##w, 0,3,1,3)   \
    DEFINE_SWIZZLE_4(x##w##z##x, 0,3,2,0)   \
    DEFINE_SWIZZLE_4(x##w##z##y, 0,3,2,1)   \
    DEFINE_SWIZZLE_4(x##w##z##z, 0,3,2,2)   \
    DEFINE_SWIZZLE_4(x##w##z##w, 0,3,2,3)   \
    DEFINE_SWIZZLE_4(x##w##w##x, 0,3,3,0)   \
    DEFINE_SWIZZLE_4(x##w##w##y, 0,3,3,1)   \
    DEFINE_SWIZZLE_4(x##w##w##z, 0,3,3,2)   \
    DEFINE_SWIZZLE_4(x##w##w##w, 0,3,3,3)   \
    DEFINE_SWIZZLE_4(y##x##x##x, 1,0,0,0)   \
    DEFINE_SWIZZLE_4(y##x##x##y, 1,0,0,1)   \
    DEFINE_SWIZZLE_4(y##x##x##z, 1,0,0,2)   \
    DEFINE_SWIZZLE_4(y##x##x##w, 1,0,0,3)   \
    DEFINE_SWIZZLE_4(y##x##y##x, 1,0,1,0)   \
    DEFINE_SWIZZLE_4(y##x##y##y, 1,0,1,1)   \
    DEFINE_SWIZZLE_4(y##x##y##z, 1,0,1,2)   \
    DEFINE_SWIZZLE_4(y##x##y##w, 1,0,1,3)   \
    DEFINE_SWIZZLE_4(y##x##z##x, 1,0,2,0)   \
    DEFINE_SWIZZLE_4(y##x##z##y, 1,0,2,1)   \
    DEFINE_SWIZZLE_4(y##x##z##z, 1,0,2,2)   \
    DEFINE_SWIZZLE_4(y##x##z##w, 1,0,2,3)   \
    DEFINE_SWIZZLE_4(y##x##w##x, 1,0,3,0)   \
    DEFINE_SWIZZLE_4(y##x##w##y, 1,0,3,1)   \
    DEFINE_SWIZZLE_4(y##x##w##z, 1,0,3,2)   \
    DEFINE_SWIZZLE_4(y##x##w##w, 1,0,3,3)   \
    DEFINE_SWIZZLE_4(y##y##x##x, 1,1,0,0)   \
    DEFINE_SWIZZLE_4(y##y##x##y, 1,1,0,1)   \
    DEFINE_SWIZZLE_4(y##y##x##z, 1,1,0,2)   \
    DEFINE_SWIZZLE_4(y##y##x##w, 1,1,0,3)   \
    DEFINE_SWIZZLE_4(y##y##y##x, 1,1,1,0)   \
    DEFINE_SWIZZLE_4(y##y##y##y, 1,1,1,1)   \
    DEFINE_SWIZZLE_4(y##y##y##z, 1,1,1,2)   \
    DEFINE_SWIZZLE_4(y##y##y##w, 1,1,1,3)   \
    DEFINE_SWIZZLE_4(y##y##z##x, 1,1,2,0)   \
    DEFINE_SWIZZLE_4(y##y##z##y, 1,1,2,1)   \
    DEFINE_SWIZZLE_4(y##y##z##z, 1,1,2,2)   \
    DEFINE_SWIZZLE_4(y##y##z##w, 1,1,2,3)   \
    DEFINE_SWIZZLE_4(y##y##w##x, 1,1,3,0)   \
    DEFINE_SWIZZLE_4(y##y##w##y, 1,1,3,1)   \
    DEFINE_SWIZZLE_4(y##y##w##z, 1,1,3,2)   \
    DEFINE_SWIZZLE_4(y##y##w##w, 1,1,3,3)   \
    DEFINE_SWIZZLE_4(y##z##x##x, 1,2,0,0)   \
    DEFINE_SWIZZLE_4(y##z##x##y, 1,2,0,1)   \
    DEFINE_SWIZZLE_4(y##z##x##z, 1,2,0,2)   \
    DEFINE_SWIZZLE_4(y##z##x##w, 1,2,0,3)   \
    DEFINE_SWIZZLE_4(y##z##y##x, 1,2,1,0)   \
    DEFINE_SWIZZLE_4(y##z##y##y, 1,2,1,1)   \
    DEFINE_SWIZZLE_4(y##z##y##z, 1,2,1,2)   \
    DEFINE_SWIZZLE_4(y##z##y##w, 1,2,1,3)   \
    DEFINE_SWIZZLE_4(y##z##z##x, 1,2,2,0)   \
    DEFINE_SWIZZLE_4(y##z##z##y, 1,2,2,1)   \
    DEFINE_SWIZZLE_4(y##z##z##z, 1,2,2,2)   \
    DEFINE_SWIZZLE_4(y##z##z##w, 1,2,2,3)   \
    DEFINE_SWIZZLE_4(y##z##w##x, 1,2,3,0)   \
    DEFINE_SWIZZLE_4(y##z##w##y, 1,2,3,1)   \
    DEFINE_SWIZZLE_4(y##z##w##z, 1,2,3,2)   \
    DEFINE_SWIZZLE_4(y##z##w##w, 1,2,3,3)   \
    DEFINE_SWIZZLE_4(y##w##x##x, 1,3,0,0)   \
    DEFINE_SWIZZLE_4(y##w##x##y, 1,3,0,1)   \
    DEFINE_SWIZZLE_4(y##w##x##z, 1,3,0,2)   \
    DEFINE_SWIZZLE_4(y##w##x##w, 1,3,0,3)   \
    DEFINE_SWIZZLE_4(y##w##y##x, 1,3,1,0)   \
    DEFINE_SWIZZLE_4(y##w##y##y, 1,3,1,1)   \
    DEFINE_SWIZZLE_4(y##w##y##z, 1,3,1,2)   \
    DEFINE_SWIZZLE_4(y##w##y##w, 1,3,1,3)   \
    DEFINE_SWIZZLE_4(y##w##z##x, 1,3,2,0)   \
    DEFINE_SWIZZLE_4(y##w##z##y, 1,3,2,1)   \
    DEFINE_SWIZZLE_4(y##w##z##z, 1,3,2,2)   \
    DEFINE_SWIZZLE_4(y##w##z##w, 1,3,2,3)   \
    DEFINE_SWIZZLE_4(y##w##w##x, 1,3,3,0)   \
    DEFINE_SWIZZLE_4(y##w##w##y, 1,3,3,1)   \
    DEFINE_SWIZZLE_4(y##w##w##z, 1,3,3,2)   \
    DEFINE_SWIZZLE_4(y##w##w##w, 1,3,3,3)   \
    DEFINE_SWIZZLE_4(z##x##x##x, 2,0,0,0)   \
    DEFINE_SWIZZLE_4(z##x##x##y, 2,0,0,1)   \
    DEFINE_SWIZZLE_4(z##x##x##z, 2,0,0,2)   \
    DEFINE_SWIZZLE_4(z##x##x##w, 2,0,0,3)   \
    DEFINE_SWIZZLE_4(z##x##y##x, 2,0,1,0)   \
    DEFINE_SWIZZLE_4(z##x##y##y, 2,0,1,1)   \
    DEFINE_SWIZZLE_4(z##x##y##z, 2,0,1,2)   \
    DEFINE_SWIZZLE_4(z##x##y##w, 2,0,1,3)   \
    DEFINE_SWIZZLE_4(z##x##z##x, 2,0,2,0)   \
    DEFINE_SWIZZLE_4(z##x##z##y, 2,0,2,1)   \
    DEFINE_SWIZZLE_4(z##x##z##z, 2,0,2,2)   \
    DEFINE_SWIZZLE_4(z##x##z##w, 2,0,2,3)   \
    DEFINE_SWIZZLE_4(z##x##w##x, 2,0,3,0)   \
    DEFINE_SWIZZLE_4(z##x##w##y, 2,0,3,1)   \
    DEFINE_SWIZZLE_4(z##x##w##z, 2,0,3,2)   \
    DEFINE_SWIZZLE_4(z##x##w##w, 2,0,3,3)   \
    DEFINE_SWIZZLE_4(z##y##x##x, 2,1,0,0)   \
    DEFINE_SWIZZLE_4(z##y##x##y, 2,1,0,1)   \
    DEFINE_SWIZZLE_4(z##y##x##z, 2,1,0,2)   \
    DEFINE_SWIZZLE_4(z##y##x##w, 2,1,0,3)   \
    DEFINE_SWIZZLE_4(z##y##y##x, 2,1,1,0)   \
    DEFINE_SWIZZLE_4(z##y##y##y, 2,1,1,1)   \
    DEFINE_SWIZZLE_4(z##y##y##z, 2,1,1,2)   \
    DEFINE_SWIZZLE_4(z##y##y##w, 2,1,1,3)   \
    DEFINE_SWIZZLE_4(z##y##z##x, 2,1,2,0)   \
    DEFINE_SWIZZLE_4(z##y##z##y, 2,1,2,1)   \
    DEFINE_SWIZZLE_4(z##y##z##z, 2,1,2,2)   \
    DEFINE_SWIZZLE_4(z##y##z##w, 2,1,2,3)   \
    DEFINE_SWIZZLE_4(z##y##w##x, 2,1,3,0)   \
    DEFINE_SWIZZLE_4(z##y##w##y, 2,1,3,1)   \
    DEFINE_SWIZZLE_4(z##y##w##z, 2,1,3,2)   \
    DEFINE_SWIZZLE_4(z##y##w##w, 2,1,3,3)   \
    DEFINE_SWIZZLE_4(z##z##x##x, 2,2,0,0)   \
    DEFINE_SWIZZLE_4(z##z##x##y, 2,2,0,1)   \
    DEFINE_SWIZZLE_4(z##z##x##z, 2,2,0,2)   \
    DEFINE_SWIZZLE_4(z##z##x##w, 2,2,0,3)   \
    DEFINE_SWIZZLE_4(z##z##y##x, 2,2,1,0)   \
    DEFINE_SWIZZLE_4(z##z##y##y, 2,2,1,1)   \
    DEFINE_SWIZZLE_4(z##z##y##z, 2,2,1,2)   \
    DEFINE_SWIZZLE_4(z##z##y##w, 2,2,1,3)   \
    DEFINE_SWIZZLE_4(z##z##z##x, 2,2,2,0)   \
    DEFINE_SWIZZLE_4(z##z##z##y, 2,2,2,1)   \
    DEFINE_SWIZZLE_4(z##z##z##z, 2,2,2,2)   \
    DEFINE_SWIZZLE_4(z##z##z##w, 2,2,2,3)   \
    DEFINE_SWIZZLE_4(z##z##w##x, 2,2,3,0)   \
    DEFINE_SWIZZLE_4(z##z##w##y, 2,2,3,1)   \
    DEFINE_SWIZZLE_4(z##z##w##z, 2,2,3,2)   \
    DEFINE_SWIZZLE_4(z##z##w##w, 2,2,3,3)   \
    DEFINE_SWIZZLE_4(z##w##x##x, 2,3,0,0)   \
    DEFINE_SWIZZLE_4(z##w##x##y, 2,3,0,1)   \
    DEFINE_SWIZZLE_4(z##w##x##z, 2,3,0,2)   \
    DEFINE_SWIZZLE_4(z##w##x##w, 2,3,0,3)   \
    DEFINE_SWIZZLE_4(z##w##y##x, 2,3,1,0)   \
    DEFINE_SWIZZLE_4(z##w##y##y, 2,3,1,1)   \
    DEFINE_SWIZZLE_4(z##w##y##z, 2,3,1,2)   \
    DEFINE_SWIZZLE_4(z##w##y##w, 2,3,1,3)   \
    DEFINE_SWIZZLE_4(z##w##z##x, 2,3,2,0)   \
    DEFINE_SWIZZLE_4(z##w##z##y, 2,3,2,1)   \
    DEFINE_SWIZZLE_4(z##w##z##z, 2,3,2,2)   \
    DEFINE_SWIZZLE_4(z##w##z##w, 2,3,2,3)   \
    DEFINE_SWIZZLE_4(z##w##w##x, 2,3,3,0)   \
    DEFINE_SWIZZLE_4(z##w##w##y, 2,3,3,1)   \
    DEFINE_SWIZZLE_4(z##w##w##z, 2,3,3,2)   \
    DEFINE_SWIZZLE_4(z##w##w##w, 2,3,3,3)   \
    DEFINE_SWIZZLE_4(w##x##x##x, 3,0,0,0)   \
    DEFINE_SWIZZLE_4(w##x##x##y, 3,0,0,1)   \
    DEFINE_SWIZZLE_4(w##x##x##z, 3,0,0,2)   \
    DEFINE_SWIZZLE_4(w##x##x##w, 3,0,0,3)   \
    DEFINE_SWIZZLE_4(w##x##y##x, 3,0,1,0)   \
    DEFINE_SWIZZLE_4(w##x##y##y, 3,0,1,1)   \
    DEFINE_SWIZZLE_4(w##x##y##z, 3,0,1,2)   \
    DEFINE_SWIZZLE_4(w##x##y##w, 3,0,1,3)   \
    DEFINE_SWIZZLE_4(w##x##z##x, 3,0,2,0)   \
    DEFINE_SWIZZLE_4(w##x##z##y, 3,0,2,1)   \
    DEFINE_SWIZZLE_4(w##x##z##z, 3,0,2,2)   \
    DEFINE_SWIZZLE_4(w##x##z##w, 3,0,2,3)   \
    DEFINE_SWIZZLE_4(w##x##w##x, 3,0,3,0)   \
    DEFINE_SWIZZLE_4(w##x##w##y, 3,0,3,1)   \
    DEFINE_SWIZZLE_4(w##x##w##z, 3,0,3,2)   \
    DEFINE_SWIZZLE_4(w##x##w##w, 3,0,3,3)   \
    DEFINE_SWIZZLE_4(w##y##x##x, 3,1,0,0)   \
    DEFINE_SWIZZLE_4(w##y##x##y, 3,1,0,1)   \
    DEFINE_SWIZZLE_4(w##y##x##z, 3,1,0,2)   \
    DEFINE_SWIZZLE_4(w##y##x##w, 3,1,0,3)   \
    DEFINE_SWIZZLE_4(w##y##y##x, 3,1,1,0)   \
    DEFINE_SWIZZLE_4(w##y##y##y, 3,1,1,1)   \
    DEFINE_SWIZZLE_4(w##y##y##z, 3,1,1,2)   \
    DEFINE_SWIZZLE_4(w##y##y##w, 3,1,1,3)   \
    DEFINE_SWIZZLE_4(w##y##z##x, 3,1,2,0)   \
    DEFINE_SWIZZLE_4(w##y##z##y, 3,1,2,1)   \
    DEFINE_SWIZZLE_4(w##y##z##z, 3,1,2,2)   \
    DEFINE_SWIZZLE_4(w##y##z##w, 3,1,2,3)   \
    DEFINE_SWIZZLE_4(w##y##w##x, 3,1,3,0)   \
    DEFINE_SWIZZLE_4(w##y##w##y, 3,1,3,1)   \
    DEFINE_SWIZZLE_4(w##y##w##z, 3,1,3,2)   \
    DEFINE_SWIZZLE_4(w##y##w##w, 3,1,3,3)   \
    DEFINE_SWIZZLE_4(w##z##x##x, 3,2,0,0)   \
    DEFINE_SWIZZLE_4(w##z##x##y, 3,2,0,1)   \
    DEFINE_SWIZZLE_4(w##z##x##z, 3,2,0,2)   \
    DEFINE_SWIZZLE_4(w##z##x##w, 3,2,0,3)   \
    DEFINE_SWIZZLE_4(w##z##y##x, 3,2,1,0)   \
    DEFINE_SWIZZLE_4(w##z##y##y, 3,2,1,1)   \
    DEFINE_SWIZZLE_4(w##z##y##z, 3,2,1,2)   \
    DEFINE_SWIZZLE_4(w##z##y##w, 3,2,1,3)   \
    DEFINE_SWIZZLE_4(w##z##z##x, 3,2,2,0)   \
    DEFINE_SWIZZLE_4(w##z##z##y, 3,2,2,1)   \
    DEFINE_SWIZZLE_4(w##z##z##z, 3,2,2,2)   \
    DEFINE_SWIZZLE_4(w##z##z##w, 3,2,2,3)   \
    DEFINE_SWIZZLE_4(w##z##w##x, 3,2,3,0)   \
    DEFINE_SWIZZLE_4(w##z##w##y, 3,2,3,1)   \
    DEFINE_SWIZZLE_4(w##z##w##z, 3,2,3,2)   \
    DEFINE_SWIZZLE_4(w##z##w##w, 3,2,3,3)   \
    DEFINE_SWIZZLE_4(w##w##x##x, 3,3,0,0)   \
    DEFINE_SWIZZLE_4(w##w##x##y, 3,3,0,1)   \
    DEFINE_SWIZZLE_4(w##w##x##z, 3,3,0,2)   \
    DEFINE_SWIZZLE_4(w##w##x##w, 3,3,0,3)   \
    DEFINE_SWIZZLE_4(w##w##y##x, 3,3,1,0)   \
    DEFINE_SWIZZLE_4(w##w##y##y, 3,3,1,1)   \
    DEFINE_SWIZZLE_4(w##w##y##z, 3,3,1,2)   \
    DEFINE_SWIZZLE_4(w##w##y##w, 3,3,1,3)   \
    DEFINE_SWIZZLE_4(w##w##z##x, 3,3,2,0)   \
    DEFINE_SWIZZLE_4(w##w##z##y, 3,3,2,1)   \
    DEFINE_SWIZZLE_4(w##w##z##z, 3,3,2,2)   \
    DEFINE_SWIZZLE_4(w##w##z##w, 3,3,2,3)   \
    DEFINE_SWIZZLE_4(w##w##w##x, 3,3,3,0)   \
    DEFINE_SWIZZLE_4(w##w##w##y, 3,3,3,1)   \
    DEFINE_SWIZZLE_4(w##w##w##z, 3,3,3,2)   \
    DEFINE_SWIZZLE_4(w##w##w##w, 3,3,3,3)

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
    struct vec_t final {
        using Self = vec_t;

        T __fields[Len];

        DEFINE_PROPERTIES(x, y, z, w)
        DEFINE_PROPERTIES(r, g, b, a)

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
    };

    template<typename T, size_t Cols, size_t Rows>
    struct mat_t final {
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

    template<typename T, size_t Len, size_t... I>
    struct vec_impl<T, Len, std::index_sequence<I...>> {
        using Self = vec_t<T, Len>;

        inline static constexpr auto add(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] + $2[I]) ...};
        }
        inline static constexpr auto sub(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] - $2[I]) ...};
        }
        inline static constexpr auto mul(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] * $2[I]) ...};
        }
        inline static constexpr auto div(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] / $2[I]) ...};
        }
        inline static constexpr auto mod(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] % $2[I]) ...};
        }
        inline static constexpr auto shl(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] << $2[I]) ...};
        }
        inline static constexpr auto shr(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] >> $2[I]) ...};
        }
        inline static constexpr auto band(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] & $2[I]) ...};
        }
        inline static constexpr auto bor(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] | $2[I]) ...};
        }
        inline static constexpr auto bxor(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] ^ $2[I]) ...};
        }
        inline static constexpr auto add(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] + $2) ...};
        }
        inline static constexpr auto sub(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] - $2) ...};
        }
        inline static constexpr auto mul(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] * $2) ...};
        }
        inline static constexpr auto div(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] / $2) ...};
        }
        inline static constexpr auto mod(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] % $2) ...};
        }
        inline static constexpr auto shl(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] << $2) ...};
        }
        inline static constexpr auto shr(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] >> $2) ...};
        }
        inline static constexpr auto band(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] & $2) ...};
        }
        inline static constexpr auto bor(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] | $2) ...};
        }
        inline static constexpr auto bxor(Self const& $1, T const& $2) -> Self {
            return Self{($1[I] ^ $2) ...};
        }
        inline static constexpr auto add(T const& $1, Self const& $2) -> Self {
            return Self{($1 + $2[I]) ...};
        }
        inline static constexpr auto sub(T const& $1, Self const& $2) -> Self {
            return Self{($1 - $2[I]) ...};
        }
        inline static constexpr auto mul(T const& $1, Self const& $2) -> Self {
            return Self{($1 * $2[I]) ...};
        }
        inline static constexpr auto div(T const& $1, Self const& $2) -> Self {
            return Self{($1 / $2[I]) ...};
        }
        inline static constexpr auto mod(T const& $1, Self const& $2) -> Self {
            return Self{($1 % $2[I]) ...};
        }
        inline static constexpr auto shl(T const& $1, Self const& $2) -> Self {
            return Self{($1 << $2[I]) ...};
        }
        inline static constexpr auto shr(T const& $1, Self const& $2) -> Self {
            return Self{($1 >> $2[I]) ...};
        }
        inline static constexpr auto band(T const& $1, Self const& $2) -> Self {
            return Self{($1 & $2[I]) ...};
        }
        inline static constexpr auto bor(T const& $1, Self const& $2) -> Self {
            return Self{($1 | $2[I]) ...};
        }
        inline static constexpr auto bxor(T const& $1, Self const& $2) -> Self {
            return Self{($1 ^ $2[I]) ...};
        }
        inline static constexpr auto dot(Self const& $1, Self const& $2) -> T {
            return (($1[I] * $2[I]) + ...);
        }
        inline static constexpr auto csum(Self const& $1) -> T {
            return ($1[I] + ...);
        }
        template<typename U>
        inline static constexpr auto cast(Self const& $1) -> vec_t<U, Len> {
            return vec_t<U, Len>{static_cast<U>($1[I])...};
        }
        inline static constexpr auto floor(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::floor($1[I])...};
        }
        inline static constexpr auto ceil(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::ceil($1[I])...};
        }
        inline static constexpr auto round(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::round($1[I])...};
        }
        inline static constexpr auto sin(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::sin($1[I])...};
        }
        inline static constexpr auto cos(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::cos($1[I])...};
        }
        inline static constexpr auto sqrt(Self const& $1) -> Self requires std::floating_point<T> {
            return Self{std::sqrt($1[I])...};
        }
        inline static constexpr auto fract(Self const& $1) -> Self requires std::floating_point<T> {
            return $1 - floor($1);
        }
        inline static constexpr auto length(Self const& $1) -> T requires std::floating_point<T> {
            return std::sqrt(dot($1, $1));
        }
        inline static constexpr auto sign(Self const& $1) -> Self {
            return Self{($1[I] < static_cast<T>(0) ? static_cast<T>(-1) : ($1[I] > static_cast<T>(0) ? static_cast<T>(1) : static_cast<T>(0)))...};
        }
        inline static constexpr auto normalize(Self const& $1) -> T requires std::floating_point<T> {
            return $1 / length($1);
        }
        inline static constexpr auto abs(Self const& $1) -> Self {
            return Self{std::abs($1[I])...};
        }
        inline static constexpr auto min(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] < $2[I] ? $1[I] : $2[I])...};
        }
        inline static constexpr auto max(Self const& $1, Self const& $2) -> Self {
            return Self{($1[I] > $2[I] ? $1[I] : $2[I])...};
        }
    };

    template<typename T, size_t Cols, size_t Rows, size_t... Ci, size_t... Ri>
    struct mat_impl<T, Cols, Rows, std::index_sequence<Ci...>, std::index_sequence<Ri...>> {
        using Self = mat_t<T, Cols, Rows>;

        inline static constexpr auto col(Self const& self, size_t i) -> vec_t<T, Rows> {
            return self.__columns[i];
        }
        inline static constexpr auto row(Self const& self, size_t i) -> vec_t<T, Cols> {
            return vec_t<T, Cols>{self.__columns[Ci][i]...};
        }
        inline static constexpr auto mul(Self const& $1, Self const& $2) -> Self {
            return Self{$1 * $2.__columns[Ci]...};
        }
        inline static constexpr auto mul(Self const& $1, vec_t<T, Cols> const& $2) -> vec_t<T, Cols> {
            return (($1.__columns[Ci] * $2[Ci]) + ...);
        }
        inline static constexpr auto mul(vec_t<T, Cols> const& $1, Self const& $2) -> vec_t<T, Cols> {
            return (($1[Ci] * $2.row(Ri)) + ...);
        }
    };

    template<typename T, size_t Len>
    inline static constexpr auto dot(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> T {
        return vec_impl<T, Len>::dot($1, $2);
    }
    template<typename T, size_t Len>
    inline static constexpr auto csum(vec_t<T, Len> const& $1) -> T {
        return vec_impl<T, Len>::csum($1);
    }
    template<typename U, typename T, size_t Len>
    inline static constexpr auto cast(vec_t<T, Len> const& $1) -> vec_t<U, Len> {
        return vec_impl<T, Len>::template cast<U>($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto floor(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::floor($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto ceil(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::ceil($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto round(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::round($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto sin(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::sin($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto cos(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::cos($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto sqrt(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::sqrt($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto fract(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::fract($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto length(vec_t<T, Len> const& $1) -> T {
        return vec_impl<T, Len>::length($1);
    }
    template<typename T, size_t Len>
    inline static constexpr auto sign(vec_t<T, Len> const& $1) -> vec_impl<T, Len> {
        return vec_impl<T, Len>::sign($1);
    }
    template<std::floating_point T, size_t Len>
    inline static constexpr auto normalize(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::normalize($1);
    }
    template<typename T, size_t Len>
    inline static constexpr auto abs(vec_t<T, Len> const& $1) -> vec_t<T, Len> {
        return vec_impl<T, Len>::abs($1);
    }
    template<typename T, size_t Len>
    inline static constexpr auto min(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> vec_t<T, Len> {
        return vec_impl<T, Len>::min($1, $2);
    }
    template<typename T, size_t Len>
    inline static constexpr auto max(vec_t<T, Len> const& $1, vec_t<T, Len> const& $2) -> vec_t<T, Len> {
        return vec_impl<T, Len>::max($1, $2);
    }

    template<typename T>
    inline static constexpr auto vec2(T $1) -> vec_t<T, 2> {
        return vec_t<T, 2>{$1, $1};
    }
    template<typename T>
    inline static constexpr auto vec2(T $1, T $2)  -> vec_t<T, 2> {
        return vec_t<T, 2>{$1, $2};
    }
    template<typename T>
    inline static constexpr auto vec3(T $1) -> vec_t<T, 3> {
        return vec_t<T, 3>{$1, $1, $1};
    }
    template<typename T>
    inline static constexpr auto vec3(T $1, T $2, T $3) -> vec_t<T, 3> {
        return vec_t<T, 3>{$1, $2, $3};
    }
    template<typename T>
    inline static constexpr auto vec3(vec_t<T, 2> $1, T $2) -> vec_t<T, 3> {
        return vec_t<T, 3>{$1.x, $1.y, $2};
    }
    template<typename T>
    inline static constexpr auto vec3(T $1, vec_t<T, 2> $2) -> vec_t<T, 3> {
        return vec_t<T, 3>{$1, $2.x, $2.y};
    }
    template<typename T>
    inline static constexpr auto vec4(T $1) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1, $1, $1, $1};
    }
    template<typename T>
    inline static constexpr auto vec4(T $1, T $2, T $3, T $4) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1, $2, $3, $4};
    }
    template<typename T>
    inline static constexpr auto vec4(vec_t<T, 2> $1, T $2, T $3) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1.x, $1.y, $2, $3};
    }
    template<typename T>
    inline static constexpr auto vec4(T $1, vec_t<T, 2> $2, T $3) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1, $2.x, $2.y, $3};
    }
    template<typename T>
    inline static constexpr auto vec4(T $1, T $2, vec_t<T, 2> $3) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1, $2, $3.x, $3.y};
    }
    template<typename T>
    inline static constexpr auto vec4(vec_t<T, 2> $1, vec_t<T, 2> $2) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1.x, $1.y, $2.x, $2.y};
    }
    template<typename T>
    inline static constexpr auto vec4(vec_t<T, 3> $1, T $2) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1.x, $1.y, $1.z, $2};
    }
    template<typename T>
    inline static constexpr auto vec4(T $1, vec_t<T, 3> $2) -> vec_t<T, 4> {
        return vec_t<T, 4>{$1, $2.x, $2.y, $2.z};
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
#undef DEFINE_PROPERTIES