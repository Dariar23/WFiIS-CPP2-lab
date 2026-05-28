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

#pragma once
#include "PlainTextRenderer.h"
#include "HtmlRenderer.h"
#include "HeaderDecorator.h"
#include "LoggingDecorator.h"


#pragma once
#include "RendererDecorator.h"
#include <string>

class HeaderDecorator : public RendererDecorator {
    std::string header;

public:
    HeaderDecorator(std::string header, IDocumentRenderer const& renderer): RendererDecorator(renderer), header(std::move(header)) {}

    std::string render(std::string const& content) const override;
};

#pragma once
#include "BaseDocumentRenderer.h"

class HtmlRenderer : public BaseDocumentRenderer {
public:
    std::string render(std::string const& content) const override;
};

#pragma once
#include <string>

class IDocumentRenderer {
public:
    virtual ~IDocumentRenderer() = default;
    virtual std::string render(std::string const& content) const = 0;
};

#pragma once
#include "RendererDecorator.h"
#include <iostream>

class LoggingDecorator : public RendererDecorator {
public:
    explicit LoggingDecorator(IDocumentRenderer const& renderer): RendererDecorator(renderer) {}

    std::string render(std::string const& content) const override;
};

#pragma once
#include "BaseDocumentRenderer.h"

class PlainTextRenderer : public BaseDocumentRenderer {
public:
    std::string render(std::string const& content) const override;
};

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


#include "PlainTextRenderer.h"
#include "HtmlRenderer.h"
#include "HeaderDecorator.h"
#include "LoggingDecorator.h"

// PlainTextRenderer
std::string PlainTextRenderer::render(std::string const& content) const {
    return normalize(content);
}

// HtmlRenderer
std::string HtmlRenderer::render(std::string const& content) const {
    std::string normalized = normalize(content);

    return "<html>\n<body>\n" +
           normalized +
           "\n</body>\n</html>";
}


// HeaderDecorator
std::string HeaderDecorator::render(std::string const& content) const {
    // Header NIE jest normalizowany
    return header + "\n" + inner.render(content);
}


// LoggingDecorator
std::string LoggingDecorator::render(std::string const& content) const {
    std::cout << "[LOG] Rendering document with content:\n"
              << content << "\n";

    std::string result = inner.render(content);

    std::cout << "[LOG] Result is: \n"
              << result << "\n";

    return result;
}
