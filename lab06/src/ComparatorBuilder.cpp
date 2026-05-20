#include "ComparatorBuilder.h"
#include <algorithm>
#include <cctype>

// namespace StringUtils {
//     std::string toLower(const std::string& s) {
//         std::string result;
//         result.reserve(s.size());
//         for (unsigned char c : s) {
//             result.push_back(static_cast<char>(std::tolower(c)));
//         }
//         return result;
//     }
    
//     std::string removePrefix(const std::string& s, const std::string& prefix) {
//         if (s.size() >= prefix.size()) {
//             bool match = true;
//             for (size_t i = 0; i < prefix.size(); ++i) {
//                 unsigned char sc = static_cast<unsigned char>(s[i]);
//                 unsigned char pc = static_cast<unsigned char>(prefix[i]);
//                 if (std::tolower(sc) != std::tolower(pc)) {
//                     match = false;
//                     break;
//                 }
//             }
//             if(match) {
//                 return s.substr(prefix.size());
//             }
//         }
//         return s;
//     }
// }
static std::string toLower(const std::string& s) {
    std::string result;
    for (unsigned char c : s) {
        result.push_back(std::tolower(c));
    }
    return result;
}

static std::string removePrefix(const std::string& s, const std::string& prefix) {
    if (s.size() >= prefix.size()) {
        bool match = true;
        for (size_t i = 0; i < prefix.size(); ++i) {
            if (std::tolower(s[i]) != std::tolower(prefix[i])) {
                match = false;
                break;
            }
        }
        if (match) return s.substr(prefix.size());
    }
    return s;
}
bool CaseInsensitiveLess::operator()(const std::string& lhs, const std::string& rhs) const {
    return toLower(lhs) < toLower(rhs);
}

bool CaseSensitiveLess::operator()(const std::string& lhs, const std::string& rhs) const {
    return lhs < rhs;
}

bool LengthLess::operator()(const std::string& lhs, const std::string& rhs) const {
    return lhs.size() < rhs.size();
}


IgnorePrefixComparator::IgnorePrefixComparator(const StringComparator& base, std::string prefix)
    : base_(base), prefix_(std::move(prefix)) {}

bool IgnorePrefixComparator::operator()(const std::string& lhs, const std::string& rhs) const {
    return base_(removePrefix(lhs, prefix_),
                 removePrefix(rhs, prefix_));
}



void CompositeComparator::add(const StringComparator* cmp) {
    comparators_.push_back(cmp);
}

bool CompositeComparator::operator()(const std::string& ls, const std::string& rs) const {
    for(const StringComparator* cmp : comparators_) {
        bool ls_lt_rhs = (*cmp)(ls, rs);
        bool rs_lt_lhs = (*cmp)(rs, ls);
        
        if(ls_lt_rhs && !rs_lt_lhs) {
            return true;
        }
        if(rs_lt_lhs && !ls_lt_rhs) {
            return false;
        }
    }
    return false;
}



ComparatorBuilder& ComparatorBuilder::caseInsensitive() {
    order_.push_back(&ci_);
    return *this;
}

ComparatorBuilder& ComparatorBuilder::thenCaseSensitive() {
    order_.push_back(&cs_);
    return *this;
}

ComparatorBuilder& ComparatorBuilder::thenByLength() {
    order_.push_back(&len_);
    return *this;
}

ComparatorBuilder& ComparatorBuilder::ignorePrefix(const std::string& prefix) {
    if (order_.empty()) {
        return *this;
    }
    
    const StringComparator* last = order_.back();
    wrappers_.emplace_back(*last, prefix);
    order_.back() = &wrappers_.back();
    return *this;
}

CompositeComparator ComparatorBuilder::build() const {
    CompositeComparator cmp;
    for (const StringComparator* c : order_) {
        cmp.add(c);
    }
    return cmp;
}