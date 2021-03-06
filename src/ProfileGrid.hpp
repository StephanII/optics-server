#ifndef PROFILE_GRID_HPP_
#define PROFILE_GRID_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Device.hpp"



using namespace std;

class ProfileGrid : public Device
{
friend unsigned int test_profileGrid(bool verbose);

public:

	ProfileGrid(const string& nomenclature, double width, double height, unsigned int nof_wires);

	virtual
	~ProfileGrid();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const ProfileGrid& profileGrid);

	void
	transport(Ion& ion);
	
	void
	reset(void);
	
private:

	void
	fillHistograms(double x, double y);

	vector<atomic<unsigned int>> m_wires_hor;
	
	vector<atomic<unsigned int>> m_wires_ver;
};

#endif /* PROFILE_GRID_HPP_ */
