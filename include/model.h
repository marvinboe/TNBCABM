#ifndef __MODEL_H__
#define __MODEL_H__ 

#include <iostream>
#include <vector>

class Model{
    public:
        Model();

        double get_Ccell_number(int comp, int type);
        void set_Ccell_number(int type,int comp, double number);

        double get_immune_count(int comp);

        void set_immune_count(int comp, double number);

        /* print model data to output. */
        void output(double dt, std::ostream & os);

    private:


};
#endif /* ifndef __MODEL_H__ */










