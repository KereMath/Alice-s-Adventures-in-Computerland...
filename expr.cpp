#include "expr.h"

namespace sym 
{
    Expr::Expr(const Const& c) : expr_(&c) { }
    Expr::Expr(const Var& v) : expr_(&v) { }
    Expr::Expr(const __expr_t* e) : expr_(e) { }
    Expr::Expr(const __expr_t& e) : expr_(&e) { }
    Expr::Expr(const Expr& e) : expr_(e.expr_) { }
    
    Expr::~Expr() 
    {
}

    __expr_t* Expr::eval(const var_map_t& vars) const 
    {
        __expr_t* result = nullptr;

    if(expr_)
    {
        result = expr_->eval(vars);
    }

    return result;  
    }

    __expr_t* Expr::diff(const std::string& v) const 
    {__expr_t* result = nullptr;
        if(expr_)
        {
            result = expr_->diff(v);
        }
        return result; 
    }

    std::ostream& Expr::operator<< (std::ostream &out) const 
    {
        if(expr_)
        {
            out<<*expr_;
        }
        return out;
    }

    bool Expr::operator==(const Expr& other) const 
    {
        if(expr_){
            if(other.expr_){
                bool k= *expr_ == *other.expr_;
            return k;
        }        
        else{return 0;}
}else{
        return 0;
    }}

    bool Expr::operator==(const __expr_t& other) const 
    {bool k=0;
        if(expr_)
        {k=*expr_ == other;
            
        }
        return k;
    }
}
