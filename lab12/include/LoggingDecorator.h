#pragma once
#include "RendererDecorator.h"
#include <iostream>

class LoggingDecorator : public RendererDecorator {
public:
    explicit LoggingDecorator(IDocumentRenderer const& renderer): RendererDecorator(renderer) {}

    std::string render(std::string const& content) const override;
};
