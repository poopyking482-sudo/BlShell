#ifndef BL_RUST_BRIDGE_H
#define BL_RUST_BRIDGE_H

// A structure matching data we want to pass between C and Rust
typedef struct {
    char match_path[256];
    int line_number;
} RustFindResult;

// Tell C that these functions are implemented externally (in Rust!)
extern int rust_find_file(const char *dir, const char *term, RustFindResult *results, int max_results);

#endif
