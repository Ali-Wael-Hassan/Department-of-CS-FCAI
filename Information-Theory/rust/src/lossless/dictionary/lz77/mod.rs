//! Byte-oriented LZ77 with a 4,096-byte search window and 258-byte match limit.
//! Tokens stay in memory; no serialized format is defined.

mod benchmark;
mod decoder;
mod encoder;
mod token;

pub use benchmark::print_benchmark;
pub use decoder::Decoder;
pub use encoder::Encoder;
pub use token::Token;
