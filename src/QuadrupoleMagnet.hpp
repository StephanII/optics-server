#ifndef QUADRUPOLE_MAGNET_HPP_
#define QUADRUPOLE_MAGNET_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class QuadrupoleMagnet : public Device
{
friend unsigned int test_quadrupoleMagnet(bool verbose);

public:

	QuadrupoleMagnet(const string& nomenclature, double width, double height, double length, double strength);

	virtual
	~QuadrupoleMagnet();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const QuadrupoleMagnet& quadrupoleMagnet);

	void
	transport(Ion& ion);
	
	void
	reset(void);
	
	inline void setStrength(double strength) { m_strength = strength; }
	
private:
	
	double m_strength;
};

#endif /* QUADRUPOLE_MAGNET_HPP_ */
