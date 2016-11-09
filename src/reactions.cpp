#include "reactions.h"


bool Reaction::apply(Model& model){


    // int n=model.get_Ccell_number(_reactant1,_reactant_comp);
    // model.set_Ccell_number(_reactant1,_reactant_comp,n);

    return true;

}

Reaction* AllReactions::return_random_reaction(){

    std::uniform_real_distribution<double> uniform01(0.,_ratesum);
    double rnumb=uniform01(rng);

    for (int i =0; i< _all.size(); ++i){

    }

    return _all.back();

}
