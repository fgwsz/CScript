#pragma once
#include"BoxManger.hpp"
// SSO && COW && Object Pool
template<typename _ValueType>
requires is_value_type_v<_ValueType>
class Box final{
public:
    using value_type=_ValueType;
    static constexpr bool is_big_size_v=
        sizeof(value_type)>sizeof(value_type*);
    using manger_type=BoxManger<_ValueType>;
private:
    union{//SSO
        value_type* data_;
        char byte_array_[sizeof(value_type*)];
    };
    constexpr value_type* byte_array()const{
        return reinterpret_cast<value_type*>(
            const_cast<char*>(&(this->byte_array_[0]))
        );
    }
public:
    constexpr Box(value_type const& value={}){
        if constexpr(is_big_size_v){
            this->data_=nullptr;
            manger_type::copy_ref_object(this->data_,&value);
        }else{
            new(this->byte_array())value_type(value);
        }
    }
    constexpr Box(Box const& rhs)
        :Box(rhs.get())
    {}
    constexpr Box(Box&& rhs){
        if constexpr(is_big_size_v){
            this->data_=nullptr;
            manger_type::move_ref_object(this->data_,rhs.data_);
        }else{
            new(this->byte_array())value_type(rhs.get());
        }
    }
    constexpr Box& operator=(Box const& rhs){
        if(this!=&rhs){
            this->set(rhs.get());
        }
        return *this;
    }
    constexpr Box& operator=(Box&& rhs){
        if(this==&rhs){
            return *this;
        }
        if constexpr(is_big_size_v){
            manger_type::move_ref_object(this->data_,rhs.data_);
        }else{
            this->set(::std::move(*(rhs.byte_array())));
        }
        return *this;
    }
    constexpr ~Box(){
        if constexpr(is_big_size_v){
            manger_type::delete_ref_object(this->data_);
        }else{
            this->byte_array()->~value_type();
        }
    }
    constexpr value_type const& get()const{
        if constexpr(is_big_size_v){
            return *(this->data_);
        }else{
            return *(this->byte_array());
        }
    }
    constexpr void set(value_type const& value){
        if constexpr(is_big_size_v){
            manger_type::copy_ref_object(this->data_,&value);
        }else{
            if(&value==this->byte_array()){
                return;
            }
            *(this->byte_array())=value;
        }
    }
    constexpr void set(value_type&& value){
        if constexpr(is_big_size_v){
            *(this->data_)=::std::move(value);
        }else{
            if(&value==this->byte_array()){
                return;
            }
            *(this->byte_array())=::std::move(value);
        }
    }
};