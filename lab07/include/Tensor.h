#pragma once
#include <vector>
#include <cassert>
#include <iostream>

class TensorView;

class Tensor {
private:
    std::vector<int> data;
    std::vector<size_t> dims;
    std::vector<size_t> steps;
    
    size_t getIndex(const std::vector<size_t>& indices) const {
        size_t result = 0;
        for (size_t i = 0; i < indices.size(); i++) {
            result += indices[i] * steps[i];
        }
        return result;
    }
    
public:
    Tensor(const std::vector<size_t>& dimensions, bool noMemory = false) {
        dims = dimensions;
       
        size_t total = 1;
        for (size_t d : dims) {
            total *= d;
        }
        data.resize(total);
    
        if(noMemory) {
            for (size_t i = 0; i < total; i++) {
                data[i] = 0;
            }
        }
        
        steps.resize(dims.size());
        size_t step = 1;
        for (int i = dims.size() - 1; i >= 0; i--) {
            steps[i] = step;
            step *= dims[i];
        }
    }
 
    int& operator()(const std::vector<size_t>& indices) {
        assert(indices.size() == dims.size());
        return data[getIndex(indices)];
    }
    
    int& operator()(size_t index) {
        assert(dims.size() == 1);
        return data[index];
    }
    
    TensorView operator[](size_t index);
    
    void printDebugInfo() const {
        std::cout << "Dimensions: ";
        for (size_t d : dims) std::cout << d << " ";
        std::cout << std::endl;
        
        std::cout << "Steps: ";
        for (size_t s : steps) std::cout << s << " ";
        std::cout << std::endl;
        
        std::cout << "Data: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
    }

    int* getData() { return data.data(); }
    const std::vector<size_t>& getDims() const { return dims; }
    const std::vector<size_t>& getSteps() const { return steps; }
};