
#include "kernel.h"

Kernel::Kernel(Data data):_model(data){
    // and here some even more funny stuff will come in

}

std::uniform_real_distribution<double> Kernel::uniform01(0.,1.);

double Kernel::direct_update(double t){

    double total_prop=0.;
    for (std::vector<Reaction*>::iterator it=_all_reactions.begin(); it!=_all_reactions.end(); ++it){
        total_prop+=(*it)->update_propensity(_model);
    }
    _all_reactions.set_total_propensity(total_prop);

    double tau=1./_all_reactions.return_total_propensity() * std::log(uniform01(rng));

    double randchoice=_all_reactions.return_total_propensity() * uniform01(rng);
    double weightsum=0.;
    int i=0;
    while (weightsum<randchoice){
        weightsum+=_all_reactions[i]->rate();
        ++i;
    }
    Reaction* reaction= _all_reactions[i];
    reaction->apply(_model);

    return t+tau;
}



void Kernel::execute(){
    double t_max=100;

    double t=0;
    while (t<t_max){

        t=direct_update(t);

    }


}
