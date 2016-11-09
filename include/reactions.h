#ifndef __REACTIONS_H
#define __REACTIONS_H

#include <vector>
#include "model.h"
#include "misc.h"
#include "data.h"


class Reaction { //X0+X1 ->Y0 + Y1
    public:
        Reaction():_reactant1(0),_reactant2(0),_reactant_comp(0), _product1(0), _product2(0), _r(-1.0), _used(0){};

        /** initialize Reaction:
         * r1: type of reactant 1
         * r2: type of reactant 2
         */
        Reaction(unsigned r1, unsigned r2,unsigned comp, unsigned p1, unsigned p2,double rate):_reactant1(r1),_reactant2(r2),_reactant_comp(comp), _product1(p1), _product2(p2), _r(rate), _used(0){};


        Reaction(const Reaction& other);
        virtual ~Reaction() {};

        int reactant1() const {return _reactant1;}
        int reactant_comp() const {return _reactant_comp;}
        int reactant2() const {return _reactant2;}
        int product1() const {return _product1;}
        int product2() const {return _product2;}
        double rate() const {return _r;}

        void setRate(double v) {_r=v;}

        unsigned used() const {return _used;}
        void incr_used() {_used += 1;}
        void reset_used() {_used = 0;}

        virtual Reaction& operator=(const Reaction& other);
        friend std::ostream & operator<<(std::ostream &o, Reaction& r){return r.display(o);}

        /** applies this reaction. */
        virtual bool apply(Model& model);

        /** are enough reactants available for this reaction? */
        virtual bool sufficient_reactants(const Model& model);

        /** returns number of cells for given reaction type */
        virtual double reactant_factor(const Model& model);
        virtual double reactant_factor2( const Model& model) const;


    protected:
        virtual std::ostream& display(std::ostream& os);
        int _reactant1;
        int _reactant2;
        unsigned int _reactant_comp;
        int _product1;
        int _product2;
        double _r; // rate constants of reaction (= compartment_rate * eps or compartmentr_rate * (1-eps))
        unsigned _used;
};


class Division_without_mutation : public Reaction {
    public:
        Division_without_mutation(int type, int comp, double rate):Reaction(type, -1,comp,type, type,rate){};
        Division_without_mutation(const Division_without_mutation& other):Reaction(other){};
        virtual ~Division_without_mutation() {};
};

class Division_with_mutation : public Reaction {
    public:
        Division_with_mutation(int type, int comp, double rate):Reaction(type, -1,comp,type, type+1,rate){};
        Division_with_mutation(const Division_with_mutation& other):Reaction(other){};
        virtual ~Division_with_mutation() {};
        // virtual Division_with_mutation& operator=(const Division_with_mutation& other);
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

    protected:
        std::vector<Reaction*> _all;
        double _ratesum;
};

#endif

