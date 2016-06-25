#include "Accelerator.hpp"

#include <sstream>



Accelerator::Accelerator() :
	m_ion_source(),
	m_devices()
{ }



Accelerator::~Accelerator()
{ }



string
Accelerator::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " {\n";
	for( auto it_device=m_devices.begin(); it_device<m_devices.end(); it_device++ ){
		ss << indention << (*it_device)->toString(indent+1) << "\n";
	}	
	ss << indention << "}";
	return ss.str();
}
	


string
Accelerator::toLine(void) const
{
	stringstream ss;
	ss << "Accelerator ( ion_source = " << m_ion_source.toString() << " )";
	return ss.str();
}
	


ostream&
operator<<(ostream& os, const Accelerator& accelerator)
{
	return os << accelerator.toLine();
}


	
void
Accelerator::appendDevice(Device* device)
{
	m_devices.push_back(device);
	m_ion_source.appendDevice(device);
}


	
void
Accelerator::startSimulation(unsigned int nof_ions, bool threaded, unsigned int nof_threads)
{
	if (threaded){
		cout << "start simulation with " << nof_ions << " ions in " << nof_threads << " threads" << endl;
	} else {
		cout << "start simulation with " << nof_ions << " ions in 1 thread" << endl;
	}
	
	
	for( auto it_device=m_devices.begin(); it_device<m_devices.end(); it_device++ ){
		(*it_device)->reset();
	}
	
	if( threaded ){
	
		unsigned int ions_per_core = nof_ions/nof_threads;
		
		thread* threadlist = new thread[nof_threads];
		
		for( unsigned int i=0; i<nof_threads; i++ ){
			try{
				//cout << "start thread with " << ions_per_core << " ions" << endl;
				threadlist[i] = thread(&IonSource::run, m_ion_source, ions_per_core);
			} catch(...) {
				cout << "THREAD LIMIT exceeded" << endl;
				exit(0);
			}
		}
		
		for( unsigned int i=0; i<nof_threads; i++ ){ 
			threadlist[i].join();
		}

		delete[] threadlist;	
	} else {
		m_ion_source.run(nof_ions);
	}	
}








