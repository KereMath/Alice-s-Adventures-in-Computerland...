#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <memory>
#include "type.h"
#include "nullary.h"


#ifndef __SYMBOLIC__EXPRESSION_H__
#define __SYMBOLIC__EXPRESSION_H__

namespace sym 
{
    Expr::Expr(const __expr_t* e) : expr_(e) { }
    Expr::Expr(const Expr& e) : expr_(e.expr_) { } // Note: This is still a shallow copy. 

    Expr::~Expr() 
    {
        delete expr_; // Delete the __expr_t object if Expr is its owner.
    }

    __expr_t* Expr::eval(const var_map_t& vars) const 
    {
        if(expr_)
        {
            return expr_->eval(vars);
        }
        throw std::runtime_error("Attempted to evaluate null expression."); // throw an exception
    }

    __expr_t* Expr::diff(const std::string& v) const 
    {
        if(expr_)
        {
            return expr_->diff(v);
        }
        throw std::runtime_error("Attempted to differentiate null expression."); // throw an exception
    }

    std::ostream& operator<<(std::ostream &out, const Expr& e) 
    {
        if(e.expr_)
        {
            out << *(e.expr_);
        }
        return out;
    }

    bool Expr::operator==(const Expr& other) const 
    {
        if(expr_ && other.expr_)
        {
            // Assumption: We assume `__expr_t` objects are comparable using the == operator. 
            return *expr_ == *other.expr_; 
        }
        // Either one or both expressions are null. They are equal only if both are null.
        return expr_ == other.expr_;
    }
}
#endif