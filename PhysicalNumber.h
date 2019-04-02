#pragma once
#include "Unit.h"

namespace ariel{

class PhysicalNumber{
  private:
	Unit _unit;
	double _size;

  public:
	PhysicalNumber(double size, Unit unit);

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
	
	PhysicalNumber& operator +() const;
	PhysicalNumber& operator -() const;

	PhysicalNumber& operator =(const PhysicalNumber other){
		return *this;
	}

	//bool operator >(const PhysicalNumber& other);
	bool operator >=(const PhysicalNumber& other);
	bool operator <(const PhysicalNumber& other);
	bool operator <=(const PhysicalNumber& other);
	bool operator ==(const PhysicalNumber& other);
	bool operator !=(const PhysicalNumber& other);

	PhysicalNumber& operator++() {return *this;}
	PhysicalNumber& operator++(int dummy_flag)  {return *this;}

	friend std::ostream& operator <<(std::ostream& os, const PhysicalNumber& num);
	friend std::istream& operator >>(std::istream& is, const PhysicalNumber& num);

};

}
