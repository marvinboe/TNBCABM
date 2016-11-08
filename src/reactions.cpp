#include "reactions.h"


bool Reaction::apply(Model& model){


    // int n=model.get_Ccell_number(_reactant1,_reactant_comp);
    // model.set_Ccell_number(_reactant1,_reactant_comp,n);

    return true;

}

Reaction* AllReactions::return_random_reaction(){

    return _all.back();

}
