#pragma once
#include"ValueType.hpp"
template<ValueType Type>
struct BoxManager{
    static constexpr Type* new_object();
    static constexpr void delete_object(Type*& object);
    static constexpr void copy_object(Type*& to,Type const* from);
    static constexpr void copy_object(Type*& object);
    static constexpr void move_object(Type*& to,Type*& from);
    static constexpr void clear();
    static constexpr void print_object_pool();
    static constexpr void print_memory_pool();
};
#include"detail/BoxManager.inl"