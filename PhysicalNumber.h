#pragma once
#include "Unit.h"
#include <iostream>

namespace ariel{

class PhysicalNumber{
  private:
	Unit _unit;
	double _size;

	double& size() { return _size;}
	Unit& unit() { return _unit;}

  public:
	PhysicalNumber(double size, Unit unit);

	double size() const{ return _size;}
	Unit unit() const{ return _unit;}

	friend PhysicalNumber operator +(const PhysicalNumber& a, const PhysicalNumber& b);
	friend PhysicalNumber operator -(const PhysicalNumber& a, const PhysicalNumber& b);

	PhysicalNumber& operator +=(const PhysicalNumber other){
		*this = (*this + other);	
		return *this;
	}
	PhysicalNumber& operator -=(const PhysicalNumber other){
		*this = (*this - other);
		return *this;
	}
	
	const PhysicalNumber& operator +() const {return *this;}
	const PhysicalNumber& operator -() const {return *this;}

	PhysicalNumber& operator =(const PhysicalNumber other){ //as default operator
		unit() = other.unit();
		size() = other.size();
		return *this;
	}

	friend bool operator >(const PhysicalNumber& a, const PhysicalNumber& b);
	friend bool operator >=(const PhysicalNumber& a, const PhysicalNumber& b);
	friend bool operator <(const PhysicalNumber& a, const PhysicalNumber& b);
	friend bool operator <=(const PhysicalNumber& a, const PhysicalNumber& b);
	friend bool operator ==(const PhysicalNumber& a, const PhysicalNumber& b);
	friend bool operator !=(const PhysicalNumber& a, const PhysicalNumber& b);

	PhysicalNumber& operator++() {
		_size++;
		return *this;
	}

	const PhysicalNumber operator++(int dummy_flag)  {
		PhysicalNumber copy = *this;
		_size++;
		return copy;
	}

	friend std::ostream& operator <<(std::ostream& os, const PhysicalNumber& num);
	friend std::istream& operator >>(std::istream& is, const PhysicalNumber& num);

};

}
