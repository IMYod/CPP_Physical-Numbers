#include "Unit.h"
#include "PhysicalNumber.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

using std::istream, std::ostream, std::endl, std::istream, std::ostream, std::string,
std::cout, std::istringstream;
using namespace ariel;


PhysicalNumber::PhysicalNumber(double size, Unit unit): _size(size), _unit(unit) {;}

/*----------------------------------------------*/

const PhysicalNumber PhysicalNumber::operator +() const {
	if (this->size() >= 0)
		return PhysicalNumber(this->size(), this->unit());
	return PhysicalNumber(0-this->size(), this->unit());
}

const PhysicalNumber PhysicalNumber::operator -() const {
	if (this->size() <= 0)
		return PhysicalNumber(this->size(), this->unit());
	return PhysicalNumber(0-this->size(), this->unit());
}

/*----------------------------------------------*/

const PhysicalNumber ariel::operator +(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() + b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

const PhysicalNumber ariel::operator -(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() - b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

PhysicalNumber& PhysicalNumber::operator +=(const PhysicalNumber& b){
	if (!comparable(this->unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");	
	this->size() += b.size()*ratio(b.unit())/ratio(this->unit());
	return *this;
}

PhysicalNumber& PhysicalNumber::operator -=(const PhysicalNumber& b){
	if (!comparable(this->unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");	
	this->size() -= b.size()*ratio(b.unit())/ratio(this->unit());
	return *this;
}

/*-----------------------------------------------*/

bool ariel::operator >(const PhysicalNumber& a, const PhysicalNumber& b) {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() > ratio(b.unit())*b.size());
}

bool ariel::operator >=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() >= ratio(b.unit())*b.size());
}

bool ariel::operator <(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() < ratio(b.unit())*b.size());
}

bool ariel::operator <=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() <= ratio(b.unit())*b.size());
}

bool ariel::operator ==(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() == ratio(b.unit())*b.size());
}

bool ariel::operator !=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() != ratio(b.unit())*b.size());
}

/*-----------------------------------------------*/

ostream& ariel::operator <<(ostream& os, const PhysicalNumber& num) {
	return os << num.size() << "[" << num.unit() << "]";
}

istream& ariel::operator >> (istream& is, PhysicalNumber& num) {

	string unitString;
	char ch;
	is >> num._size >> ch >> unitString >> ch;	

/*	is >> num._size;
	is >> temp; //for [
	is >> unitString;
	is >> temp; //for ]*/

	num.unit() = unitByString(unitString);
	return is;
}

/*-----------------------------------------------*/
/*unit functions*/

double ariel::ratio(const enum ariel::Unit type){
	switch (type){
		case Unit::CM: return 1;
		case Unit::M: return 100;
		case Unit::KM: return 100000;
		case Unit::SEC: return 1;
		case Unit::MIN: return 60;
		case Unit::HOUR: return 3600;
		case Unit::G: return 1;
		case Unit::KG: return 1000;
		case Unit::TON: return 1000000;
	}
}


int getUnitID(const enum Unit type){
	switch (type){
		case Unit::CM: return 1;
		case Unit::M: return 1;
		case Unit::KM: return 1;
		case Unit::SEC: return 2;
		case Unit::MIN: return 2;
		case Unit::HOUR: return 2;
		case Unit::G: return 3;
		case Unit::KG: return 3;
		case Unit::TON: return 3;
	}
}

bool ariel::comparable(const enum ariel::Unit a, const enum ariel::Unit b){
	return (getUnitID(a) == getUnitID(b));
}

enum Unit ariel::unitByString(std::string str){
	if (!str.compare("cm]")) //the strings are equale
		return (Unit::CM);
	if (!str.compare("m]"))	
		return (Unit::M);
	if (!str.compare("km]"))	
		return (Unit::KM);
	if (!str.compare("sec]"))	
		return (Unit::SEC);
	if (!str.compare("min]"))	
		return (Unit::MIN);
	if (!str.compare("hour]"))
		return (Unit::HOUR);
	if (!str.compare("g]"))	
		return (Unit::G);
	if (!str.compare("kg]"))	
		return (Unit::KG);
	if (!str.compare("ton]"))
		return (Unit::TON);
	throw string ("Input exception");
}

inline std::ostream& operator << (std::ostream &os, const enum Unit u){
	switch (u){
		case Unit::CM: return os << "cm";
		case Unit::M: return os << "m";
		case Unit::KM: return os << "km";
		case Unit::SEC: return os << "sec";
		case Unit::MIN: return os << "min";
		case Unit::HOUR: return os << "hour";
		case Unit::G: return os << "g";
		case Unit::KG: return os << "kg";
		case Unit::TON: return os << "ton";
	}
}

/*
bool ariel::operator >(const enum Unit a, const enum Unit b){
	return (ratio(a) > ratio(b));
}
bool ariel::operator <(const enum Unit a, const enum Unit b){
	return (ratio(a) < ratio(b));
}*/
