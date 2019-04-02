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
	if (a.unit() < b.unit() )
		return PhysicalNumber(a.size() + b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
	else
		return PhysicalNumber(b.size() + a.size()*ratio(a.unit())/ratio(b.unit()), b.unit());
}

PhysicalNumber operator -(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	if (a.unit() < b.unit() )
		return PhysicalNumber(a.size() - b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
	else
		return PhysicalNumber(b.size() - a.size()*ratio(a.unit())/ratio(b.unit()), b.unit());
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

ostream& operator <<(ostream& os, const PhysicalNumber& num) {return os;}
istream& operator >>(istream& is, const PhysicalNumber& num) {return is;}
