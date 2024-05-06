#pragma once
#include<stdexcept>
#include"Variant.hpp"
#include"variant_to_string.hpp"
#include"Logger.hpp"
constexpr Variant::Variant(Null const& value)noexcept
    :data_(typename Variant::value_type{value}){};
constexpr Variant::Variant(Boolean const& value)noexcept
    :data_(typename Variant::value_type{value}){}
constexpr Variant::Variant(Number const& value)noexcept
	:data_(typename Variant::value_type{value}){}
constexpr Variant::Variant(String const& value)noexcept
	:data_(typename Variant::value_type{value}){}
constexpr Variant::Variant(Array const& value)noexcept
	:data_(typename Variant::value_type{value}){}
constexpr Variant::Variant(Object const& value)noexcept
	:data_(typename Variant::value_type{value}){}
constexpr Variant::Variant(Function const& value)noexcept
	:data_(typename Variant::value_type{value}){}
template<VariantType Type>
constexpr bool Variant::is()const noexcept{
    if constexpr(
        IsSame<Type,Variant>::value
        ||IsSame<Type,Variant const>::value
    ){
        return true;
    }else{
        return ::std::holds_alternative<::std::remove_const_t<Type>>(this->data_.const_data());
    }
}
namespace detail{
template<VariantType Type>struct VariantTypeName;

template<>
struct VariantTypeName<Null>
{static constexpr ::std::string_view value="Null";};
template<>
struct VariantTypeName<Boolean>
{static constexpr ::std::string_view value="Boolean";};
template<>
struct VariantTypeName<Number>
{static constexpr ::std::string_view value="Number";};
template<>
struct VariantTypeName<String>
{static constexpr ::std::string_view value="String";};
template<>
struct VariantTypeName<Array>
{static constexpr ::std::string_view value="Array";};
template<>
struct VariantTypeName<Object>
{static constexpr ::std::string_view value="Object";};
template<>
struct VariantTypeName<Function>
{static constexpr ::std::string_view value="Function";};

template<>
struct VariantTypeName<Null const>
{static constexpr ::std::string_view value="Null";};
template<>
struct VariantTypeName<Boolean const>
{static constexpr ::std::string_view value="Boolean";};
template<>
struct VariantTypeName<Number const>
{static constexpr ::std::string_view value="Number";};
template<>
struct VariantTypeName<String const>
{static constexpr ::std::string_view value="String";};
template<>
struct VariantTypeName<Array const>
{static constexpr ::std::string_view value="Array";};
template<>
struct VariantTypeName<Object const>
{static constexpr ::std::string_view value="Object";};
template<>
struct VariantTypeName<Function const>
{static constexpr ::std::string_view value="Function";};
}//namespace detail
template<VariantType Type>
constexpr Type& Variant::data(){
    if constexpr(
        IsSame<Type,Variant>::value
        ||IsSame<Type,Variant const>::value
    ){
        return *this;
    }else if(this->is<Type>()){
        return ::std::get<::std::remove_const_t<Type>>(this->data_.data());
    }else{
        auto message=
            ::std::string("Variant(")
            .append(this->type_name())
            .append(") Cast To ")
            .append(detail::VariantTypeName<Type>::value);
        Logger::error(message);
        throw ::std::runtime_error(message);
    }
}
template<VariantType Type>
constexpr Type const& Variant::const_data()const{
    if constexpr(
        IsSame<Type,Variant>::value
        ||IsSame<Type,Variant const>::value
    ){
        return *this;
    }else if(this->is<Type>()){
        return ::std::get<::std::remove_const_t<Type>>(this->data_.const_data());
    }else{
        auto message=
            ::std::string("Variant(")
            .append(this->type_name())
            .append(") Cast To ")
            .append(detail::VariantTypeName<Type>::value);
        Logger::error(message);
        throw ::std::runtime_error(message);
    }
}
constexpr ::std::string_view Variant::type_name()const noexcept{
    if(this->is<Null>()){
        return "Null";
    }else if(this->is<Boolean>()){
        return "Boolean";
    }else if(this->is<Number>()){
        return "Number";
    }else if(this->is<String>()){
        return "String";
    }else if(this->is<Array>()){
        return "Array";
    }else if(this->is<Object>()){
        return "Object";
    }else /*if(this->is<Function>())*/{
        return "Function";
    }
}
constexpr bool Variant::is_null()const noexcept{
    return this->is<Null>();
}
constexpr bool Variant::is_boolean()const noexcept{
    return this->is<Boolean>();
}
constexpr bool Variant::is_number()const noexcept{
    return this->is<Number>();
}
constexpr bool Variant::is_string()const noexcept{
    return this->is<String>();
}
constexpr bool Variant::is_array()const noexcept{
    return this->is<Array>();
}
constexpr bool Variant::is_object()const noexcept{
    return this->is<Object>();
}
constexpr bool Variant::is_function()const noexcept{
    return this->is<Function>();
}
constexpr Null& Variant::null(){
    return this->data<Null>();
}
constexpr Boolean& Variant::boolean(){
    return this->data<Boolean>();
}
constexpr Number& Variant::number(){
    return this->data<Number>();
}
constexpr String& Variant::string(){
    return this->data<String>();
}
constexpr Array& Variant::array(){
    return this->data<Array>();
}
constexpr Object& Variant::object(){
    return this->data<Object>();
}
constexpr Function& Variant::function(){
    return this->data<Function>();
}
constexpr Null const& Variant::const_null()const{
    return this->const_data<Null>();
}
constexpr Boolean const& Variant::const_boolean()const{
    return this->const_data<Boolean>();
}
constexpr Number const& Variant::const_number()const{
    return this->const_data<Number>();
}
constexpr String const& Variant::const_string()const{
    return this->const_data<String>();
}
constexpr Array const& Variant::const_array()const{
    return this->const_data<Array>();
}
constexpr Object const& Variant::const_object()const{
    return this->const_data<Object>();
}
constexpr Function const& Variant::const_function()const{
    return this->const_data<Function>();
}
template<typename OutputStream>
constexpr OutputStream& operator<<(
    OutputStream& os,
    typename Variant::value_type const& value
)noexcept{
    if(::std::holds_alternative<Null>(value)){
        return os<<"null";
    }else if(::std::holds_alternative<Boolean>(value)){
        return os<<(::std::get<Boolean>(value)?"true":"false");
    }else if(::std::holds_alternative<Number>(value)){
        return os<<number_to_string(::std::get<Number>(value));
    }else if(::std::holds_alternative<String>(value)){
        return os<<"\""+::std::get<String>(value)+"\"";
    }else if(::std::holds_alternative<Array>(value)){
        return os<<array_to_string(::std::get<Array>(value));
    }else if(::std::holds_alternative<Object>(value)){
        return os<<object_to_string(::std::get<Object>(value));
    }else /*Function*/{
        return os<<"function";
    }
}