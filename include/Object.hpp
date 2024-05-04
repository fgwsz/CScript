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
template<typename Type>
concept ObjectType=
        ::std::is_same_v<Type,Null>    ||
        ::std::is_same_v<Type,Boolean> ||
        ::std::is_same_v<Type,Number>  ||
        ::std::is_same_v<Type,String>  ||
        ::std::is_same_v<Type,Vector>  ||
        ::std::is_same_v<Type,Map>     ||
        ::std::is_same_v<Type,Function>;

class Object final{
public:
    constexpr Object(Null     const& value={})noexcept;
    constexpr Object(Boolean  const& value)noexcept;
    constexpr Object(Number   const& value)noexcept;
    constexpr Object(String   const& value)noexcept;
    constexpr Object(Vector   const& value)noexcept;
    constexpr Object(Map      const& value)noexcept;
    constexpr Object(Function const& value)noexcept;

    template<ObjectType Type>
    constexpr bool is()const noexcept;
    template<ObjectType Type>
    constexpr Type& data();
    template<ObjectType Type>
    constexpr Type const& const_data()const;

    constexpr bool is_null    ()const noexcept;
    constexpr bool is_boolean ()const noexcept;
    constexpr bool is_number  ()const noexcept;
    constexpr bool is_string  ()const noexcept;
    constexpr bool is_vector  ()const noexcept;
    constexpr bool is_map     ()const noexcept;
    constexpr bool is_function()const noexcept;

    constexpr Null    & null    ();
    constexpr Boolean & boolean ();
    constexpr Number  & number  ();
    constexpr String  & string  ();
    constexpr Vector  & vector  ();
    constexpr Map     & map     ();
    constexpr Function& function();

    constexpr Null     const& const_null    ()const;
    constexpr Boolean  const& const_boolean ()const;
    constexpr Number   const& const_number  ()const;
    constexpr String   const& const_string  ()const;
    constexpr Vector   const& const_vector  ()const;
    constexpr Map      const& const_map     ()const;
    constexpr Function const& const_function()const;

    //literal
    constexpr Object(short value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(int value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(long value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(long long value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(unsigned short value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(unsigned int value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(unsigned long value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(unsigned long long value)noexcept
        :Object(static_cast<Number>(value)){}
    constexpr Object(char const* value)noexcept
        :Object(String{value}){};
    template<unsigned long long n>
    constexpr Object(char const(&value)[n])noexcept
        :Object(String{value}){};
    constexpr Object(char value)noexcept
        :Object(String{value}){};
    constexpr Object(::std::initializer_list<Object> const& value)noexcept
        :Object(Vector{value}){};
    inline Object(::std::initializer_list<typename Map::value_type> const& value)noexcept
        :Object(Map{value}){};
    template<typename FunctionType>
        requires ::std::is_function_v<FunctionType>
    constexpr Object(FunctionType* value)noexcept
        :Object(Function{value}){};
    template<typename FunctorType>
        requires requires{ {::std::remove_cvref_t<FunctorType>::operator()};}
    constexpr Object(FunctorType const& value)noexcept
        :Object(Function{value}){};
private:
    using value_type=::std::variant<
        Null,Boolean,Number,String,Vector,Map,Function
    >;
    Box<value_type> data_;
};
#include"detail/Object.inl"