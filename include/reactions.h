#ifndef __REACTIONS_H
#define __REACTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "model.h"
#include "rangen.h"


class Reaction { //X0 ->X0 + X1 or X0 -> X0 + X0
public:
	Reaction():reactant(0), _product1(0), _product2(0), _r(-1.0), _used(0){};
	Reaction(const Reaction& other);
	virtual ~Reaction() {};
	
	unsigned int reactant() const {return _reactant;}
	unsigned int product1() const {return _product1;}
	unsigned int product2() const {return _product2;}
	double rate() const {return _r;}
	

	double probability(double dt) const {return _a * dt;}

	
        void setRate(double v) {_r=v;};
	
	unsigned used() const {return _used;}
	void incr_used() {_used += 1;}
	void reset_used() {_used = 0;}

	virtual Reaction& operator=(const Reaction& other);
	friend std::ostream & operator<<(std::ostream &o, Reaction& r){return r.display(o);}
	
        /** applies this reaction. */
	virtual bool apply(Model& model,double time);

	virtual bool sufficientReactants(Model& model);
        
        /** returns number of cells for given reaction type */
	virtual double reactantFactor(Model& model);
	
	
protected:
	virtual std::ostream& display(std::ostream& os);
	unsigned int _reactant;
	unsigned int _product1;
	unsigned int _product2;
	double _r; // rate constants of reaction (= compartment_rate * eps or compartmentr_rate * (1-eps))
	unsigned _used;
};


class division_without_mutation : public Reaction {
public:
	division_without_mutation(int type, double rate):Reaction(compartment,ct,compartment,ct,compartment,ct,rate){};
	division_without_mutation(const division_without_mutation& other):Reaction(other){};
	virtual ~division_without_mutation() {};
	virtual division_without_mutation& operator=(const division_without_mutation& other);
	
};


class AllReactions  {
public:
	AllReactions():_sumprop(0.0){_all.clear();}
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
	Reaction* operator[](unsigned pos);
	
	double propSum() const {return _sumprop;}
	void setPropSum(double v) { _sumprop = v;}

        void print(std::ostream &);
	
        std::vector<Reaction*>::iterator begin() {return _all.begin();}
        std::vector<Reaction*>::iterator end() {return _all.end();}
        std::vector<Reaction*>::const_iterator begin() const{return _all.begin();}
        std::vector<Reaction*>::const_iterator end() const {return _all.end();}
	
protected:
        std::vector<Reaction*> _all;
	double _sumprop;
};

#endif

