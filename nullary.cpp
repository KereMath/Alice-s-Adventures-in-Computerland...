#include "type.h"
#include "nullary.h"

namespace sym 
{
	double Const::get_value() const 
	{
		return value_;
	}

	Const::operator double() const 
	{
		return value_;
	}

	bool Const::is_con() const 
	{
		return true;
	}

	__expr_t* Const::eval(const var_map_t& var_map) const 
	{
	__expr_t* result = new Const(*this);
    return result;
	}

	__expr_t* Const::diff(const std::string& v) const 
	{
    Const* result = new Const(0);
    return result;	
	    
	}

	std::ostream& Const::operator<<(std::ostream &out) const 
	{
		out << value_;
		return out;
	}

	bool Const::operator==(const __expr_t& other) const
{
    if (const Const* con = dynamic_cast<const Const*>(&other))
    {
        bool k=value_ == con->value_;
        return k;
    }
    return false;
}
}

namespace sym 
{
	std::string Var::get_variable() const 
	{
		return var_;
	}

	Var::operator std::string () const 
	{
		return var_;
	}
	
	bool Var::is_var() const 
	{
		return true;
	}

	__expr_t* Var::eval(const var_map_t& vars) const 
	{
		for (const auto& value : vars) {
        if (value.first == var_) {
            return new Const(value.second);
        }
    }
    return new Var(var_);
	}

	__expr_t* Var::diff(const std::string& v) const 
{
    Const* result;
    if (v != var_)
        result = new Const(0); 
    else {
        result = new Const(1);
    }
    return result;
}

	std::ostream& Var::operator<<(std::ostream &out) const 
	{
		out << var_;
		return out;
	}

	bool Var::operator==(const __expr_t& other) const 
	{
		const Var* com = dynamic_cast<const Var*>(&other);
		if (com){bool k= var_ == com->var_;
		
			return k;}
		else{
		return false;}
	}
}