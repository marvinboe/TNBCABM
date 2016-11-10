#ifndef __DATA_H__
#define __DATA_H__ 

#include "parameter_handler.h"
#include <vector>

class Data{
    public:
        Data();
        Data(const Data&); 
        Data(ParameterHandler& parameters);

        double get_prolif_rate(unsigned int type) const;
        double set_prolif_rate(unsigned int type, double rate);
		
		

        double get_mutation_rate() const {return _mutation_rate;}
        void set_mutation_rate(double v){_mutation_rate=v;}

        double return_initial_cellnumber() const { return _initial_cellnumber;}

        int return_max_prolif_types() const { return _max_prolif_types;}
        int return_max_immune_types() const { return _max_immune_types;}

        void set_max_prolif_types(int v){ _max_prolif_types=v;}
        void set_max_immun_types(int v){ _max_immune_types=v;}
		
		double get_initial_primary_tumour_cellnumber() const { return _initial_primary_tumour_cellnumber;}
		double get_initial_anti_tumour_immune_cellnumber () const {return _initial_anti_tumour_immune_cellnumber;}
		double get_initial_pro_tumour_immune_cellnumber() const {return _initial_pro_tumour_immune_cellnumber;}
		
		int get_chemo_state() const {return _chemo_state;}
		double get_death_chemo() const{return _death_chemo;}
		double get_death_intrinsic() const{return _death_intrinsic;}
		double get_immune_promoted_rate() const{return _immune_promoted_rate;}
		double get_immune_inhibited_rate() const{return _immune_inhibited_rate;}


		double get_primary_tumour_prolif_types() const{return _primary_tumour_prolif_types;}
		double get_primary_tumour_immune_types() const{return _primary_tumour_immune_types;}
		

    private:
        std::vector<double> prolif_rates;

		double _initial_cellnumber;
		double _initial_primary_tumour_cellnumber;
		double _initial_anti_tumour_immune_cellnumber;
		double _initial_pro_tumour_immune_cellnumber;
		
        int _max_prolif_types;
        int _max_immune_types;
		double _mutation_rate;
		int _chemo_state;//binary number with 0 and 1
		double _death_chemo;
		double _death_intrinsic;//death should also be density dependent on local tumour size
		double _immune_promoted_rate;//the rate that immune cells are promoted by total tumour
		double _immune_inhibited_rate;//the rate that immune cells are inhibited by total tumour


		double _primary_tumour_prolif_types;
		double _primary_tumour_immune_types;


};
#endif /* ifndef __DATA_H__ */
