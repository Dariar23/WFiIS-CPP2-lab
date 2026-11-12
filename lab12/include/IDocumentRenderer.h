#pragma once
#include <string>

class IDocumentRenderer {
public:
    virtual ~IDocumentRenderer() = default;
    virtual std::string render(std::string const& content) const = 0;
};
