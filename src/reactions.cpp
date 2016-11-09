#include "reactions.h"


bool Reaction::apply(Model& model){


    if (_reactant1 >=0){
        int react1=model.get_Ccell_number(_reactant1,_reactant_comp);
        model.set_Ccell_number(_reactant1,_reactant_comp,react1-1);
    }

    if (_reactant2 >=0){
        int react2=model.get_Ccell_number(_reactant2,_reactant_comp);
        model.set_Ccell_number(_reactant2,_reactant_comp,react2-1);
    }

    if (_product1>=0){
    int prod1=model.get_Ccell_number(_product1,_reactant_comp);
    model.set_Ccell_number(_product1,_reactant_comp,prod1+1);
    }
    if (_product2>=0){
        int prod2=model.get_Ccell_number(_product2,_reactant_comp);
        model.set_Ccell_number(_product2,_reactant_comp,prod2+2);
    }


    return true;

}

Reaction* AllReactions::return_random_reaction(){

    std::uniform_real_distribution<double> uniform01(0.,_ratesum);
    double rnumb=uniform01(rng);

    double sum=0;
    for (int i =0; i< _all.size(); ++i){
        sum +=_all[i]->rate();
        
        if (sum > rnumb){
            return _all[i];
        }
        

    }

    return _all.back();

}
