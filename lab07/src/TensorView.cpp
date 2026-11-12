#include "TensorView.h"
#include "Tensor.h"

Tensor TensorView::asTensor() const {
    Tensor result(dims, false);
    
    size_t total = 1;
    for (size_t d : dims) total *= d;
    
    for (size_t i = 0; i < total; i++) {
        result.getData()[i] = dataPtr[i];
    }
    
    return result;
}
