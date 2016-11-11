
#include "data.h"

Data::Data(){
    _initial_cellnumber=100;
    _prolif.no_types=10;
    _immmune.no_types=10;
}


Data::Data(ParameterHandler & parameters){
    //defining defaults:
    _initial_cellnumber=100;
    _initial_primary_tumour_cellnumber=10000;
    _initial_anti_tumour_immune_cellnumber=1000;
    _initial_pro_tumour_immune_cellnumber=1000;

    _prolif.no_types=10;
    _prolif.start_type=5;
    _immmune.no_types=10;
    _immmune.start_type=5;
    _mutation_prob = 1.1;
    _immune_promoted_rate=0;
    _immune_inhibited_rate=0.01;
    _prolif.av_rate=0.3;
    _immmune.av_rate = 0.0001;

    _prolif.rate_var=0.2;
    _immmune.rate_var = 0.00005;

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


    parameters.SetValue("prolif_types","total number of proliferation phenotypes",_prolif.no_types);
    parameters.SetValue("av_prolif_rate","mean proliferation rate of tumor cells",_prolif.av_rate);

    parameters.SetValue("death_chemo","death rate due to chemotherapy (need to be scaled by prolif rate)",_chemparams.deathrate);
    parameters.SetValue("chemo_starttime","starting time of chemo (default: never)",_chemparams.t_start);
    parameters.SetValue("chemo_duration","duration of chemo (default: forever)",_chemparams.t_dur);

    parameters.SetValue("immune_types","total number of proliferation phenotypes",_immmune.no_types);
    parameters.SetValue("mutation_rate","total mutation rate = 0.1",_mutation_prob);
    parameters.SetValue("immune_promoted_rate","the rate of immune cells promoted by total tumour burden (need to be scaled by total tumour size)",_immune_promoted_rate);
    parameters.SetValue("immune_inhibited_rate","the rate of immune cells inhibited by total tumour burden (need to be scaled by total tumour size)",_immune_inhibited_rate);

    parameters.SetValue("primary_tumour_prolif_rate","the prolif type(rate) of primary tumour cells",_primary_tumour_prolif_rate);
    parameters.SetValue("primary_tumour_immune_rate","the immune type(rate) of primary tumour cells",_primary_tumour_immune_rate);

    parameters.SetValue("spontaneous_cell_death_rate","death rate of micromet cells",_spontaneous_cell_death_rate);

    parameters.SetValue("spontaneous_immune_cell_death_rate","coeffcient of density dependent death for immune cell",_spontaneous_immune_cell_death_rate);
    parameters.SetValue("immune_cell_prolif_rate","the prolife rate of immune cells",_immune_cell_prolif_rate);
    parameters.SetValue("t_max","maximum simulation time (=100)",_runparams.tmax);
    parameters.SetValue("dt","timestep for deterministic integration (=0.1)",_runparams.dt);
    parameters.SetValue("no_runs","number of runs (=10)",_runparams.no_runs);
    parameters.SetValue("output_interval","interval of output (=1.)",_runparams.output_interval);
    parameters.print_help(std::cout);

    _prolif.prolif_step = _prolif.rate_var / (double)_prolif.start_type;
    _immmune.prolif_step = _immmune.rate_var / (double)_immmune.start_type;

}

double Data::get_prolif_rate(unsigned int type) const{
    return (_prolif.av_rate - _prolif.rate_var) + (type * _prolif.prolif_step);
}

double Data::get_immune_sensitivity_rate(unsigned int type) const{
    return (_immmune.av_rate - _immmune.rate_var) + (type * _immmune.prolif_step);
}




