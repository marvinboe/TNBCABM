#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>
#include "data.h"

class Model{
    public:

        Model(const Data& data);
        
        /** returns the number of cancer cells with proliferation type type_p
         * and immun type type_i.*/
        double return_Ccell_number(int type_p, int type_i) const;//count the number of cells with phenotype i in compartment comp

        /** sets the number of cancer cells with proliferation type type_p
         * and immun type type_i.*/
        void set_Ccell_number(int type_p, int type_i, double number); // update the cell numbers for type i in compartment comp
    
        void increment_Ccell_number(int type_p, int type_i, double number);

        double get_immune_count(int comp) const;
        void set_immune_count(int comp, double number);

        
        /** Returns the size of the primizry (deterministically modeled) tumor.*/
        double return_primary_size(){return _PrimaryTumourSize;}

        /** Returns anti tumor immune strength.*/
        double return_anti_immune()const{return _AntiTumImmuneSize;}

        /** Returns pro tumor immune strength.*/
        double return_pro_immune()const{return _ProTumImmuneSize;}
    
        double return_chemo_state()const{return _ChemoState;}

        /** Sets the size of the primizry (deterministically modeled) tumor.*/
        void set_primary_size(double v){_PrimaryTumourSize=v;}

        /** Sets anti tumor immune strength.*/
        void set_anti_immune(double v){_AntiTumImmuneSize=v;}

        /** Sets pro tumor immune strength.*/
        void set_pro_immune(double v){_ProTumImmuneSize=v;}

        /* print model data to output. */
        void output(double dt, std::ostream & os1, std::ostream & os2) const;//print the output

        std::vector<std::vector<double>> return_all_cells() const {return _cells;}

        /** Return total number of cancer cells in system. */
        double return_total_cellnumber() const;
    private:
		
    /** _cells[type_p][type_i]*/
    std::vector<std::vector<double>> _cells;

    double _PrimaryTumourSize;
    double _AntiTumImmuneSize;
    double _ProTumImmuneSize;
    double _ChemoState;
		


};
#endif /* ifndef __MODEL_H__ */










