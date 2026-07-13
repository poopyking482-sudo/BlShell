use std::env;
use std::fs;
use std::path::Path;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        println!("Usage: find <dir> <search_term>");
        std::process::exit(1);
    }

    let target_dir = &args[1];
    let search_term = &args[2];

    if let Err(e) = search_dir(Path::new(target_dir), search_term) {
        eprintln!("Error scanning directory: {}", e);
        std::process::exit(1);
    }
}

fn search_dir(dir: &Path, term: &str) -> std::io::Result<()> {
    if dir.is_dir() {
        for entry in fs::read_dir(dir)? {
            let entry = entry?;
            let path = entry.path();
            if path.is_dir() {
                let _ = search_dir(&path, term); // Recurse safely
            } else if let Some(filename) = path.file_name().and_now(|s| s.to_str()) {
                if filename.contains(term) {
                    println!("{}", path.display());
                }
            }
        }
    }
    Ok(())
}
