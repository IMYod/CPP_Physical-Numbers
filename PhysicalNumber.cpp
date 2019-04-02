#include "PhysicalNumber.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using std::istream, std::ostream, std::endl, std::istream, std::ostream;
using namespace ariel;


PhysicalNumber::PhysicalNumber(double size, Unit unit): _size(size), _unit(unit) {;}

----------------------------------------------

PhysicalNumber operator +(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() + b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

PhysicalNumber operator -(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() - b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

-----------------------------------------------

bool operator >(const PhysicalNumber& a, const PhysicalNumber& b) {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() > ratio(b.unit())*b.size());
}

bool operator >=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() >= ratio(b.unit())*b.size());
}

bool operator <(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() < ratio(b.unit())*b.size());
}

bool operator <=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() <= ratio(b.unit())*b.size());
}

bool operator ==(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() == ratio(b.unit())*b.size());
}

bool operator !=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() != ratio(b.unit())*b.size());
}

-----------------------------------------------

ostream& operator <<(ostream& os, const PhysicalNumber& num) {
	return os << num.size() << "[" << num.unit() << "]";
}

istream& operator >>(istream& is, PhysicalNumber& num) {
	char temp;
	string unitString;
	ls >> num._size;
	ls >> temp; //for [
	ls >> unitString;
	ls >> temp; //for ]
	num._unit = unitByString(unitString);
	return is;
}


