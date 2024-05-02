#pragma once
#include<type_traits>
template<typename _Type>
static constexpr bool is_value_type_v=
    ::std::is_same_v<::std::decay_t<_Type>,_Type>
    &&(!::std::is_void_v<_Type>);