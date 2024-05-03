#pragma once
#include<new>
#include<stack>
#include<map>
#include<iostream>
#include"is_value_type_v.hpp"
template<typename _ValueType>
class BoxManger{
public:
    static_assert(is_value_type_v<_ValueType>);
    using value_type=_ValueType;
private:
    //Object Pool And COW
    static ::std::map<value_type*,unsigned/*ref count*/> ref_object_pool_;
    static ::std::stack<value_type*> null_object_pool_;
public:
    static value_type* new_ref_object(){
        static auto auto_clear_init_flag=auto_clear_.init_flag();
        value_type* ret=nullptr; 
        if(!null_object_pool_.empty()){
            ret=null_object_pool_.top();
            new(ret)value_type{};
            ref_object_pool_[ret]=1;
            null_object_pool_.pop();
        }else{
            ret=static_cast<value_type*>(::operator new(sizeof(value_type)));
new(ret)value_type{};
            ref_object_pool_[ret]=1;
        }
        return ret;
    }
    static void delete_ref_object(value_type*& object){
        if(!object){
            return;
        }
        if(ref_object_pool_.count(object)==0){
            return;
        }
        if(ref_object_pool_[object]>1){
            --(ref_object_pool_[object]);
        }else{
object->~value_type();
            null_object_pool_.push(object);
            ref_object_pool_.erase(object);
        }
        object=nullptr;
    }
    static void copy_ref_object(value_type*& to,value_type const* from){
        if(!from){
            return;
        }
        if(to==from){
            return;
        }
        bool to_is_ref=ref_object_pool_.count(to)!=0;
        bool from_is_ref=ref_object_pool_.count(const_cast<value_type*>(from))!=0;
        if((!to_is_ref)&&(!from_is_ref)){
            if(!to){
                to=new_ref_object();
            }
            *to=*from;
            return;
        }
        if((!to_is_ref)&&from_is_ref){
            if(!to){
    to=const_cast<value_type*>(from);
                ++(ref_object_pool_[const_cast<value_type*>(from)]);
                return;
            }
            *to=*from;
            return;
        }
        if(to_is_ref&&(!from_is_ref)){
            if(ref_object_pool_[to]>1){
                --(ref_object_pool_[to]);
                to=new_ref_object();
            }
            *to=*from;
            return;
        }
        if(to_is_ref&&from_is_ref){
            delete_ref_object(to);
            to=const_cast<value_type*>(from);
            ++(ref_object_pool_[const_cast<value_type*>(from)]);
        }
    }
    static void move_ref_object(value_type*& to,value_type*& from){
        if(!from){
            return;
        }
        if(to==from){
            return;
        }
        bool to_is_ref=ref_object_pool_.count(to)!=0;
        bool from_is_ref=ref_object_pool_.count(from)!=0;
        if((!to_is_ref)&&(!from_is_ref)){
            if(!to){
                to=new_ref_object();
            }
            *to=::std::move(*from);
            from=nullptr;
            return;
        }
        if((!to_is_ref)&&from_is_ref){//has case:to==nullptr
            if(!to){
                to=from;
                from=nullptr;
                return;
            }
            *to=::std::move(*from);
            delete_ref_object(from);
            return;
        }
        if(to_is_ref&&(!from_is_ref)){
            if(ref_object_pool_[to]>1){
                --(ref_object_pool_[to]);
                to=new_ref_object();
            }
            *to=::std::move(*from);
            return;
        }
        if(to_is_ref&&from_is_ref){
            delete_ref_object(to);
            to=from;
            from=nullptr;
        }

    }
    static unsigned get_object_ref_count(value_type* object){
        if(ref_object_pool_.count(object)==0){
            return 0;
        }
        return ref_object_pool_[object];
    }
    static void clear_ref_object(){
        for(auto& pair:ref_object_pool_){
(pair.first)->~value_type();
           null_object_pool_.push(pair.first); 
        }
        ref_object_pool_.clear();
    }
    static void clear_null_object(){
        value_type* object=nullptr;
        while(!null_object_pool_.empty()){
            object=null_object_pool_.top();
            ::operator delete(object);
            null_object_pool_.pop();
        }
    }
    struct AutoClear{
        AutoClear()
        {}
        bool init_flag(){
            return true;
        }
        ~AutoClear(){
            clear_ref_object();
            clear_null_object();
            ::std::cout<<"BoxManger Auto Clear!\n";
        }
    };
    static AutoClear auto_clear_;
};
template<typename _ValueType>
::std::map<typename BoxManger<_ValueType>::value_type*,unsigned>
BoxManger<_ValueType>::ref_object_pool_={};
template<typename _ValueType>
::std::stack<typename BoxManger<_ValueType>::value_type*>
BoxManger<_ValueType>::null_object_pool_={};
template<typename _ValueType>
typename BoxManger<_ValueType>::AutoClear
BoxManger<_ValueType>::auto_clear_={};