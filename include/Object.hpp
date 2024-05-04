#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<functional>
#include<initializer_list>
#include<type_traits>
#include<variant>
#include"Box.hpp"
struct Null final{};
using Boolean=bool;
using Number=double;
using String=::std::string;
class Object;
using Vector=::std::vector<Object>;
using Map=::std::unordered_map<String,Object>;
using Function=::std::function<Object(Object)>;
class Object final{
public:
    using null_t    =Null;
    using boolean_t =Boolean;
    using number_t  =Number;
    using string_t  =String;
    using vector_t  =Vector;
    using map_t     =Map;
    using function_t=Function;

    constexpr Object(null_t     const& value={})noexcept;
    constexpr Object(boolean_t  const& value)noexcept;
    constexpr Object(number_t   const& value)noexcept;
    constexpr Object(string_t   const& value)noexcept;
    constexpr Object(vector_t   const& value)noexcept;
    constexpr Object(map_t      const& value)noexcept;
    constexpr Object(function_t const& value)noexcept;

    constexpr bool is_null    ()const noexcept;
    constexpr bool is_boolean ()const noexcept;
    constexpr bool is_number  ()const noexcept;
    constexpr bool is_string  ()const noexcept;
    constexpr bool is_vector  ()const noexcept;
    constexpr bool is_map     ()const noexcept;
    constexpr bool is_function()const noexcept;

    constexpr null_t    & null    ();
    constexpr boolean_t & boolean ();
    constexpr number_t  & number  ();
    constexpr string_t  & string  ();
    constexpr vector_t  & vector  ();
    constexpr map_t     & map     ();
    constexpr function_t& function();

    constexpr null_t     const& const_null    ()const;
    constexpr boolean_t  const& const_boolean ()const;
    constexpr number_t   const& const_number  ()const;
    constexpr string_t   const& const_string  ()const;
    constexpr vector_t   const& const_vector  ()const;
    constexpr map_t      const& const_map     ()const;
    constexpr function_t const& const_function()const;

    //literal
    constexpr Object(short value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(int value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(long value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(long long value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(unsigned short value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(unsigned int value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(unsigned long value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(unsigned long long value)noexcept
        :Object(static_cast<number_t>(value)){}
    constexpr Object(char const* value)noexcept
        :Object(string_t{value}){};
    template<unsigned long long n>
    constexpr Object(char const(&value)[n])noexcept
        :Object(string_t{value}){};
    constexpr Object(char value)noexcept
        :Object(string_t{value}){};
    constexpr Object(::std::initializer_list<Object> const& value)noexcept
        :Object(vector_t{value}){};
    inline Object(::std::initializer_list<typename map_t::value_type> const& value)noexcept
        :Object(map_t{value}){};
    template<typename FunctionType>
        requires ::std::is_function_v<FunctionType>
    constexpr Object(FunctionType* value)noexcept
        :Object(function_t{value}){};
    template<typename FunctorType>
        requires requires{ {::std::remove_cvref_t<FunctorType>::operator()};}
    constexpr Object(FunctorType const& value)noexcept
        :Object(function_t{value}){};
private:
    using value_type=::std::variant<
        null_t,boolean_t,number_t,string_t,vector_t,map_t,function_t
    >;
    Box<value_type> data_;
};
#include"detail/Object.inl"