
#include "kernel.h"
#include <fstream>
#include <ostream>  

Kernel::Kernel(Data data):_data(data),_model(_data),_all_reactions(_model,_data){

    // and here some even more funny stuff will come in

}

std::uniform_real_distribution<double> Kernel::uniform01(0.,1.);

double Kernel::direct_update(double t){

    double total_prop=0.;
    for (std::vector<Reaction*>::iterator it=_all_reactions.begin(); it!=_all_reactions.end(); ++it){
        total_prop+=(*it)->update_propensity(_model, _data);
    }
    if (total_prop<=1e-20) return std::numeric_limits<double>::infinity();

    _all_reactions.set_total_propensity(total_prop);

    double tau=-1./_all_reactions.return_total_propensity() * std::log(uniform01(rng));

    double randchoice=_all_reactions.return_total_propensity() * uniform01(rng);
    double wheightsum=0.;
    int i=-1;
    while (wheightsum<randchoice){
        ++i;
        wheightsum+=_all_reactions[i]->propensity();
    }
    Reaction* reaction= _all_reactions[i];
    reaction->apply(_model, _data);
    // std::cout <<"test "<<_model.return_Ccell_number(0,0)<<" "<<total_prop<<" "<<tau<<" "<<randchoice<<" "<<i<<std::endl;
    return t+tau;
}

void Kernel::deterministic(double dt){
    //get the parameters
    int c=_model.return_chemo_state();
    double d_c=_data.get_death_chemo();
    double delta=_data.get_spontaneous_cell_death_rate();
    double ki=_data.get_immune_promoted_rate();
    double kd=_data.get_immune_inhibited_rate();
    double rate_prim=_data.get_primary_tumour_prolif_rate();
    double rate_imm=_data.get_primary_tumour_immune_rate();

    double delta_imm=_data.get_spontaneous_immune_cell_death_rate();
    double Prolif_imm=_data.get_immune_cell_prolif_rate();


    double primary_size=_model.return_primary_size();
    double anti_size=_model.return_anti_immune();
    double pro_size=_model.return_pro_immune();


    double new_primary_size=0.;
    double new_anti_size=0.;
    double new_pro_size=0.;

    //update the primary tumour size as well as the anti- and pro_ tumour immune cell sizes
    new_primary_size=primary_size+dt*primary_size*(rate_prim+rate_imm*(pro_size-anti_size)-c*d_c*rate_prim-delta*primary_size);
    new_anti_size=anti_size+dt*anti_size*(Prolif_imm+primary_size*(ki-kd)-c*d_c-delta_imm*anti_size);
    new_pro_size=pro_size+dt*pro_size*(Prolif_imm+primary_size*(ki-kd)-c*d_c-delta_imm*anti_size);

    // std::cout <<new_primary_size<<" "<<(rate_prim+rate_imm*(pro_size-anti_size)-c*d_c*rate_prim-delta*primary_size)<<" "<<new_anti_size<<" "<<new_pro_size<<std::endl;
    _model.set_primary_size(new_primary_size);
    _model.set_anti_immune(new_anti_size);
    _model.set_pro_immune(new_pro_size);

}

void Kernel::execute(Output& output){
    double t_max=_data.return_runparameters().tmax;
    double dt=_data.return_runparameters().dt;
    double output_step=_data.return_runparameters().output_interval;
    double next_t_output=0.;

    double t=0;
    double t_stoch=0;

    while (t<t_max){
        //output stuff (TODO maybe extra class for that)
        while (next_t_output <= t){
            //print matrix to new files every time
            output.save_data(next_t_output,_model);
            next_t_output+=output_step;
        }
        while (t_stoch<t){
            t_stoch=direct_update(t_stoch);
        }
        t=t+dt;
        deterministic(dt);
        // std::cout<<t<<"\t"<<_model.get_primary_size()<<"\t"<<new_anti_size<<"\t"<<new_pro_size<<std::endl;
    }
    output.save_at_end(t,_model);
}
