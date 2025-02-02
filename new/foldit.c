#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// ANSI escape codes for colors
#define COLOR_RESET "\x1b[0m"
#define COLOR_DIR "\x1b[34m"      // Blue for directories
#define COLOR_FILE "\x1b[32m"     // Green for files
#define COLOR_C "\x1b[31m"        // Red for C files
#define COLOR_PYTHON "\x1b[33m"   // Yellow for Python files
#define COLOR_JAVA "\x1b[35m"     // Magenta for Java files
#define COLOR_JS "\x1b[93m"       // Bright Yellow for JavaScript files
#define COLOR_HTML "\x1b[91m"     // Bright Red for HTML files
#define COLOR_CSS "\x1b[94m"      // Bright Blue for CSS files
#define COLOR_CPP "\x1b[36m"      // Cyan for C++ files
#define COLOR_PHP "\x1b[95m"      // Bright Magenta for PHP files
#define COLOR_GO "\x1b[96m"       // Bright Cyan for Go files
#define COLOR_SWIFT "\x1b[97m"    // White for Swift files
#define COLOR_PERL "\x1b[92m"     // Bright Green for Perl files
#define COLOR_RUST "\x1b[90m"     // Bright Black for Rust files

// Unicode icons for files and directories
#define ICON_DIR "📁"
#define ICON_FILE "📄"
#define ICON_C "🅒"
#define ICON_PYTHON "🐍"
#define ICON_JAVA "☕"
#define ICON_JS "🟨"
#define ICON_HTML "🌐"
#define ICON_CSS "🎨"
#define ICON_CPP "🅒➕"
#define ICON_PHP "🐘"
#define ICON_GO "🦫"
#define ICON_SWIFT "🐦"
#define ICON_PERL "🐪"
#define ICON_RUST "🦀"

// Function to get the color and icon for a file based on its extension
const char *get_file_style(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (dot) {
        if (strcmp(dot, ".c") == 0) {
            return COLOR_C ICON_C;
        } else if (strcmp(dot, ".py") == 0) {
            return COLOR_PYTHON ICON_PYTHON;
        } else if (strcmp(dot, ".java") == 0) {
            return COLOR_JAVA ICON_JAVA;
        } else if (strcmp(dot, ".js") == 0) {
            return COLOR_JS ICON_JS;
        } else if (strcmp(dot, ".html") == 0) {
            return COLOR_HTML ICON_HTML;
        } else if (strcmp(dot, ".css") == 0) {
            return COLOR_CSS ICON_CSS;
        } else if (strcmp(dot, ".cpp") == 0 || strcmp(dot, ".cxx") == 0 || strcmp(dot, ".cc") == 0) {
            return COLOR_CPP ICON_CPP;
        } else if (strcmp(dot, ".php") == 0) {
            return COLOR_PHP ICON_PHP;
        } else if (strcmp(dot, ".go") == 0) {
            return COLOR_GO ICON_GO;
        } else if (strcmp(dot, ".swift") == 0) {
            return COLOR_SWIFT ICON_SWIFT;
        } else if (strcmp(dot, ".pl") == 0 || strcmp(dot, ".pm") == 0) {
            return COLOR_PERL ICON_PERL;
        } else if (strcmp(dot, ".rs") == 0) {
            return COLOR_RUST ICON_RUST;
        }
    }
    return COLOR_FILE ICON_FILE; // Default for files
}

// Function to recursively print the directory tree
void print_tree(const char *dir_path, const char *prefix) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip "." and ".."
        }

        // Construct the full path of the entry
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        // Print the current entry with color and icon
        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                printf("%s├── %s%s %s%s\n", prefix, COLOR_DIR, ICON_DIR, entry->d_name, COLOR_RESET);
            } else {
                const char *style = get_file_style(entry->d_name);
                printf("%s├── %s %s%s\n", prefix, style, entry->d_name, COLOR_RESET);
            }
        }

        // If the entry is a directory, recursively print its contents
        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            char new_prefix[1024];
            snprintf(new_prefix, sizeof(new_prefix), "%s│   ", prefix); // Update prefix for children
            print_tree(full_path, new_prefix);
        }
    }

    closedir(dir);
}

// Function to display the tree structure of a directory
void display_tree(const char *dir_path) {
    printf("%s%s %s%s\n", COLOR_DIR, ICON_DIR, dir_path, COLOR_RESET); // Print the root directory
    print_tree(dir_path, "");
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-d") != 0) {
        printf("Usage: %s -d <directory_name>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[2];
    display_tree(dir_path);

    return 0;
}
