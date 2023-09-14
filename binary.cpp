#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
    bool AddOp::is_add() const { return true; }
    
    __expr_t* AddOp::eval(const var_map_t& vars) const 
{
    __expr_t* lhs_result = lhs_->eval(vars);
    __expr_t* rhs_result = rhs_->eval(vars);

    Const* lhs_const = dynamic_cast<Const*>(lhs_result);
    Const* rhs_const = dynamic_cast<Const*>(rhs_result);

    if (lhs_const ) {
        if(rhs_const->get_value() == 0){
            delete rhs_result; 
        return lhs_result;
        
    }
        double sum = lhs_const->get_value() + rhs_const->get_value();
        delete lhs_result;
        delete rhs_result;
        return new Const(sum);
    }
    else if(rhs_const->get_value() == 0){
        delete rhs_result; 
        return lhs_result;
    }
    
    else {
        return new AddOp(lhs_, rhs_); 
    }
}


    __expr_t* AddOp::diff(const std::string& v) const 
{
    __expr_t* lhs_diff = lhs_->diff(v);
    __expr_t* rhs_diff = rhs_->diff(v);
    if (lhs_diff == nullptr) {
    if (rhs_diff == nullptr) {
        return new Const(0); 
    } else {
        Const* rhs_diff_const = dynamic_cast<Const*>(rhs_diff);
        if (rhs_diff_const) {
            if (rhs_diff_const->get_value() == 0) {
                return new Const(0); 
            }
        }
    }
} else {
    Const* lhs_diff_const = dynamic_cast<Const*>(lhs_diff);
    if (lhs_diff_const) {
        if (lhs_diff_const->get_value() == 0) {
            if (rhs_diff == nullptr) {
                return new Const(0); 
            } else {
                Const* rhs_diff_const = dynamic_cast<Const*>(rhs_diff);
                if (rhs_diff_const) {
                    if (rhs_diff_const->get_value() == 0) {
                        return new Const(0); 
                    }
                }
            }
        }
    }
}

if (lhs_diff == nullptr) {
    return rhs_diff;
} else {
    Const* lhs_diff_const = dynamic_cast<Const*>(lhs_diff);
    if (lhs_diff_const) {
        if (lhs_diff_const->get_value() == 0) {
            return rhs_diff;
        }
    }
}

if (rhs_diff == nullptr) {
    return lhs_diff;
} else {
    Const* rhs_diff_const = dynamic_cast<Const*>(rhs_diff);
    if (rhs_diff_const) {
        if (rhs_diff_const->get_value() == 0) {
            return lhs_diff;
        }
    }
}

    return new AddOp(lhs_diff, rhs_diff);
}

std::ostream& AddOp::operator<< (std::ostream &out) const 
{
    bool lhs_is_non_nullary = !(dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_)) || dynamic_cast<Var*>(const_cast<__expr_t*>(lhs_)));
    bool rhs_is_non_nullary = !(dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_)) || dynamic_cast<Var*>(const_cast<__expr_t*>(rhs_)));
 bool lhs_is_const = dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_));
    bool rhs_is_const = dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_));
    bool lhs_is_var = dynamic_cast<Var*>(const_cast<__expr_t*>(lhs_));
    bool rhs_is_var = dynamic_cast<Var*>(const_cast<__expr_t*>(rhs_));

    if (lhs_is_const && rhs_is_const) {
        Const* lhs_const = dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_));
        Const* rhs_const = dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_));
        if (lhs_const && lhs_const->get_value() == 0 &&  rhs_const->get_value() == 0) {
            return out;
        }
        if (lhs_const->get_value() == 0) {
        } else {
            if (lhs_is_non_nullary) {
                out << "(";
            }
            out << *lhs_;
            if (lhs_is_non_nullary) {
                out << ")";
            }
        }
        if ( rhs_const->get_value() == 0) {
        } else {
            if (!(lhs_const && lhs_const->get_value() == 0)) {
                out << " + ";
            }
            if (rhs_is_non_nullary) {
                out << "(";
            }
            out << *rhs_;
            if (rhs_is_non_nullary) {
                out << ")";
            }
        }
    } else if (lhs_is_var && rhs_is_var) {
        out << *lhs_ << " + " << *rhs_;
    } else {
    if (lhs_is_const) {
        Const* const_lhs = dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_));
        if (const_lhs != nullptr) {
            if (const_lhs->get_value() != 0) {
                if (lhs_is_non_nullary) {
                    out << "(";
                }
                out << *lhs_;
                if (lhs_is_non_nullary) {
                    out << ")";
                }
                out << " + ";
            }
        }
    }
    else {
        if (lhs_is_non_nullary) {
            out << "(";
        }
        out << *lhs_;
        if (lhs_is_non_nullary) {
            out << ")";
        }
        out << " + ";
    }

    if (rhs_is_const) {
        Const* const_rhs = dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_));
        if (const_rhs != nullptr) {
            if (const_rhs->get_value() != 0) {
                if (rhs_is_non_nullary) {
                    out << "(";
                }
                out << *rhs_;
                if (rhs_is_non_nullary) {
                    out << ")";
                }
            }
        }
    }
    else {
        if (rhs_is_non_nullary) {
            out << "(";
        }
        out << *rhs_;
        if (rhs_is_non_nullary) {
            out << ")";
        }
    }
}

    return out;
}




    bool AddOp::operator==(const __expr_t& other_) const 
    {bool k=false;
        const AddOp* addOther = dynamic_cast<const AddOp*>(&other_);
        if(addOther)
        {
            k= *lhs_ == *addOther->lhs_ && *rhs_ == *addOther->rhs_;
        }
        return k;
    }

    bool MulOp::is_mul() const { return true; }

   __expr_t* MulOp::eval(const var_map_t& vars) const {
    __expr_t* lhs_result = lhs_->eval(vars);
    __expr_t* rhs_result = rhs_->eval(vars);

    Const* lhs_const = dynamic_cast<Const*>(lhs_result);
    Const* rhs_const = dynamic_cast<Const*>(rhs_result);

    if (lhs_const) {
        if (rhs_const) {
            double product = lhs_const->get_value() * rhs_const->get_value();
            delete lhs_result;
            delete rhs_result;
            return new Const(product);
        }
        else if (lhs_const->get_value() == 0) {
            delete lhs_result;
            delete rhs_result;
            return new Const(0);
        }
        else if (lhs_const->get_value() == 1) {
            delete lhs_result;
            return rhs_result;
        }
    }
    else if (rhs_const) {
        if (rhs_const->get_value() == 0) {
            delete lhs_result;
            delete rhs_result;
            return new Const(0);
        }
        else if (rhs_const->get_value() == 1) {
            delete rhs_result;
            return lhs_result;
        }
    }

    return new MulOp(lhs_, rhs_);
}

__expr_t* MulOp::diff(const std::string& v) const {
    __expr_t* lhs_diff = lhs_->diff(v);
    __expr_t* rhs_diff = rhs_->diff(v);

    __expr_t* lhs_mul_rhs_diff = new MulOp(lhs_diff, rhs_);
    __expr_t* rhs_mul_lhs_diff = new MulOp(lhs_, rhs_diff);

    if (lhs_diff == nullptr || dynamic_cast<Const*>(lhs_diff)->get_value() == 0) {
        if (rhs_diff == nullptr || dynamic_cast<Const*>(rhs_diff)->get_value() == 0) {
            return new Const(0);
        } else {
            return rhs_mul_lhs_diff;
        }
    } else {
        if (rhs_diff == nullptr ||  dynamic_cast<Const*>(rhs_diff)->get_value() == 0) {
            return lhs_mul_rhs_diff;
        } else {
            return new AddOp(lhs_mul_rhs_diff, rhs_mul_lhs_diff);
        }
    }
}


std::ostream& MulOp::operator<< (std::ostream &out) const 
{    bool lhs_is_non_nullary = !(dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_)) || dynamic_cast<Var*>(const_cast<__expr_t*>(lhs_)));
    bool rhs_is_non_nullary = !(dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_)) || dynamic_cast<Var*>(const_cast<__expr_t*>(rhs_)));

    Const* lhs_const = dynamic_cast<Const*>(const_cast<__expr_t*>(lhs_));
                    Const* rhs_const = dynamic_cast<Const*>(const_cast<__expr_t*>(rhs_));

    if(lhs_const && lhs_const->get_value() == 0 ||rhs_const && rhs_const->get_value() == 0 ) {}
    else if(lhs_const && lhs_const->get_value() == -0 ||rhs_const && rhs_const->get_value() == -0 ) {}
    else{

                if(lhs_const && lhs_const->get_value() == 1) {
                } else {
                    if(lhs_is_non_nullary) {
                        out << "(";
                    }
                    out << *lhs_;
                    if(lhs_is_non_nullary) {
                        out << ")";
                    }
                }
            
                if(rhs_const && rhs_const->get_value() == 1) {
                } else {
                    if(!(lhs_const && lhs_const->get_value() == 1)) {
                        out << " * ";
                    }
                    if(rhs_is_non_nullary) {
                        out << "(";
                    }
                    out << *rhs_;
                    if(rhs_is_non_nullary) {
                        out << ")";
                    }
                }
}
    return out;
}


    bool MulOp::operator==(const __expr_t& other_) const 
    {bool k=false;
        const MulOp* mulOther = dynamic_cast<const MulOp*>(&other_);
        if(mulOther)
        {
            k= *lhs_ == *mulOther->lhs_ && *rhs_ == *mulOther->rhs_;
        }
        return k;
    }
}
