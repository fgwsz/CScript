#pragma once
#include<initializer_list>
#include<type_traits>
#include<variant>
#include"VariantType.hpp"
#include"FunctorType.hpp"
#include"Box.hpp"
class Variant final{
public:
    constexpr Variant(Null     const& value={})noexcept;
    constexpr Variant(Boolean  const& value)noexcept;
    constexpr Variant(Number   const& value)noexcept;
    constexpr Variant(String   const& value)noexcept;
    constexpr Variant(Array    const& value)noexcept;
    constexpr Variant(Object   const& value)noexcept;
    constexpr Variant(Function const& value)noexcept;

    template<VariantType Type>
    constexpr bool is()const noexcept;
    template<VariantType Type>
    constexpr Type& data();
    template<VariantType Type>
    constexpr Type const& const_data()const;

    constexpr bool is_null    ()const noexcept;
    constexpr bool is_boolean ()const noexcept;
    constexpr bool is_number  ()const noexcept;
    constexpr bool is_string  ()const noexcept;
    constexpr bool is_array   ()const noexcept;
    constexpr bool is_object  ()const noexcept;
    constexpr bool is_function()const noexcept;

    constexpr Null    & null    ();
    constexpr Boolean & boolean ();
    constexpr Number  & number  ();
    constexpr String  & string  ();
    constexpr Array   & array   ();
    constexpr Object  & object  ();
    constexpr Function& function();

    constexpr Null     const& const_null    ()const;
    constexpr Boolean  const& const_boolean ()const;
    constexpr Number   const& const_number  ()const;
    constexpr String   const& const_string  ()const;
    constexpr Array    const& const_array   ()const;
    constexpr Object   const& const_object  ()const;
    constexpr Function const& const_function()const;

    //literal
    constexpr Variant(short value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(int value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(long value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(long long value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(unsigned short value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(unsigned int value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(unsigned long value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(unsigned long long value)noexcept
        :Variant(static_cast<Number>(value)){}
    constexpr Variant(char const* value)noexcept
        :Variant(String{value}){};
    template<unsigned long long n>
    constexpr Variant(char const(&value)[n])noexcept
        :Variant(String{value}){};
    constexpr Variant(char value)noexcept
        :Variant(String{value}){};
    constexpr Variant(::std::initializer_list<Variant> const& value)noexcept
        :Variant(Array{value}){};
    inline Variant(::std::initializer_list<typename Object::value_type> const& value)noexcept
        :Variant(Object{value}){};
    template<typename FunctionType>
        requires ::std::is_function_v<FunctionType>
    constexpr Variant(FunctionType* value)noexcept
        :Variant(Function{value}){};
    template<FunctorType Type>
    constexpr Variant(Type const& value)noexcept
        :Variant(Function{value}){};

    using value_type=::std::variant<
        Null,Boolean,Number,String,Array,Object,Function
    >;
private:
    Box<value_type> data_;
};
#include"detail/Variant.inl"