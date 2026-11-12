#pragma once
#include "RendererDecorator.h"
#include <string>

class HeaderDecorator : public RendererDecorator {
    std::string header;

public:
    HeaderDecorator(std::string header, IDocumentRenderer const& renderer): RendererDecorator(renderer), header(std::move(header)) {}

    std::string render(std::string const& content) const override;
};
