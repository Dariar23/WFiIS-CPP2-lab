#pragma once
#include <map>
#include <vector>


struct DataSet{
    
    std::string zbiornik;
    std::vector<double> _vector;
    public:
    DataSet(std::string z,std::vector<double> vector): zbiornik(z),_vector(vector){} 

};
enum class SortingDirection {
    ASCENDING,
    DESCENDING
};


class DataStore{
    private:
    int _size;
    std::vector<DataSet> _data;
    public:
    DataStore( int size): _size(size) {}
    ~DataStore()=default;
    void addDataset(const std::string& s, std::vector<double> vector ) {
        _data.push_back({s, vector});
    }
    void addDataset(const DataSet& data) { //kopiuje
        _data.push_back(data);
    }
    void addDataset( DataSet&& data){//pszenosi
        _data.push_back(std::move(data));
    }
    auto begin() const{
        return _data.begin();
    }
    auto end() const{
        return _data.end();
    }
    auto begin(){
        return _data.begin();
    }
    auto end(){
        return _data.end();
    }
    template<typename Func>
    void sort(Func metric, SortingDirection direction) {

        if(_data.empty()){
            return;
        }
        
        std::vector<std::pair<double, int>> metrics;
        metrics.reserve(_data.size());
        
        for (size_t i = 0; i < _data.size(); ++i) {
            double value = metric(_data[i]._vector.begin(), _data[i]._vector.end());
            metrics.push_back({value, i});
        }
        
        if (direction == SortingDirection::ASCENDING) {
            std::sort(metrics.begin(), metrics.end(),
                [](const auto& a, const auto& b) { return a.first < b.first; });
        } else {
            std::sort(metrics.begin(), metrics.end(),
                [](const auto& a, const auto& b) { return a.first > b.first; });
        }
    
        std::vector<DataSet> sorted;
        sorted.reserve(_data.size());
        
        for (const auto& [value, index] : metrics) {
            sorted.push_back(std::move(_data[index]));
        }
        
        _data = std::move(sorted);
}
    


};
// std::ostream& operator<<(std::ostream& os, const DataSet& data) {
//     os<< data.zbiornik<<": [";
//     for(auto it=0; it!=data._vector.size(); it++){
//             std::cout<<data._vector[it]<<" ";
//         } std::cout<<" ]"<<std::endl;
// }

std::ostream& operator<<(std::ostream& os, const DataSet& ds) {
    os << ds.zbiornik << ": [";
    for (size_t i = 0; i < ds._vector.size(); ++i) {
        os << ds._vector[i];
        if(i + 1 < ds._vector.size()) {
            os << ", ";
        
        }
    }
    os << "]";
    return os;
}
