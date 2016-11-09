#ifndef __DATA_H__
#define __DATA_H__ 

#include <vector>

class Data{
    public:
        Data();

        double get_prolif_rate(unsigned int type);

        double get_mutation_rate(){return _mutation_rate;}
        double set_mutation_rate(double v){_mutation_rate=v;}

    private:
        std::vector<double> prolif_rates;

        double _mutation_rate;


};
#endif /* ifndef __DATA_H__ */
