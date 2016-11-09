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

        double get_immune_count(int comp) const;
	void set_immune_count(int comp, double number);

        /* print model data to output. */
        void output(double dt, std::ostream & os) const;//print the output


    private:
		
    std::vector<std::vector<double>> _cells;
		


};
#endif /* ifndef __MODEL_H__ */










