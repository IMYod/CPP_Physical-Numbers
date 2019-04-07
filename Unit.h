#ifndef UNIT_H
#define UNIT_H

#include <iostream>

namespace ariel{

enum class Unit{CM, M, KM, SEC, MIN, HOUR, G, KG, TON};
enum class Dimenson{LENGTH, TIME, WEIGHT};


double ratio(const enum Unit);

enum Unit unitByString(std::string);

inline std::ostream& operator << (std::ostream &os, const Unit u){
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


bool comparable(const enum Unit, const enum Unit);
bool operator >(const enum Unit, const enum Unit);
bool operator <(const enum Unit, const enum Unit);

}

#endif
