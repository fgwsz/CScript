#pragma once
#include"ValueType.hpp"
::std::string number_to_string(double number)noexcept;
::std::string array_to_string(Array const& array,int tab_count=0)noexcept;
::std::string object_to_string(Object const& object,int tab_count=0)noexcept;
::std::string variant_to_string(Variant variant,int tab_count=0)noexcept;
#include"detail/variant_to_string.inl"