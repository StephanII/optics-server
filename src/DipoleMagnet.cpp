#include "DipoleMagnet.hpp"

#include <sstream>
#include <cmath>


DipoleMagnet::DipoleMagnet(const string& nomenclature, double width, double height, double length, double angle) :
	Device(nomenclature, width, height, length),
	m_angle(angle)
{ }



DipoleMagnet::~DipoleMagnet()
{ }



string
DipoleMagnet::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "length = " << m_length << " m, "
	   << "angle = " << m_angle  
	   << ")";
	return ss.str();
}
	


string
DipoleMagnet::toLine(void) const
{
	return m_nomenclature==""?"DipoleMagnet":m_nomenclature;
}
	


ostream&
operator<<(ostream& os, const DipoleMagnet& dipoleMagnet)
{
	return os << dipoleMagnet.toLine();
}




void
DipoleMagnet::transport(Ion& ion)
{
	if( m_angle != 0 ){
		
		double r        = m_length/m_angle;
		double cosangle = cos(m_angle);
		double sinangle = sin(m_angle);
			
		ion.setX( cosangle*ion.x() + r*sinangle*ion.dx() + r*(1.-cosangle)*ion.dp() );			
		ion.setDx( -(1/r)*sinangle*ion.x() +  cosangle*ion.dx() + sinangle*ion.dp() );	
		ion.setY( m_length*ion.dy() );
		ion.setDl( -sinangle*ion.x() - r*(1.-cosangle)*ion.dx() - r*(m_length-r*sinangle)*ion.dp() );

	} else {
		ion.setX( m_length * ion.dx() );
		ion.setY( m_length * ion.dy() );	
	}
	
	if( not isParticleLost(ion) ){
		if( m_next != NULL ){
			m_next->transport(ion);
		}
	}
}


	
void
DipoleMagnet::reset(void)
{ }






