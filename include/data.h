#ifndef __DATA_H__
#define __DATA_H__ 

#include "parameter_handler.h"
#include <vector>

struct Run_parameters{
    double tmax=100;
    double dt=0.1;
    int no_runs=10;
    double output_interval=1.;
};

struct Chemo_parameters{
    double t_start=10;
    double t_dur=50;
    double deathrate=0.1;
};

struct Type_params{
        int no_types;
        int start_type;
        double av_rate;//initial proliferation rate
        double rate_var;//allowed variance in proliferation rate
        double prolif_step;
};

class Data{
    public:
        Data();
        Data(ParameterHandler& parameters);

        double get_prolif_rate(unsigned int type) const;
        double set_prolif_rate(unsigned int type, double rate);

        double get_immune_sensitivity_rate(unsigned int type) const;

        double get_mutation_rate() const {return _mutation_prob;}
        void set_mutation_rate(double v){_mutation_prob=v;}

        double return_initial_cellnumber() const { return _initial_cellnumber;}

        int return_max_prolif_types() const { return _prolif.no_types;}
        int return_start_prolif_type() const { return _prolif.start_type;}
        int return_max_immune_types() const { return _immmune.no_types;}
        int return_start_immune_type() const { return _immmune.start_type;}

        void set_max_prolif_types(int v){ _prolif.no_types=v;}
        void set_max_immun_types(int v){ _immmune.no_types=v;}


        double get_initial_primary_tumour_cellnumber() const { return _initial_primary_tumour_cellnumber;}
        double get_initial_anti_tumour_immune_cellnumber () const {return _initial_anti_tumour_immune_cellnumber;}
        double get_initial_pro_tumour_immune_cellnumber() const {return _initial_pro_tumour_immune_cellnumber;}

        /** return the chemotherapy state according to min and max.*/
        bool return_chemo_state(double t) const {return false;}

        double get_death_chemo() const {return _chemparams.deathrate;}
        double get_immune_promoted_rate() const {return _immune_promoted_rate;}
        double get_immune_inhibited_rate() const {return _immune_inhibited_rate;}


        double get_primary_tumour_prolif_rate() const{return _primary_tumour_prolif_rate;}
        double get_primary_tumour_immune_rate() const{return _primary_tumour_immune_rate;}
        double get_spontaneous_cell_death_rate() const{return _spontaneous_cell_death_rate;}
        double get_spontaneous_immune_cell_death_rate() const{return _spontaneous_immune_cell_death_rate;}
        double get_immune_cell_prolif_rate() const{return _immune_cell_prolif_rate;}

        double return_output_interval() const{return _runparams.output_interval;}
        double return_no_runs() const{return _runparams.no_runs;}

        const Run_parameters & return_runparameters(){return _runparams;}


    private:
        std::vector<double> prolif_rates;

        double _initial_cellnumber;
        double _initial_primary_tumour_cellnumber;
        double _initial_anti_tumour_immune_cellnumber;
        double _initial_pro_tumour_immune_cellnumber;

        Type_params _prolif;
        Type_params _immmune;

        double _mutation_prob;
        double _immune_promoted_rate;//the rate that immune cells are promoted by total tumour
        double _immune_inhibited_rate;//the rate that immune cells are inhibited by total tumour
        double _spontaneous_cell_death_rate;
        double _spontaneous_immune_cell_death_rate;
        double _immune_cell_prolif_rate;

        Chemo_parameters _chemparams;


        double _primary_tumour_prolif_rate;
        double _primary_tumour_immune_rate;

        Run_parameters _runparams;


};
#endif /* ifndef __DATA_H__ */
