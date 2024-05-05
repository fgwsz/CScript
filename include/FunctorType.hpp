#pragma once
#include<type_traits>
template<typename Type>
concept FunctorType=
    requires{ {::std::remove_cvref_t<Type>::operator()};};