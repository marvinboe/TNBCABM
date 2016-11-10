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

    private:
        std::vector<double> prolif_rates;

        double _mutation_rate;

        double _initial_cellnumber;

        int _max_prolif_types;
        int _max_immune_types;


};
#endif /* ifndef __DATA_H__ */
