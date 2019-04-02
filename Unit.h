#pragma once

namespace ariel{

enum class Unit{CM, M, KM, SEC, MIN, HOUR, G, KG, TON};
enum class Dimenson{LENGTH, TIME, WEIGHT};

long double ratio(Unit type){
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
	return 0;
}

bool operator ==(const Unit& a, const Unit& b); //iff they have same dimenson 
bool operator !=(const Unit& a, const Unit& b); 


}
