
#include "data.h"

Data::Data(){
    _initial_cellnumber=100;
    _max_prolif_types=10;
    _max_immune_types=10;
}

Data::Data(const Data& other){
    _initial_cellnumber=other.return_initial_cellnumber();
    _max_prolif_types=other.return_max_prolif_types();
    _max_immune_types=other.return_max_immune_types();
}

Data::Data(ParameterHandler & parameters){
    //defining defaults:
    _initial_cellnumber=100;
    _max_prolif_types=10;
    _max_immune_types=10;
    _mutation_rate = 1;
    
    //overwriting with parameter files
    
    parameters.SetValue("initial_cellnumber","initial number of cells = 100",_initial_cellnumber);
    parameters.SetValue("prolif_types","total number of proliferation phenotypes",_max_prolif_types);
    parameters.SetValue("immune_types","total number of proliferation phenotypes",_max_immune_types);
    parameters.SetValue("mutation_rate","total mutation rate = 0.1",_mutation_rate);

    parameters.print_help(std::cout);

}

double Data::get_prolif_rate(unsigned int type) const{
    //needs to be written!
    return 0.3+type/double(_max_prolif_types);
}




