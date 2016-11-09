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

Reaction& Reaction::operator=(const Reaction& other){
    _reactant1=other.reactant1();
    _reactant2=other.reactant2();
    _reactant_comp=other.reactant_comp();
    _product1=other.product1();
    _product2=other.product2();
    _r=other.rate();
    _used=other.used();
    return *this;
}

double Reaction::reactant_factor( const Model& model){
    return model.get_Ccell_number(reactant_comp(),reactant1());
}

bool Reaction::sufficient_reactants( const Model& model){
    return (model.get_Ccell_number(reactant_comp(),reactant1())>0);
}

std::ostream& Reaction::display(std::ostream& os){
    os << "#reaction: "<<_reactant_comp<<" "<<_reactant1<<" "<<_reactant2<<" "
        <<_product1<<" "<<_product2<<" "
        <<std::endl;
    return os;
}

Reaction* AllReactions::return_random_reaction(const Model & model){

    std::uniform_real_distribution<double> uniform01(0.,_ratesum);
    double rnumb=uniform01(rng);

    double sum=0;
    for (int i =0; i< _all.size(); ++i){
        sum +=_all[i]->rate()*model.get_Ccell_number(_all[i]->reactant_comp(),_all[i]->reactant1());
        
        if (sum > rnumb){
            return _all[i];
        }
        

    }

    return _all.back();

}

AllReactions::AllReactions(const Model & model, const Data & data):_ratesum(0.0){
    _all.clear();
    for (int comp_i=0; comp_i<5; ++comp_i){
        Reaction * normaldiff= new Division_without_mutation(0,comp_i,data.get_prolif_rate(0));
        _all.push_back(normaldiff);

    }
}
