#pragma once
#include"../Box.hpp"
#include<utility>//::std::move
namespace detail{
template<typename Type>
static constexpr bool is_small_object_v=sizeof(Type*)>sizeof(Type);
template<typename Type>
static Type* get_small_object(Type*& data){
    return static_cast<Type*>(static_cast<void*>(&data));//Type**
}
}//namespace detail
template<typename Type>
constexpr Box<Type>::Box()
    :data_(nullptr){
    if constexpr(detail::is_small_object_v<Type>){
        new(detail::get_small_object(this->data_))Type{};
    }else{
        this->data_=BoxManager<Type>::new_object();
    }
}
template<typename Type>
constexpr Box<Type>::~Box(){
    if constexpr(detail::is_small_object_v<Type>){
        detail::get_small_object(this->data_)->~Type();
    }else{
        BoxManager<Type>::delete_object(this->data_);
    }
}
template<typename Type>
constexpr Box<Type>::Box(Box<Type> const& rhs)
    :data_(nullptr){
    if constexpr(detail::is_small_object_v<Type>){
        new(detail::get_small_object(this->data_))Type{rhs.data()};
    }else{
        BoxManager<Type>::copy_object(this->data_,rhs.data_);
    }
}
template<typename Type>
constexpr Box<Type>::Box(Box<Type>&& rhs)
    :data_(nullptr){
    if constexpr(detail::is_small_object_v<Type>){
        new(detail::get_small_object(this->data_))Type{rhs.data()};
    }else{
        BoxManager<Type>::move_object(this->data_,rhs.data_);
    }
}
template<typename Type>
constexpr Box<Type>::Box(Type const& value)
    :data_(nullptr){
    if constexpr(detail::is_small_object_v<Type>){
        new(detail::get_small_object(this->data_))Type{value};
    }else{
        BoxManager<Type>::copy_object(this->data_,&value);
    }
}
template<typename Type>
constexpr Box<Type>& Box<Type>::operator=(Box<Type> const& rhs){
    if(this==&rhs){
        return *this;
    }
    return this->operator=(rhs.data());
}
template<typename Type>
constexpr Box<Type>& Box<Type>::operator=(Box<Type>&& rhs){
    if(this==&rhs){
        return *this;
    }
    if constexpr(detail::is_small_object_v<Type>){
        *detail::get_small_object(this->data_)=
            ::std::move(*detail::get_small_object(rhs.data_));
    }else{
        BoxManager<Type>::move_object(this->data_,rhs.data_);
    }
    return *this;
}
template<typename Type>
constexpr Box<Type>& Box<Type>::operator=(Type const& value){
    if constexpr(detail::is_small_object_v<Type>){
        if(detail::get_small_object(this->data_)==&value){
            return *this;
        }
        *detail::get_small_object(this->data_)=value;
    }else{
        BoxManager<Type>::copy_object(this->data_,&value);
    }
    return *this;
}
template<typename Type>
constexpr Type const& Box<Type>::data()const{
    if constexpr(detail::is_small_object_v<Type>){
        return *detail::get_small_object(
            const_cast<Type*&>(this->data_)
        );
    }else{
        return *(this->data_);
    }
}
