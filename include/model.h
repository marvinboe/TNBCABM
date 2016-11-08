#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>

class Model{
    public:
        Model();

        unsigned int get_Ccell_number(int comp, int type);

        unsigned int set_Ccell_number(int type,int comp, int number);

        /* print model data to output. */
        void output(double dt, std::ostream & os);

    private:


};
#endif /* ifndef __MODEL_H__ */










