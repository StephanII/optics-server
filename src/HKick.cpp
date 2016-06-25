#include "HKick.hpp"

#include <sstream>



HKick::HKick(const string& nomenclature, double angle) :
	Device(nomenclature, 0, 0, 0),
	m_angle(angle)
{ }



HKick::~HKick()
{ }



string
HKick::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "angle = " << m_angle << " rad" 
	   << ")";
	return ss.str();
}
	


string
HKick::toLine(void) const
{
	return m_nomenclature==""?"HKick":m_nomenclature;
}
	


ostream&
operator<<(ostream& os, const HKick& hKick)
{
	return os << hKick.toLine();
}



void
HKick::transport(Ion& ion)
{
	ion.setDx( ion.dx() + m_angle );
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
HKick::reset(void)
{ }





