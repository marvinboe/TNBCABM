#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>

class Model{
    public:
       
        
		Model(int initial_pt_size,int initial_mt_size,double num_micromets,double initial_pt_birthRate,double initial_mt_birthRate);
			
        double get_Ccell_number(int comp, int type);//count the number of cells with phenotype i in compartment comp
        void set_Ccell_number(int type,int comp, double number); // update the cell numbers for type i in compartment comp

        double get_immune_count(int comp);
		void set_immune_count(int comp, double number);

        /* print model data to output. */
        void output(double dt, std::ostream & os);//print the output

    private:
		
		std::vector<std::vector<double>> Tumour;
		


};
#endif /* ifndef __MODEL_H__ */










