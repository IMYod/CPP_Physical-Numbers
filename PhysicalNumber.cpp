#include "PhysicalNumber.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using std::istream, std::ostream, std::endl, std::istream, std::ostream;
using namespace ariel;


PhysicalNumber::PhysicalNumber(double size, Unit unit): _size(size), _unit(unit) {;}

PhysicalNumber operator +(const PhysicalNumber& a, const PhysicalNumber& b)
{return PhysicalNumber(1, Unit::KM);}
PhysicalNumber operator -(const PhysicalNumber& a, const PhysicalNumber& b)
{return PhysicalNumber(1, Unit::KM);}

bool operator >(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator >=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator <(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator <=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator ==(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator !=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}

ostream& operator <<(ostream& os, const PhysicalNumber& num) {return os;}
istream& operator >>(istream& is, const PhysicalNumber& num) {return is;}
