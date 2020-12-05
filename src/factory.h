
#include <vector>

enum class StructureType {mine, factory};

class Structure
{
    private:
    public:
    int owner = 0;
    int size = 0;

    std::vector<ProductionQueue> queue;

};

class ProductionQueue
{

};

class ProductionRecepie
{

};
