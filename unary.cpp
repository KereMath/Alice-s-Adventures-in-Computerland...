#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
    bool NegOp::is_neg() const { 
        return true; 
    }

    __expr_t* NegOp::eval(const var_map_t& vars) const { 
    __expr_t* evaluatedOperand = this->operand->eval(vars);
    const Const* constantOperand = dynamic_cast<const Const*>(evaluatedOperand);

    if(!constantOperand) {
        evaluatedOperand = new NegOp(evaluatedOperand);
        
            return evaluatedOperand;

    } else {
        double negativeConstant = -constantOperand->get_value();
        delete evaluatedOperand;
        evaluatedOperand = new Const(negativeConstant);
            return evaluatedOperand;

    }

}


    __expr_t* NegOp::diff(const std::string& v) const { 
    __expr_t* operandDiff = operand->diff(v);
    __expr_t* negatedDiff = new NegOp(operandDiff);
    return negatedDiff;
}


std::ostream& NegOp::operator<< (std::ostream &out) const
{
    out << "-";
    if (!dynamic_cast<Const*>(const_cast<__expr_t*>(operand))) {
        if(!dynamic_cast<Var*>(const_cast<__expr_t*>(operand))){
        out << "(";
        out << *operand;
        out << ")";
        return out;}
        else{out << *operand;
        return out;}
    }
    else{
    out << *operand;
        return out;
    }}


    bool NegOp::operator==(const __expr_t& other_) const { 
        const NegOp* op = dynamic_cast<const NegOp*>(&other_);
        if(op) {
            bool k=*operand == *op->operand;
            return k;
        }
        return false;
    }
}

namespace sym 
{
    bool ExpOp::is_exp() const { 
        return true; 
    }

    __expr_t* ExpOp::eval(const var_map_t& vars) const { 
    __expr_t* evaluatedOperand = this->operand->eval(vars);
    const Const* constantOperand = dynamic_cast<const Const*>(evaluatedOperand);

    if(!constantOperand) {
        evaluatedOperand = new ExpOp(evaluatedOperand);
        return evaluatedOperand;

    } else {
        double expConstant = std::exp(constantOperand->get_value());
        delete evaluatedOperand;
        evaluatedOperand = new Const(expConstant);
        return evaluatedOperand;

    }
}


   __expr_t* ExpOp::diff(const std::string& v) const { 
    __expr_t* op_diff = operand->diff(v);
Const* op_diff_const = dynamic_cast<Const*>(op_diff);
if (!(op_diff_const && op_diff_const->get_value() == 0)) {
    
    MulOp* mulOp = new MulOp(op_diff, new ExpOp(operand));
return mulOp;
}
else{delete op_diff;
    return new Const(0);}

}


    std::ostream& ExpOp::operator<< (std::ostream &out) const {
    Var* operand_is_var = dynamic_cast<Var*>(const_cast<__expr_t*>(operand));
    Const* operand_is_const = dynamic_cast<Const*>(const_cast<__expr_t*>(operand));

    out << "e^";
    if (operand_is_var) {
        out << *operand_is_var;
    } else if (operand_is_const) {
        out << *operand_is_const;
    } else {
        if (!dynamic_cast<Const*>(const_cast<__expr_t*>(operand))) {
            if(!dynamic_cast<Var*>(const_cast<__expr_t*>(operand))){
            out << "(";
                out << *operand;
                out << ")";
                return out;
           }
            else{out << *operand;}
        }
        else{out << *operand;
            return out;
        }
        }
    }



    bool ExpOp::operator==(const __expr_t& other_) const { 
        const ExpOp* expo = dynamic_cast<const ExpOp*>(&other_);
        if(expo) {
            bool k=*operand == *expo->operand;
            return k;
        }
        return false;
    }
}
