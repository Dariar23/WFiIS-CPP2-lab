#pragma once
#include "BaseDocumentRenderer.h"

class HtmlRenderer : public BaseDocumentRenderer {
public:
    std::string render(std::string const& content) const override;
};
