#pragma once
#include<type_traits>
#include"IsSame.hpp"
template<typename Type>
concept ValueType=
    IsSame<::std::decay_t<Type>,Type>::value
    &&(!IsSame<void,Type>::value);
