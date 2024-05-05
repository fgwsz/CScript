#pragma once
#include<string_view>
#include<source_location>
struct Logger{
    static void info(
        ::std::string_view const& message
        ,::std::source_location const& location
        =::std::source_location::current()
    )noexcept;
    static void error(
        ::std::string_view const& message
        ,::std::source_location const& location
        =::std::source_location::current()
    )noexcept;
};