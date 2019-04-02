#pragma once

namespace ariel{

enum Unit{CM, M, KM, SEC, MIN, HOUR, G, KG, TON};
enum Dimenson{LENGTH, TIME, WEIGHT};

long double ratio(Unit type){
	switch (type){
		case CM: return 1;
			break;
		case M: return 100;
			break;
		case KM: return 100000;
			break;
		case SEC: return 1;
			break;
		case MIN: return 60;
			break;
		case HOUR: return 3600;
			break;
		case G: return 1;
			break;
		case KG: return 1000;
			break;
		case TON: return 1000000;
			break;
	}
	return 0;
}

bool operator ==(const Unit& a, const Unit& b); //iff they have same dimenson 
bool operator !=(const Unit& a, const Unit& b); 


}
