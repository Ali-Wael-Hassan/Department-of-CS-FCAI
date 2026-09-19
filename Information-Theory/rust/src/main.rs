//! A byte-oriented LZ77 demonstration (birdlzzRust).
//!
//! Run with `cargo run` from the rust directory.

mod lossless;

use lossless::dictionary::lz77::{Decoder, Encoder, print_benchmark};

/// Runs a round trip on sample UTF-8 text and prints tokens and size statistics.
fn main() {
    let input = b"this is random charachters";

    let encoder = Encoder;
    let tokens = encoder.encode(input);

    println!("{tokens:#?}");

    let decoder = Decoder;
    let output = String::from_utf8(decoder.decode(&tokens)).unwrap();

    println!("the decoded text : {:?}", output);

    print_benchmark(input, &tokens);
}
