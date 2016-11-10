#ifndef __DATA_H__
#define __DATA_H__ 

#include "parameter_handler.h"
#include <vector>

class Data{
    public:
        Data();
        Data(ParameterHandler& parameters);

        double get_prolif_rate(unsigned int type) const;
        double set_prolif_rate(unsigned int type, double rate);
    
        double get_immune_sensitivity_rate(unsigned int type) const;

        double get_mutation_rate() const {return _mutation_rate;}
        void set_mutation_rate(double v){_mutation_rate=v;}

        double return_initial_cellnumber() const { return _initial_cellnumber;}

        int return_max_prolif_types() const { return _max_prolif_types;}
        int return_start_prolif_type() const { return _start_prolif_type;}
        int return_max_immune_types() const { return _max_immune_types;}
        int return_start_immune_type() const { return _start_immune_type;}

        void set_max_prolif_types(int v){ _max_prolif_types=v;}
        void set_max_immun_types(int v){ _max_immune_types=v;}

        double get_initial_primary_tumour_cellnumber() const { return _initial_primary_tumour_cellnumber;}
        double get_initial_anti_tumour_immune_cellnumber () const {return _initial_anti_tumour_immune_cellnumber;}
        double get_initial_pro_tumour_immune_cellnumber() const {return _initial_pro_tumour_immune_cellnumber;}

        int get_chemo_state() const {return _chemo_state;}
        double get_death_chemo() const {return _death_chemo;}
        double get_death_intrinsic() const {return _death_intrinsic;}
        double get_immune_promoted_rate() const {return _immune_promoted_rate;}
        double get_immune_inhibited_rate() const {return _immune_inhibited_rate;}


        double get_primary_tumour_prolif_rate() const{return _primary_tumour_prolif_rate;}
        double get_primary_tumour_immune_rate() const{return _primary_tumour_immune_rate;}
        double get_spontaneous_cell_death_rate() const{return _spontaneous_cell_death_rate;}

        double return_output_interval() const{return 1.;}
        double return_no_runs() const{return 5;}


    private:
        std::vector<double> prolif_rates;

        double _initial_cellnumber;
        double _initial_primary_tumour_cellnumber;
        double _initial_anti_tumour_immune_cellnumber;
        double _initial_pro_tumour_immune_cellnumber;

        int _max_prolif_types;
        int _start_prolif_type;
        int _max_immune_types;
        int _start_immune_type;
        double _mutation_rate;
        int _chemo_state;//binary number with 0 and 1
        double _death_chemo;
        double _death_intrinsic;//death should also be density dependent on local tumour size
        double _immune_promoted_rate;//the rate that immune cells are promoted by total tumour
        double _immune_inhibited_rate;//the rate that immune cells are inhibited by total tumour
        double _prolif_rate;//initial proliferation rate
        double _prolif_var;//allowed variance in proliferation rate
        double _prolif_step;
        double _immune_sensitivity_rate;
        double _immune_sensitivity_var;
        double _immune_sensitivity_step;
        double _spontaneous_cell_death_rate;


        double _primary_tumour_prolif_rate;
        double _primary_tumour_immune_rate;


};
#endif /* ifndef __DATA_H__ */
