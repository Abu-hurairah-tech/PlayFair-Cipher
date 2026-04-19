#ifndef COLORS_H
#define COLORS_H

#include <string>

namespace Color
{
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string DIM = "\033[2m";
    const std::string UNDERLINE = "\033[4m";

    // Main Colors
    const std::string GREEN = "\033[32m";   // Success/Positive
    const std::string RED = "\033[31m";     // Errors/Warning
    const std::string CYAN = "\033[36m";    // Info/Headers
    const std::string YELLOW = "\033[33m";  // Inputs/Prompts
    const std::string BLUE = "\033[34m";    // Data/Content
    const std::string MAGENTA = "\033[35m"; // Special/Important
    const std::string WHITE = "\033[37m";   // Normal text

    // Bright Colors
    const std::string BRIGHT_GREEN = "\033[92m";   // Success emphasis
    const std::string BRIGHT_RED = "\033[91m";     // Critical errors
    const std::string BRIGHT_CYAN = "\033[96m";    // Headers
    const std::string BRIGHT_YELLOW = "\033[93m";  // Highlights
    const std::string BRIGHT_BLUE = "\033[94m";    // Data emphasis
    const std::string BRIGHT_MAGENTA = "\033[95m"; // Special emphasis

    // Special Effects
    const std::string REVERSE = "\033[7m"; // Highlight
}

#endif