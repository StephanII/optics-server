#include "Screen.hpp"

#include <sstream>
#include <cmath>



Screen::Screen(const string& nomenclature, double width, double height, double dots_per_meter) :
	Device(nomenclature, width, height, 0),
	m_dots_per_meter(dots_per_meter),
	m_pixel(ceil(dots_per_meter*dots_per_meter*width*height)),
	m_missed(0)
{ }



Screen::~Screen()
{ }



string
Screen::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " ("
	   << "width = " << m_width << " m, "
	   << "height = " << m_height << " m, "
	   << "m_missed = " << m_missed  
	   << ") {\n";
	
	unsigned int cells_hor = m_dots_per_meter * m_width;
	unsigned int cells_ver = m_dots_per_meter * m_height;
	
	for( unsigned int y=0; y<cells_ver; y++ ){
		ss << indention << "\t";
		for( unsigned int x=0; x<cells_hor; x++ ){
			ss << m_pixel[cells_hor * y + x] << " ";		
		}
		ss << "\n";
	}
	ss << indention << "}";	   
	return ss.str();
}
	


string
Screen::toLine(void) const
{
	return m_nomenclature==""?"Screen":m_nomenclature;
}
	


ostream&
operator<<(ostream& os, const Screen& screen)
{
	return os << screen.toLine();
}



void
Screen::transport(Ion& ion)
{
	fillHistogram(ion.x(),ion.y());
	if( m_next != NULL ){
		m_next->transport(ion);
	}
}


	
void
Screen::reset(void)
{ 
	fill(m_pixel.begin(), m_pixel.end(), 0);
}



// @TODO optimize
void
Screen::fillHistogram(double x, double y)
{
	double half_width  = 0.5*m_width;
	double half_height = 0.5*m_height;
	unsigned int cells_hor = m_dots_per_meter * m_width;
	unsigned int cells_ver = m_dots_per_meter * m_height;
		
	if ( x < half_width and
		 x > -half_width and
		 y < half_height and
		 y > -half_height){
		
		double x_ = floor((x*cells_hor/m_width) + 0.5*cells_hor);
		double y_ = floor((y*cells_ver/m_height) + 0.5*cells_ver);			
		unsigned int pos = cells_hor * y_ + x_;
		
		m_pixel[pos] += 1;
	} else {
		m_missed += 1;
	}
}



