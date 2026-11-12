#include "Tensor.h"
#include "TensorView.h"

TensorView Tensor::operator[](size_t index) {
    assert(dims.size() > 0);
    assert(index < dims[0]);
    
    int* newPtr = data.data() + index * steps[0];
    std::vector<size_t> newDims(dims.begin() + 1, dims.end());
    std::vector<size_t> newSteps(steps.begin() + 1, steps.end());
    
    return TensorView(newPtr, newDims, newSteps);
}