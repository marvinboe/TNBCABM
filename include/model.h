#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>

class Model{
    public:
        Model();

        unsigned int get_Ccell_number(int comp, int type);
        unsigned int get_Ccell_type(int comp);

        unsigned int set_Ccell_number(int comp);
        unsigned int set_Ccell_type(int comp);

        /* print model data to output. */
        void output(double dt, std::ostream & os);

    private:
        std::vector<unsigned int> cellnumbers;
        std::vector<int> celltypes;


};
#endif /* ifndef __MODEL_H__ */










