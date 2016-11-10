#include "reactions.h"


bool Reaction::apply(Model& model, const Data& data){


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

double Reaction::update_propensity(const Model& model, const Data& data){
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


double Immune_division_without_mutation::update_propensity(const Model& model, const Data& data){
    double n=reactant_factor(model);
    // update rate
    // TBD take current chemo state from model
    _rate = model.return_pro_immune() * data.get_immune_sensitivity_rate(_reactant1_imm);
    _propensity=_rate*n;
    return _propensity;
}


bool Division_with_mutation::apply(Model& model, const Data& data){
    std::uniform_real_distribution<double> uniform01(0.,1.);
    int new_prolif;
    int new_imm;
    
    if ((_reactant1_prolif >=0)&&(_reactant1_imm >=0)){
        int react1=model.return_Ccell_number(_reactant1_prolif,_reactant1_imm);
        model.set_Ccell_number(_reactant1_prolif,_reactant1_imm,react1-1);
    }
    
    // if prolif mutation
    if(uniform01(rng) > 0.5){
        if(uniform01(rng) > 0.5){
            new_prolif = std::min(_reactant1_prolif + 1, data.return_max_prolif_types() - 1);
        } else {
            new_prolif = std::max(_reactant1_prolif - 1, 0);
        }
        model.increment_Ccell_number(new_prolif,_reactant1_imm,1);
    } else {
        if(uniform01(rng) > 0.5){
            new_imm = std::min(_reactant1_imm+ 1, data.return_max_prolif_types() - 1);
        } else {
            new_imm = std::max(_reactant1_imm - 1, 0);
        }
        model.increment_Ccell_number(_reactant1_prolif,new_imm,1);
    }
    
    return true;
}

bool Immune_division_with_mutation::apply(Model& model, const Data& data){
    std::uniform_real_distribution<double> uniform01(0.,1.);
    int new_prolif;
    int new_imm;
    
    if ((_reactant1_prolif >=0)&&(_reactant1_imm >=0)){
        int react1=model.return_Ccell_number(_reactant1_prolif,_reactant1_imm);
        model.set_Ccell_number(_reactant1_prolif,_reactant1_imm,react1-1);
    }
    
    // if prolif mutation
    if(uniform01(rng) > 0.5){
        if(uniform01(rng) > 0.5){
            new_prolif = std::min(_reactant1_prolif + 1, data.return_max_prolif_types() - 1);
        } else {
            new_prolif = std::max(_reactant1_prolif - 1, 0);
        }
        model.increment_Ccell_number(new_prolif,_reactant1_imm,1);
    } else {
        if(uniform01(rng) > 0.5){
            new_imm = std::min(_reactant1_imm+ 1, data.return_max_prolif_types() - 1);
        } else {
            new_imm = std::max(_reactant1_imm - 1, 0);
        }
        model.increment_Ccell_number(_reactant1_prolif,new_imm,1);
    }
    
    return true;
}

double Immune_division_with_mutation::update_propensity(const Model& model, const Data& data){
    double n=reactant_factor(model);
    // update rate
    _rate = model.return_pro_immune() * data.get_immune_sensitivity_rate(_reactant1_imm);
    _propensity=_rate*n;
    return _propensity;
}

double Chemotherapy_cell_death::update_propensity(const Model& model, const Data& data){
    double n=reactant_factor(model);
    // update rate
    // TBD take current chemo state from model
    _rate = model.return_chemo_state() * data.get_death_chemo() * data.get_prolif_rate(_reactant1_prolif);
    _propensity=_rate*n;
    return _propensity;
}

double Immune_cell_death::update_propensity(const Model& model, const Data& data){
    double n=reactant_factor(model);
    // update rate
    _rate = model.return_anti_immune() * data.get_immune_sensitivity_rate(_reactant1_imm);
    _propensity=_rate*n;
    return _propensity;
}

double Spontanious_cell_death::update_propensity(const Model& model, const Data& data){
    double n=reactant_factor(model);
    double n_tot=model.return_total_cellnumber();
    // update rate
    _propensity=_rate*n*n_tot;
    return _propensity;
}

std::ostream& Reaction::display(std::ostream& os){
    //TODO to be implemented
    os << "#reaction: "
        <<std::endl;
    return os;
}

AllReactions::AllReactions(const Model & model, const Data & data):_ratesum(0.0){
    _all.clear();
    for (int i=0; i < data.return_max_prolif_types(); i++) {
        for (int j = 0; j < data.return_max_immune_types(); j++) {
            Reaction * normaldiff= new Division_without_mutation(i,j,data.get_prolif_rate(i) * (1 - data.get_mutation_rate()));
            _all.push_back(normaldiff);
            Reaction * immunenormaldiff= new Immune_division_without_mutation(i,j,(data.get_initial_pro_tumour_immune_cellnumber() * data.get_immune_sensitivity_rate(j)) * (1 - data.get_mutation_rate()));
            _all.push_back(immunenormaldiff);
            Reaction * mutationdiff= new Division_with_mutation(i,j,data.get_prolif_rate(i) * data.get_mutation_rate());
            _all.push_back(mutationdiff);
            Reaction * Immunemutationdiff= new Immune_division_with_mutation(i,j,(data.get_initial_pro_tumour_immune_cellnumber() * data.get_immune_sensitivity_rate(j)) * data.get_mutation_rate());
            _all.push_back(Immunemutationdiff);
            Reaction * chemo_death= new Chemotherapy_cell_death(i,j, data.get_chemo_state() * data.get_death_chemo() * data.get_prolif_rate(i));
            _all.push_back(chemo_death);
            Reaction * immune_death= new Immune_cell_death(i,j, data.get_initial_anti_tumour_immune_cellnumber()  * data.get_immune_sensitivity_rate(j));
            _all.push_back(immune_death);
            Reaction * death= new Spontanious_cell_death(i,j, data.get_spontaneous_cell_death_rate());
            _all.push_back(death);
        }
    }

    // std::cout <<"_all.size()="<<_all.size()<<std::endl;

}


