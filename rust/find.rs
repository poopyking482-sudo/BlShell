use std::ffi::CStr;
use std::fs;
use std::os::raw::c_char;
use std::path::Path;

// Explicitly tell Rust to layout this memory EXACTLY like the C struct
#[repr(C)]
pub struct RustFindResult {
    pub match_path: [c_char; 256],
    pub line_number: i32,
}

#[no_mangle]
pub unsafe extern "C" fn rust_find_file(
    dir: *const c_char,
    term: *const c_char,
    results: *mut RustFindResult,
    max_results: i32,
) -> i32 {
    // 1. Safety Checks: Protect against null pointers passed from C
    if dir.is_null() || term.is_null() || results.is_null() || max_results <= 0 {
        return 0;
    }

    // 2. Convert incoming C strings into safe Rust string slices
    let c_dir_str = match CStr::from_ptr(dir).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };
    let c_term_str = match CStr::from_ptr(term).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };

    let mut match_count = 0;

    // 3. Kick off the fast recursive scanner
    scan_directory(
        Path::new(c_dir_str),
        c_term_str,
        results,
        max_results,
        &mut match_count,
    );

    match_count
}

// Internal, high-performance recursive directory walker
unsafe fn scan_directory(
    dir: &Path,
    term: &str,
    results: *mut RustFindResult,
    max_results: i32,
    match_count: &mut i32,
) {
    // Stop scanning immediately if the C array is completely full
    if *match_count >= max_results {
        return;
    }

    // Read directory contents using optimized iterator pipelines
    if let Ok(entries) = fs::read_dir(dir) {
        for entry in entries.flatten() {
            let path = entry.path();

            if path.is_dir() {
                // Safely recurse down into the next folder level
                scan_directory(&path, term, results, max_results, match_count);
            } else if let Some(filename) = path.file_name().and_then(|s| s.to_str()) {
                // Check if the file name contains our search string
                if filename.contains(term) {
                    let path_str = path.to_string_lossy();
                    
                    // Get the pointer to the specific slot in our C array
                    let slot = results.offset(*match_count as isize);

                    // Copy the path string safely into the fixed-size C char array
                    let bytes = path_str.as_bytes();
                    let len = bytes.len().min(255); // Save room for null terminator
                    
                    for i in 0..len {
                        (*slot).match_path[i] = bytes[i] as c_char;
                    }
                    (*slot).match_path[len] = 0; // Explicit null termination
                    (*slot).line_number = 0;     // Placeholder or tracking

                    *match_count += 1;
                    if *match_count >= max_results {
                        return;
                    }
                }
            }
        }
    }
}
