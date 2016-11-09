
#include "kernel.h"


std::uniform_real_distribution<double> Kernel::uniform01(0.,1.);

double Kernel::direct_update(double t){

    double tau=1./_all_reactions.rate_sum() * std::log(uniform01(rng));

    double randchoice=_all_reactions.rate_sum() * uniform01(rng);

    double weightsum=0.;
    int i=0;
    while (weightsum<randchoice){
        weightsum+=_all_reactions[i]->rate();
        ++i;
    }
    Reaction* reaction= _all_reactions[i];

    reaction->apply(model);

    return t+tau;
}



void Kernel::execute(){
    double t_max=100;

    double t=0;
    while (t<t_max){

        t=direct_update(t);

    }


}
