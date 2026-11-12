#pragma once
#include <vector>
#include <cassert>
#include <iostream>

class Tensor;

class TensorView {
private:
    int* dataPtr;
    std::vector<size_t> dims;
    std::vector<size_t> steps;
    
public:
    TensorView(int* data, const std::vector<size_t>& d, const std::vector<size_t>& s)
        : dataPtr(data), dims(d), steps(s) {}

    int& operator()(const std::vector<size_t>& indices) {
        assert(indices.size() == dims.size());
        size_t idx = 0;
        for (size_t i = 0; i < indices.size(); i++) {
            idx += indices[i] * steps[i];
        }
        return dataPtr[idx];
    }

    int& operator()(size_t index) {
        assert(dims.size() == 1);
        return dataPtr[index];
    }
    
    TensorView operator[](size_t index) {
        assert(dims.size() > 0);
        int* newPtr = dataPtr + index * steps[0];
        std::vector<size_t> newDims(dims.begin() + 1, dims.end());
        std::vector<size_t> newSteps(steps.begin() + 1, steps.end());
        return TensorView(newPtr, newDims, newSteps);
    }

    Tensor asTensor() const;
    
    void printDebugInfo() const {
        std::cout << "View dimensions: ";
        for (size_t d : dims) std::cout << d << " ";
        std::cout << std::endl;
        std::cout << "View steps: ";
        for (size_t s : steps) std::cout << s << " ";
        std::cout << std::endl;
    }
};