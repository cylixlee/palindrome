use std::collections::HashSet;

mod ffi {
    use std::ffi::c_char;

    extern "C" {
        fn solution(s: *const c_char, begin: i32, end: i32) -> i32;
        fn solution_cxx(s: *const c_char, n: i32) -> i32;
    }

    pub fn solve<S: AsRef<[u8]>>(string: &S) -> i32 {
        let slice = string.as_ref();
        let cstr = slice.as_ptr() as *const c_char;
        unsafe {
            solution(cstr, 0, slice.len() as i32)
        }
    }

    pub fn solve_cxx<S: AsRef<[u8]>>(string: S) -> i32 {
        let slice = string.as_ref();
        let cstr = slice.as_ptr() as *const c_char;
        unsafe {
            solution_cxx(cstr, slice.len() as i32)
        }
    }
}

const CROSSCHECK_TIME: usize = 26 * 26 * 26 * 26 * 26;
const STRING_CAPACITY: usize = 20;

fn main() {
    let mut hashset = HashSet::new();

    let mut count = 0;
    loop {
        let length = rand::random::<usize>() % STRING_CAPACITY + 1;
        let mut string = Vec::with_capacity(length);
        for _ in 0..length {
            let character = b'a' + rand::random::<u8>() % 5;
            string.push(character);
        }

        if hashset.contains(&string) {
            continue;
        }
        hashset.insert(string.clone());

        let legacy = ffi::solve(&string);
        let new = ffi::solve_cxx(&string);
        let s = unsafe { std::str::from_utf8_unchecked(&string) };
        if legacy != new {
            println!("\"{s}\" => (C) {legacy}, (CXX) {new}", );
            break;
        } else {
            if legacy != 0 {
                println!(
                    "[{}/{CROSSCHECK_TIME} -- {}%] ACCEPTED \"{s}\" {legacy} {new}",
                    hashset.len(),
                    ((hashset.len() as f64 / CROSSCHECK_TIME as f64) * 100.0) as usize,
                );
            }
        }
        count += 1;
        if count >= CROSSCHECK_TIME {
            break;
        }
    }
}
