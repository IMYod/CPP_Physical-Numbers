/*
* This is a hpp file for the Physical-Numbers assignment.
* In this assignment we will focus on the three dimensions of Newtonian physics: length, time, and mass, and in the following units:
* 1. Length - meters (m) kilometers (km) centimeters (cm).
* 2. Time (sec) minute (min) hour (hour).
* 3. mass - grams (g) kg (kg) ton (ton).
*
* link https://github.com/erelsgl/ariel-cpp-5779/blob/master/04-const-friend-operators/homework/readme.pdf
* @author Yoav and Elad.
*/

#ifndef PHYSICALNUMBER_H
#define PHYSICALNUMBER_H

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
	
	/*******************************************************/
	/**** overloading opertors for physical numbers *******/
	/*****************************************************/
	
	friend const PhysicalNumber operator +(const PhysicalNumber&, const PhysicalNumber&);
	friend const PhysicalNumber operator -(const PhysicalNumber&, const PhysicalNumber&);

	PhysicalNumber& operator +=(const PhysicalNumber&);
	PhysicalNumber& operator -=(const PhysicalNumber&);
	
	const PhysicalNumber& operator +() const {return *this;}
	const PhysicalNumber& operator -() const {return *this;}

	PhysicalNumber& operator =(const PhysicalNumber other){ //as default operator
		unit() = other.unit();
		size() = other.size();
		return *this;
	}
	
	friend bool operator >(const PhysicalNumber&, const PhysicalNumber&);
	friend bool operator >=(const PhysicalNumber&, const PhysicalNumber&);
	friend bool operator <(const PhysicalNumber&, const PhysicalNumber&);
	friend bool operator <=(const PhysicalNumber&, const PhysicalNumber&);
	friend bool operator ==(const PhysicalNumber&, const PhysicalNumber&);
	friend bool operator !=(const PhysicalNumber&, const PhysicalNumber&);

	PhysicalNumber& operator++() {
		_size++;
		return *this;
	}

	const PhysicalNumber operator++(int dummy_flag)  {
		PhysicalNumber copy = *this;
		_size++;
		return copy;
	}

	friend std::ostream& operator <<(std::ostream&, const PhysicalNumber&);
	friend std::istream& operator >>(std::istream&, PhysicalNumber&);
};

}

#endif
