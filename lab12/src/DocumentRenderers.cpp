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
