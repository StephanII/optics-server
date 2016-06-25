#ifndef H_KICK_HPP_
#define H_KICK_HPP_

#include <iostream>
#include <string>

#include "Device.hpp"



using namespace std;

class HKick : public Device
{
friend unsigned int test_hKick(bool verbose);

public:

	HKick(const string& nomenclature, double angle);

	virtual
	~HKick();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const HKick& hKick);

	virtual void
	transport(Ion& ion);
		
	virtual void
	reset(void);
	
private:

	double m_angle;
};

#endif /* H_KICK_HPP_ */
