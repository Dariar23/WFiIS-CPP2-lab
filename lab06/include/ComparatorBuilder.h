#ifndef COMPARATOR_BUILDER_H
#define COMPARATOR_BUILDER_H

#include <string>
#include <vector>


// namespace StringUtils {
//     std::string toLower(const std::string& s);
//     std::string removePrefix(const std::string& s, const std::string& prefix);
// }
static std::string toLower(const std::string& s);
static std::string removePrefix(const std::string& s, const std::string& prefix);
class StringComparator {
public:
    virtual ~StringComparator() = default;
    virtual bool operator()(const std::string& lhs, const std::string& rhs) const = 0;
};

class CaseInsensitiveLess : public StringComparator {
public:
    bool operator()(const std::string& lhs, const std::string& rhs) const override;
};

class CaseSensitiveLess : public StringComparator {
public:
    bool operator()(const std::string& lhs, const std::string& rhs) const override;
};

class LengthLess : public StringComparator {
public:
    bool operator()(const std::string& lhs, const std::string& rhs) const override;
};


class IgnorePrefixComparator : public StringComparator {
private:
    const StringComparator& base_;
    std::string prefix_;
    
public:
    IgnorePrefixComparator(const StringComparator& base, std::string prefix);
    bool operator()(const std::string& lhs, const std::string& rhs) const override;
};


class CompositeComparator : public StringComparator {
private:
    std::vector<const StringComparator*> comparators_;
    
public:
    void add(const StringComparator* cmp);
    bool operator()(const std::string& lhs, const std::string& rhs) const override;
};


// class ComparatorBuilder {
// private:
//     CaseInsensitiveLess ci_;
//     CaseSensitiveLess cs_;
//     LengthLess len_;
//     std::vector<const StringComparator*> order_;
//     std::vector<IgnorePrefixComparator> wrappers_;
    
// public:
//     ComparatorBuilder& caseInsensitive();
//     ComparatorBuilder& thenCaseSensitive();
//     ComparatorBuilder& thenByLength();
//     ComparatorBuilder& ignorePrefix(const std::string& prefix);
//     CompositeComparator build() const;
// };
class ComparatorBuilder{
    private:
    CaseInsensitiveLess ci_;
    CaseSensitiveLess cs_;
    LengthLess len_;
    std::vector<StringComparator*> order_;
    std::vector<IgnorePrefixComparator> wrappers_;
    public:
    ComparatorBuilder& caseInsensitive();
    ComparatorBuilder& thenCaseSensitive();
    ComparatorBuilder& thenByLength();
    ComparatorBuilder& ignorePrefix(const std::string& prefix);
    ComparatorBuilder build() const;
};

#endif 