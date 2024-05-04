#include"../Object.hpp"
constexpr Object::Object(null_t const& value)noexcept
    :data_(typename Object::value_type{value}){};
constexpr Object::Object(boolean_t const& value)noexcept
    :data_(typename Object::value_type{value}){}
constexpr Object::Object(number_t const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(string_t const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(vector_t const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(map_t const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr Object::Object(function_t const& value)noexcept
	:data_(typename Object::value_type{value}){}
constexpr bool Object::is_null()const noexcept{
    return ::std::holds_alternative<typename Object::null_t>(this->data_.const_data());
}
constexpr bool Object::is_boolean()const noexcept{
    return ::std::holds_alternative<typename Object::boolean_t>(this->data_.const_data());
}
constexpr bool Object::is_number()const noexcept{
    return ::std::holds_alternative<typename Object::number_t>(this->data_.const_data());
}
constexpr bool Object::is_string()const noexcept{
    return ::std::holds_alternative<typename Object::string_t>(this->data_.const_data());
}
constexpr bool Object::is_vector()const noexcept{
    return ::std::holds_alternative<typename Object::vector_t>(this->data_.const_data());
}
constexpr bool Object::is_map()const noexcept{
    return ::std::holds_alternative<typename Object::map_t>(this->data_.const_data());
}
constexpr bool Object::is_function()const noexcept{
    return ::std::holds_alternative<typename Object::function_t>(this->data_.const_data());
}
constexpr typename Object::null_t& Object::null(){
    return ::std::get<typename Object::null_t>(this->data_.data());
}
constexpr typename Object::boolean_t& Object::boolean(){
    return ::std::get<typename Object::boolean_t>(this->data_.data());
}
constexpr typename Object::number_t& Object::number(){
    return ::std::get<typename Object::number_t>(this->data_.data());
}
constexpr typename Object::string_t& Object::string(){
    return ::std::get<typename Object::string_t>(this->data_.data());
}
constexpr typename Object::vector_t& Object::vector(){
    return ::std::get<typename Object::vector_t>(this->data_.data());
}
constexpr typename Object::map_t& Object::map(){
    return ::std::get<typename Object::map_t>(this->data_.data());
}
constexpr typename Object::function_t& Object::function(){
    return ::std::get<typename Object::function_t>(this->data_.data());
}
constexpr typename Object::null_t const& Object:: Object::const_null()const{
    return ::std::get<typename Object::null_t>(this->data_.const_data());
}
constexpr typename Object::boolean_t const& Object:: Object::const_boolean()const{
    return ::std::get<typename Object::boolean_t>(this->data_.const_data());
}
constexpr typename Object::number_t const& Object:: Object::const_number()const{
    return ::std::get<typename Object::number_t>(this->data_.const_data());
}
constexpr typename Object::string_t const& Object:: Object::const_string()const{
    return ::std::get<typename Object::string_t>(this->data_.const_data());
}
constexpr typename Object::vector_t const& Object:: Object::const_vector()const{
    return ::std::get<typename Object::vector_t>(this->data_.const_data());
}
constexpr typename Object::map_t const& Object:: Object::const_map()const{
    return ::std::get<typename Object::map_t>(this->data_.const_data());
}
constexpr typename Object::function_t const& Object:: Object::const_function()const{
    return ::std::get<typename Object::function_t>(this->data_.const_data());
}