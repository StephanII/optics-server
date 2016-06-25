#ifndef Device_HPP_
#define Device_HPP_

#include <iostream>
#include <string>

#include "Ion.hpp"



using namespace std;

class Device
{
public:

	Device(const string& nomenclature, double width, double height, double length=0.);

	virtual
	~Device();

	virtual string
	toString(unsigned int indent=0) const = 0; 
	
	virtual string
	toLine(void) const = 0;
	
	friend ostream&
	operator<<(ostream& os, const Device& device);

	void
	appendDevice(Device* device);
	
	bool
	isParticleLost(const Ion& ion) const ;	
	
	virtual void
	transport(Ion& ion) = 0;
		
	virtual void
	reset(void) = 0;
	
	inline void setPreviousDevice(Device* device) { m_previous = device; }	
	
	inline Device* getNextDevice(void) { return m_next; }

protected:

	string m_nomenclature;

	double m_width;

	double m_height;
	
	double m_length;
	
	Device* m_previous;
	
	Device* m_next;
};

#endif /* Device_HPP_ */
