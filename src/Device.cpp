#include "Device.hpp"

#include <sstream>
#include <cmath>



Device::Device(const string& nomenclature, double width, double height) :
	m_nomenclature(nomenclature),
	m_width(width),
	m_height(height),
	m_previous(NULL),
	m_next(NULL)
{ }



Device::~Device()
{ }
	


ostream&
operator<<(ostream& os, const Device& device)
{
	return os << device.toLine();
}



void
Device::appendDevice(Device* device)
{
	if( m_next==NULL ){
		m_next=device;
		device->setPreviousDevice(this);
	} else {
		m_next->appendDevice(device);
	}
}



bool
Device::isParticleLost(const Ion& ion) const 
{	
	return (4*pow(ion.x(),2)/pow(m_width,2) + 4*pow(ion.y(),2)/pow(m_height,2)) > 1;
}





