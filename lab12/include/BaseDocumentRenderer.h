#pragma once
#include "IDocumentRenderer.h"
#include <string>
#include <algorithm>
#include <cctype>

class BaseDocumentRenderer : public IDocumentRenderer {
protected:
    static std::string normalize(std::string content) {
        for (char& c : content) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return content;
    }
};