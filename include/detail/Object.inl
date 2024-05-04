#pragma once
#include"../Object.hpp"
constexpr Object::Object(Null const& value)noexcept
    :data_(typename Object::value_type{value}){};
constexpr Object::Object(Boolean const& value)noexcept
    :data_(typename Object::value_type{value}){}
constexpr Object::Object(Number const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(String const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(Vector const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(Map const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(Function const& value)noexcept
	:data_(typename Object::value_type{value}){}
template<ObjectType Type>
constexpr bool Object::is()const noexcept{
    return ::std::holds_alternative<Type>(this->data_.const_data());
}
template<ObjectType Type>
constexpr Type& Object::data(){
    return ::std::get<Type>(this->data_.data());
}
template<ObjectType Type>
constexpr Type const& Object::const_data()const{
    return ::std::get<Type>(this->data_.const_data());
}
constexpr bool Object::is_null()const noexcept{
    return this->is<Null>();
}
constexpr bool Object::is_boolean()const noexcept{
    return this->is<Boolean>();
}
constexpr bool Object::is_number()const noexcept{
    return this->is<Number>();
}
constexpr bool Object::is_string()const noexcept{
    return this->is<String>();
}
constexpr bool Object::is_vector()const noexcept{
    return this->is<Vector>();
}
constexpr bool Object::is_map()const noexcept{
    return this->is<Map>();
}
constexpr bool Object::is_function()const noexcept{
    return this->is<Function>();
}
constexpr Null& Object::null(){
    return this->data<Null>();
}
constexpr Boolean& Object::boolean(){
    return this->data<Boolean>();
}
constexpr Number& Object::number(){
    return this->data<Number>();
}
constexpr String& Object::string(){
    return this->data<String>();
}
constexpr Vector& Object::vector(){
    return this->data<Vector>();
}
constexpr Map& Object::map(){
    return this->data<Map>();
}
constexpr Function& Object::function(){
    return this->data<Function>();
}
constexpr Null const& Object:: Object::const_null()const{
    return this->const_data<Null>();
}
constexpr Boolean const& Object:: Object::const_boolean()const{
    return this->const_data<Boolean>();
}
constexpr Number const& Object:: Object::const_number()const{
    return this->const_data<Number>();
}
constexpr String const& Object:: Object::const_string()const{
    return this->const_data<String>();
}
constexpr Vector const& Object:: Object::const_vector()const{
    return this->const_data<Vector>();
}
constexpr Map const& Object:: Object::const_map()const{
    return this->const_data<Map>();
}
constexpr Function const& Object:: Object::const_function()const{
    return this->const_data<Function>();
}