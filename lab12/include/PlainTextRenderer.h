#pragma once
#include "BaseDocumentRenderer.h"

class PlainTextRenderer : public BaseDocumentRenderer {
public:
    std::string render(std::string const& content) const override;
};
