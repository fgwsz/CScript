#pragma once
#include"Object.hpp"
static ::std::string object_to_string(Object object)noexcept{
    if(object.is_null()){
        return "null";
    }else if(object.is_boolean()){
        return object.const_boolean()?"true":"false";
    }else if(object.is_number()){
        return ::std::to_string(object.const_number());
    }else if(object.is_string()){
        return "\""+object.const_string()+"\"";
    }else if(object.is_vector()){
        ::std::string ret="[";
        for(auto const& element:object.const_vector()){
            ret+=object_to_string(element)+",";
        }
        if(ret.length()>1){
            ret.pop_back();
        }
        return ret+="]";
    }else if(object.is_map()){
        ::std::string ret="{";
        for(auto const& pair:object.const_map()){
            ret+="\""+pair.first+"\":"+object_to_string(pair.second)+",";
        }
        if(ret.length()>1){
            ret.pop_back();
        }
        return ret+="}";
    }else /*if(object.is_function())*/{
        return "function";
    }
}