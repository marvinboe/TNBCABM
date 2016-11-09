#include "reactions.h"


bool Reaction::apply(Model& model){


    if ((_reactant1_prolif >=0)&&(_reactant1_imm >=0)){
        int react1=model.return_Ccell_number(_reactant1_prolif,_reactant1_imm);
        model.set_Ccell_number(_reactant1_prolif,_reactant1_imm,react1-1);
    }

    // if ((_reactant2_prolif >=0)&&(_reactant2_imm >=0)){
    //     int react2=model.return_Ccell_number(_reactant2_prolif,_reactant2_imm);
    //     model.set_Ccell_number(_reactant2_prolif,_reactant2_imm,react2-1);
    // }

    if ((_product1_prolif >=0)&&(_product1_imm >=0)){
        int prod1=model.return_Ccell_number(_product1_prolif,_product1_imm);
        model.set_Ccell_number(_product1_prolif,_product1_imm,prod1+1);
    }
    if ((_product2_prolif >=0)&&(_product2_imm >=0)){
        int prod2=model.return_Ccell_number(_product2_prolif,_product2_imm);
        model.set_Ccell_number(_product2_prolif,_product2_imm,prod2+1);
    }


    return true;

}

double Reaction::update_propensity(const Model& model){
    double n=reactant_factor(model);
    _propensity=_rate*n;
    return _propensity;
}

Reaction& Reaction::operator=(const Reaction& other){
    _reactant1_prolif=other.reactant1_p();
    _reactant1_imm=other.reactant1_i();
    _product1_prolif=other.product1_p();
    _product1_imm=other.product1_i();
    _product2_prolif=other.product2_p();
    _product2_imm=other.product2_i();
    _rate=other.rate();
    _used=other.used();
    return *this;
}

double Reaction::reactant_factor( const Model& model) const{
    return model.return_Ccell_number(reactant1_p(),reactant1_i());
}


bool Reaction::sufficient_reactants( const Model& model){
    return (model.return_Ccell_number(reactant1_p(),reactant1_i())>0);
}

std::ostream& Reaction::display(std::ostream& os){
    //TODO to be implemented
    os << "#reaction: "
        <<std::endl;
    return os;
}

// Reaction* AllReactions::return_random_reaction(const Model & model){
//
//     std::uniform_real_distribution<double> uniform01(0.,_ratesum);
//     double rnumb=uniform01(rng);
//
//     double sum=0;
//     for (int i =0; i< _all.size(); ++i){
//         sum +=_all[i]->rate()*model.get_Ccell_number(_all[i]->reactant_comp(),_all[i]->reactant1());
//         
//         if (sum > rnumb){
//             return _all[i];
//         }
//         
//
//     }
//
//     return _all.back();
//
// }

AllReactions::AllReactions(const Model & model, const Data & data):_ratesum(0.0){
    _all.clear();
    for (int i=0; i < data.return_max_prolif_types(); i++) {
        for (int j = 0; j < data.return_max_immune_types(); j++) {
            Reaction * normaldiff= new Division_without_mutation(i,j,data.get_prolif_rate(i));
            _all.push_back(normaldiff);
            Reaction * death= new Spontanious_cell_death(i,j,data.get_prolif_rate(i));
            _all.push_back(death);
        }
    }

    // std::cout <<"_all.size()="<<_all.size()<<std::endl;

}


