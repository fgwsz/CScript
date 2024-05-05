#pragma once
#include"Variant.hpp"
// ... : bind list
#define Lambda_Begin(result_type__,...) \
    Function{ \
        [__VA_ARGS__](Variant argument_list__) \
        ->result_type__{ \
//
#define Lambda_Arg(index__,type__,name__) \
        type__& name__= \
            argument_list__.array()[index__] \
            .data<type__>(); \
//
#define Lambda_End \
            return {}; \
        } \
    } \
//
// ... : arguments
#define Invoke(...) \
    operator()(Array{__VA_ARGS__}) \
//
