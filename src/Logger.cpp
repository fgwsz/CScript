#include"Logger.hpp"
#include<chrono>//::std::chrono
#include<iostream>//::std::cout
namespace detail{
void logger_logln(
    ::std::string_view const& head
    ,::std::string_view const& message
    ,::std::source_location const& location
){
    auto now=::std::chrono::system_clock::now();
    ::std::time_t now_time_t
        =::std::chrono::system_clock::to_time_t(now);
    auto ms
        =::std::chrono::duration_cast<::std::chrono::milliseconds>(
            now.time_since_epoch()
        )%1000;
    char time_str[100];
    ::std::strftime(
        time_str,sizeof(time_str)
        ,"%Y-%m-%d %H:%M:%S"
        ,::std::localtime(&now_time_t)
    );
    ::std::cout
        <<"\n================================================="
        <<"\n["<<head<<"]"
        <<"\n================================================="
        <<"\n[TIME] "<<time_str<<"."<<ms.count()
        <<"\n[FILE] "<<location.file_name()
            <<"("<<location.line()<<":"<<location.column()<<")"
        //<<"\n[FUNCTION] "<<location.function_name()
        <<"\n[MESSAGE] \n"
        <<message
        <<"\n================================================="
        <<"\n";
}
}//namespace detail
void Logger::info(
    ::std::string_view const& message
    ,::std::source_location const& location
)noexcept{
    detail::logger_logln("INFO",message,location);
}
void Logger::error(
    ::std::string_view const& message
    ,::std::source_location const& location
)noexcept{
    detail::logger_logln("ERROR",message,location);
}