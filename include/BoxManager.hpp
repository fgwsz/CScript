#pragma once
#include"is_value_type_v.hpp"
template<typename Type>
struct BoxManager{
    static_assert(is_value_type_v<Type>);
    static constexpr Type* new_object();
    static constexpr void delete_object(Type*& object);
    static constexpr void copy_object(Type*& to,Type const* from);
    static constexpr void move_object(Type*& to,Type*& from);
    static constexpr void clear();
};
#include"detail/BoxManager.inl"