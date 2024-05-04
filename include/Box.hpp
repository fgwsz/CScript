#pragma once
#include"BoxManager.hpp"
template<typename Type>
struct Box final{
    static_assert(is_value_type_v<Type>);
    constexpr Box();
    constexpr ~Box();
    constexpr Box(Box<Type> const& rhs);
    constexpr Box(Box<Type>&& rhs);
    constexpr Box(Type const& value);
    constexpr Box<Type>& operator=(Box<Type> const& rhs);
    constexpr Box<Type>& operator=(Box<Type>&& rhs);
    constexpr Box<Type>& operator=(Type const& value);
    constexpr Type& data();
    constexpr Type const& const_data()const;
private:
    Type* data_;
};
#include"detail/Box.inl"