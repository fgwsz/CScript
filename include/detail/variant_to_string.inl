#pragma once
#include"variant_to_string.hpp"
#include<limits>//::std::numeric_limits
#include<string>//::std::string ::std::to_string
#include"Variant.hpp"
::std::string variant_to_string(Variant variant,int tab_count)noexcept{
    if(variant.is_null()){
        return "null";
    }else if(variant.is_boolean()){
        return variant.const_boolean()?"true":"false";
    }else if(variant.is_number()){
        return number_to_string(variant.const_number());
    }else if(variant.is_string()){
        return "\""+variant.const_string()+"\"";
    }else if(variant.is_array()){
        return array_to_string(variant.const_array(),tab_count);
    }else if(variant.is_object()){
        return object_to_string(variant.const_object(),tab_count);
    }else /*if(variant.is_function())*/{
        return "function";
    }
}
::std::string number_to_string(double number)noexcept{
    if(
        number>::std::numeric_limits<unsigned long long>::max() ||
        number<::std::numeric_limits<long long>::min()
    ){
        return ::std::to_string(number);
    }
    if(number>=0){
        if(
            static_cast<double>(
                static_cast<unsigned long long>(number)
            )==number
        ){
            return ::std::to_string(static_cast<unsigned long long>(number));
        }else{
            return ::std::to_string(number);
        }
    }else{
        if(
            static_cast<double>(
                static_cast<long long>(number)
            )==number
        ){
            return ::std::to_string(static_cast<long long>(number));
        }else{
            return ::std::to_string(number);
        }
    }
}
::std::string array_to_string(Array const& array,int tab_count)noexcept{
        ::std::string ret="[";
        if(array.size()>0){
            ret+="\n";
        }
        for(auto const& element:array){
            ret+=
                ::std::string(tab_count+1,'\t')
                +variant_to_string(element,tab_count+1)
                +",\n";
        }
        if(array.size()>0){
            ret.pop_back();//\n
            ret.pop_back();//,
            ret+="\n";
        }
        return ret+=::std::string(tab_count,'\t')+"]";
}
::std::string object_to_string(Object const& object,int tab_count)noexcept{
    ::std::string ret="{";
    if(object.size()>0){
        ret+="\n";
    }
    for(auto const& pair:object){
        ret+=
            ::std::string(tab_count+1,'\t')
            +"\""+pair.first+"\":"+variant_to_string(pair.second,tab_count+1)+",\n";
    }
    if(ret.length()>0){
        ret.pop_back();//\n
        ret.pop_back();//,
        ret+="\n";
    }
    return ret+=::std::string(tab_count,'\t')+"}";
}