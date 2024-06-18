fn main() {
    cc::Build::new()
        .file("src/trivial/palindrome.c")
        .compile("palindrome");
    cc::Build::new()
        .cpp(true)
        .file("src/trivial/palindrome.cxx")
        .compile("palindrome-cxx")
}