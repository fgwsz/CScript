#pragma once
#include"Variant.hpp"
// ... : bind list
#define Function_Begin(function_name__,result_type__) \
    result_type__ function_name__(Variant parameter_list__) { \
        unsigned long long index__=0; \
//
#define Parameter(type__,name__) \
    type__& name__= \
        parameter_list__.array()[(index__++)] \
        .data<type__>(); \
//
#define Function_End \
        return {}; \
    } \
//
// ... : bind list
#define Lambda_Begin(result_type__,...) \
    Function{ \
        [__VA_ARGS__](Variant parameter_list__) \
        ->result_type__{ \
            unsigned long long index__=0; \
//
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
