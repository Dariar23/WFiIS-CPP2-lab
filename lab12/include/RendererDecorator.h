#pragma once
#include "IDocumentRenderer.h"

class RendererDecorator : public IDocumentRenderer {
protected:
    IDocumentRenderer const& inner;

public:
    explicit RendererDecorator(IDocumentRenderer const& renderer)
        : inner(renderer) {}

    virtual ~RendererDecorator() = default;
};
