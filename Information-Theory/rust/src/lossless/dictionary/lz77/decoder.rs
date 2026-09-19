use super::Token;

/// Stateless decoder for the in-memory LZ77 token representation.
pub struct Decoder;

impl Decoder {
    /// Reconstructs bytes from tokens, returning an empty vector for empty input.
    ///
    /// Zero-distance tokens emit only their optional literal; their length is
    /// ignored. Nonzero distances must refer to bytes already in the output.
    /// Overlapping matches are supported by copying one byte at a time.
    ///
    /// # Panics
    ///
    /// Malformed tokens can panic if a distance exceeds the current output
    /// length or if computing the copy range overflows. Use valid tokens such
    /// as those produced by [`super::Encoder::encode`].
    pub fn decode(&self, tokens: &[Token]) -> Vec<u8> {
        let mut decompressed: Vec<u8> = Vec::new();

        tokens.iter().for_each(|t| {
            if t.distance == 0 {
                if let Some(ch) = t.character {
                    decompressed.push(ch);
                }
            } else {
                let start_pos = decompressed.len() - t.distance;
                let end_pos = start_pos + t.length;

                // Newly appended bytes can become the source of later copies
                // in this same match, allowing lengths greater than distance.
                for i in start_pos..end_pos {
                    let byte = decompressed[i];
                    decompressed.push(byte);
                }

                if let Some(ch) = t.character {
                    decompressed.push(ch);
                }
            }
        });

        decompressed
    }
}
