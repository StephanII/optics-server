#include "DriftTube.hpp"

#include <sstream>



DriftTube::DriftTube(const string& nomenclature, double width, double height, double length) :
	Device(nomenclature, width, height, length)
{ }



DriftTube::~DriftTube()
{ }



string
DriftTube::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "length = " << m_length << " m" 
	   << ")";
	return ss.str();
}
	


string
DriftTube::toLine(void) const
{
	return m_nomenclature==""?"Drifttube":m_nomenclature;
}
	


ostream&
operator<<(ostream& os, const DriftTube& driftTube)
{
	return os << driftTube.toLine();
}



void
DriftTube::transport(Ion& ion)
{
	ion.setX( m_length * ion.dx() );
	ion.setY( m_length * ion.dy() );	
	
	if( not isParticleLost(ion) ){
		if( m_next != NULL ){
			m_next->transport(ion);
		}
	}
}


	
void
DriftTube::reset(void)
{ }







