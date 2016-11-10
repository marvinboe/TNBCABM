#ifndef __REACTIONS_H
#define __REACTIONS_H

#include <vector>
#include "model.h"
#include "misc.h"
#include "data.h"


class Reaction { //X0 ->Y0 + Y1
    public:
        Reaction():_reactant1_prolif(0),_reactant1_imm(0), _product1_prolif(0), _product2_prolif(0), _rate(-1.0), _used(0){};

        /** initialize Reaction:
         * r1: type of reactant 1
         * r2: type of reactant 2
         */
        Reaction(unsigned r1p, unsigned r1i,// unsigned r2p, unsigned r2i,
                unsigned p1p, unsigned p1i, unsigned p2p, unsigned p2i,double rate):
            _reactant1_prolif(r1p),_reactant1_imm(r1i),//_reactant2_prolif(r1),_reactant2_imm(r1),
            _product1_prolif(p1p),_product1_imm(p1i),_product2_prolif(p2p),_product2_imm(p2i),
            _rate(rate), _used(0){};


        Reaction(const Reaction& other);
        virtual ~Reaction() {};

        int reactant1_p() const {return _reactant1_prolif;}
        int reactant1_i() const {return _reactant1_imm;}
        int product1_p() const {return _product1_prolif;;}
        int product1_i() const {return _product2_imm;}
        int product2_p() const {return _product2_prolif;;}
        int product2_i() const {return _product2_imm;}


        double rate() const {return _rate;}
        double propensity() const {return _propensity;}


        void setRate(double v) {_rate=v;}

        /** sets the actual propensity of the reaction. 
         * Usually propensity=rate*number_of_cells.*/
        void set_propensity(double v) {_propensity=v;}

        double update_propensity(const Model& model, const Data& data);
        unsigned used() const {return _used;}
        void incr_used() {_used += 1;}
        void reset_used() {_used = 0;}

        virtual Reaction& operator=(const Reaction& other);
        friend std::ostream & operator<<(std::ostream &o, Reaction& r){return r.display(o);}

        /** applies this reaction. */
        virtual bool apply(Model& model, const Data& data);

        /** are enough reactants available for this reaction? */
        virtual bool sufficient_reactants(const Model& model);

        /** returns number of cells for given reaction type */
        virtual double reactant_factor(const Model& model) const;

    protected:
        virtual std::ostream& display(std::ostream& os);
        int _reactant1_prolif;
        int _reactant1_imm;
        // int _reactant2_prolif;
        // int _reactant2_imm;
        int _product1_prolif;
        int _product1_imm;
        int _product2_prolif;
        int _product2_imm;
        double _rate; // rate constants of reaction (= compartment_rate * eps or compartmentr_rate * (1-eps))
        double _propensity;
        unsigned _used;
};


class Division_without_mutation : public Reaction {
    public:
        Division_without_mutation(int type_p, int type_i, double rate):Reaction(type_p,type_i,type_p,type_i,type_p,type_i,rate){};
        Division_without_mutation(const Division_without_mutation& other):Reaction(other){};
        virtual ~Division_without_mutation() {};
};


class Division_with_mutation : public Reaction {
public:
    Division_with_mutation(int type_p, int type_i, double rate):Reaction(type_p,type_i,type_p,type_i,-1,-1,rate){};
    Division_with_mutation(const Division_with_mutation& other):Reaction(other){};
    virtual ~Division_with_mutation() {};
    // virtual Division_with_mutation& operator=(const Division_with_mutation& other);
    bool apply(Model& model, const Data& data);
};

class Chemotherapy_cell_death : public Reaction {
public:
    Chemotherapy_cell_death(int type_p, int type_i,double rate):Reaction(type_p,type_i,-1,-1,-1,-1,rate){};
    Chemotherapy_cell_death(const Chemotherapy_cell_death& other):Reaction(other){};
    virtual ~Chemotherapy_cell_death(){};
    double update_propensity(const Model& model, const Data& data);
};

class Immune_cell_death : public Reaction {
public:
    Immune_cell_death(int type_p, int type_i,double rate):Reaction(type_p,type_i,-1,-1,-1,-1,rate){};
    Immune_cell_death(const Immune_cell_death& other):Reaction(other){};
    virtual ~Immune_cell_death(){};
    double update_propensity(const Model& model, const Data& data);
};


class Spontanious_cell_death : public Reaction {
    public:
    Spontanious_cell_death(int type_p, int type_i,double rate):Reaction(type_p,type_i,-1,-1,-1,-1,rate){};
    Spontanious_cell_death(const Spontanious_cell_death& other):Reaction(other){};
    virtual ~Spontanious_cell_death(){};
    double update_propensity(const Model& model, const Data& data);

};


class AllReactions  {
    public:
        AllReactions():_ratesum(0.0){_all.clear();}
        AllReactions(const Model& model, const Data & data);

        ~AllReactions(){
            while(_all.size() > 0){
                Reaction* r = _all[_all.size()-1];
                _all.pop_back();
                delete r;
            }
        }

        unsigned int size() const {return (unsigned)_all.size();}

        /** Adds reaction to the end of _all.
         * returns index of this element (=_all.size()-1) */
        unsigned int add(Reaction*);

        /** Returns pointer to reaction saved in _all[pos] */
        Reaction* operator[](unsigned pos){return _all[pos];}

        Reaction * return_random_reaction(const Model & model);

        double rate_sum() const {return _ratesum;}
        void set_rate_sum(double v) { _ratesum = v;}

        void print(std::ostream &);

        std::vector<Reaction*>::iterator begin() {return _all.begin();}
        std::vector<Reaction*>::iterator end() {return _all.end();}
        std::vector<Reaction*>::const_iterator begin() const{return _all.begin();}
        std::vector<Reaction*>::const_iterator end() const {return _all.end();}

        void set_total_propensity(double v){_total_propensity=v;}
        double return_total_propensity(){return _total_propensity;}

    protected:
        std::vector<Reaction*> _all;
        double _ratesum;
        double _total_propensity;
};

#endif

