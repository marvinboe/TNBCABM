#ifndef __DATA_H__
#define __DATA_H__ 

#include <vector>

class Data{
    public:
        Data();

        double get_prolif_rate(unsigned int type);

    private:
        std::vector<double> prolif_rates;


};
#endif /* ifndef __DATA_H__ */
