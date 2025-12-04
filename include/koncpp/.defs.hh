#ifndef KONCPP__DEFS__HH
#define KONCPP__DEFS__HH

/* clang-format off */
#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef KONCPP_BUILD
        #ifdef __GNUC__
            #define KONCPP_PUBLIC __attribute__((dllexport))
        #else
            #define KONCPP_PUBLIC __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define KONCPP_PUBLIC __attribute__((dllimport))
        #else
            #define KONCPP_PUBLIC __declspec(dllimport)
        #endif
    #endif

    #define KONCPP_LOCAL

#else
    #if __GNUC__ >= 4
        #define KONCPP_PUBLIC __attribute__((visibility("default")))
        #define KONCPP_LOCAL  __attribute__((visibility("hidden")))
    #else
        #define KONCPP_PUBLIC
        #define KONCPP_LOCAL
    #endif
#endif

/* clang-format on */

#endif /* KONCPP__DEFS__HH */
