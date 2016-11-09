#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>
#include "data.h"

class Model{
    public:

        Model(const Data& data);
        
		Model(int initial_pt_size,int initial_mt_size,double num_micromets,double initial_pt_birthRate,double initial_mt_birthRate);
			
        double get_Ccell_number(int comp, int type) const;//count the number of cells with phenotype i in compartment comp
        void set_Ccell_number(int type,int comp, double number); // update the cell numbers for type i in compartment comp

        double get_immune_count(int comp) const;
		void set_immune_count(int comp, double number);

        /* print model data to output. */
        void output(double dt, std::ostream & os) const;//print the output


    private:
		
		std::vector<std::vector<double>> Tumour;
		


};
#endif /* ifndef __MODEL_H__ */










