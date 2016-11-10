
#include "data.h"

Data::Data(){
    _initial_cellnumber=100;
    _max_prolif_types=10;
    _max_immune_types=10;
}


Data::Data(ParameterHandler & parameters){
    //defining defaults:
    _initial_cellnumber=100;
	_initial_primary_tumour_cellnumber=10000;
	_initial_anti_tumour_immune_cellnumber=1000;
	_initial_pro_tumour_immune_cellnumber=1000;
	
    _max_prolif_types=10;
    _start_prolif_type=5;
    _max_immune_types=10;
    _start_immune_type=5;
    _mutation_rate = 1.1;
	_chemo_state=1;
	_death_chemo=0.5;
	_immune_promoted_rate=0;
	_immune_inhibited_rate=0.01;
    _prolif_rate=0.3;
    _prolif_var=0.2;
    _prolif_step = _prolif_var / (double)_start_prolif_type;
    _immune_sensitivity_rate = 0.0001;
    _immune_sensitivity_var = 0.00005;
    _immune_sensitivity_step = _immune_sensitivity_var / (double)_start_immune_type;
    
    _spontaneous_cell_death_rate=0.3;
	_spontaneous_immune_cell_death_rate=0.3;
	_immune_cell_prolif_rate=0.3;
	
	_primary_tumour_prolif_rate=1.;
	_primary_tumour_immune_rate=1.;
	
    
    
    //overwriting with parameter files
    
    parameters.SetValue("initial_cellnumber","initial number of cells = 100",_initial_cellnumber);
	parameters.SetValue("initial_primary_tumour_cellnumber","initial number of primary tumour cells = 10000",_initial_primary_tumour_cellnumber);
	parameters.SetValue("initial_anti_tumour_immune_cellnumber","initial number of anti-tumour immune cells = 1000",_initial_anti_tumour_immune_cellnumber);
	parameters.SetValue("initial_pro_tumour_immune_cellnumber","initial number of pro-tumour immune cells = 1000",_initial_pro_tumour_immune_cellnumber);
	
	
    parameters.SetValue("prolif_types","total number of proliferation phenotypes",_max_prolif_types);
    parameters.SetValue("immune_types","total number of proliferation phenotypes",_max_immune_types);
    parameters.SetValue("mutation_rate","total mutation rate = 0.1",_mutation_rate);
	parameters.SetValue("chemo_state","whether chemotherapy is applied (0/1)",_chemo_state);
	parameters.SetValue("death_chemo","death rate due to chemotherapy (need to be scaled by prolif rate)",_death_chemo);
	parameters.SetValue("spontaneous_cell_death_rate","coeffcient of density dependent death for tumour cell",_spontaneous_cell_death_rate);
	parameters.SetValue("immune_promoted_rate","the rate of immune cells promoted by total tumour burden (need to be scaled by total tumour size)",_immune_promoted_rate);
	parameters.SetValue("immune_inhibited_rate","the rate of immune cells inhibited by total tumour burden (need to be scaled by total tumour size)",_immune_inhibited_rate);
	parameters.SetValue("primary_tumour_prolif_types","the prolif type(rate) of primary tumour cells",_primary_tumour_prolif_rate);
	parameters.SetValue("primary_tumour_immune_types","the immune type(rate) of primary tumour cells",_primary_tumour_immune_rate);
	parameters.SetValue("spontaneous_immune_cell_death_rate","coeffcient of density dependent death for immune cell",_spontaneous_immune_cell_death_rate);
	parameters.SetValue("immune_cell_prolif_rate","the prolife rate of immune cells",_immune_cell_prolif_rate);
   
    parameters.print_help(std::cout);

}

double Data::get_prolif_rate(unsigned int type) const{
    return (_prolif_rate - _prolif_var) + (type * _prolif_step);
}

double Data::get_immune_sensitivity_rate(unsigned int type) const{
    return (_immune_sensitivity_rate - _immune_sensitivity_var) + (type * _immune_sensitivity_step);
}




