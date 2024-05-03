#pragma once
#include<type_traits>
template<typename Type>
static constexpr bool is_value_type_v=
    ::std::is_same_v<::std::decay_t<Type>,Type>
    &&(!::std::is_void_v<Type>);
