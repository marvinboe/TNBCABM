
#include "kernel.h"




std::uniform_real_distribution<double> Kernel::uniform01(0.,1.);

double Kernel::direct_update(double t){

    double tau=1./_all_reactions.rate_sum() * std::log(uniform01(rng));

    Reaction* reaction= _all_reactions.return_random_reaction();
    
    reaction->apply(model);




    



    return t+tau;
}
