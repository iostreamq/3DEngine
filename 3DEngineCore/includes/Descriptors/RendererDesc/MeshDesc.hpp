#pragma once
#include <Descriptors/IDescriptor.hpp>


struct MeshDesc : public IDescriptor {
    
    MeshDesc(const std::vector<float>& _coords, unsigned _loc, int _size)
        : coords(_coords), loc(_loc), size(_size)
    {}

    std::vector<float> coords;
    unsigned loc;
    int size;
};
