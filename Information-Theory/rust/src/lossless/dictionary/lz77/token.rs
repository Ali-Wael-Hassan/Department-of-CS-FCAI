/// An LZ77 back-reference followed by an optional literal byte.
///
/// A literal-only token has zero distance and length. A match reaching the end
/// of the input has no trailing literal (`character` is `None`).
#[derive(Debug)]
pub struct Token {
    /// Number of bytes to step backward from the current output position.
    pub distance: usize,
    /// Number of bytes to copy from the back-reference.
    pub length: usize,
    /// Literal byte to append after the match, if present.
    pub character: Option<u8>,
}

impl Token {
    /// Creates a token from its fields without validating the back-reference.
    pub fn from_values(distance: usize, length: usize, character: Option<u8>) -> Self {
        Self {
            distance,
            length,
            character,
        }
    }
}
