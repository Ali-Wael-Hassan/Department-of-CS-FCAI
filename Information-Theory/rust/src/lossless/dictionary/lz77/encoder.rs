use super::Token;

/// Stateless greedy encoder using a bounded backward search.
pub struct Encoder;

impl Encoder {
    /// Encodes arbitrary bytes as greedy LZ77 tokens.
    ///
    /// At each position, searches up to 4,096 preceding bytes for the longest
    /// match of at most 258 bytes. Equal-length matches keep the nearest source.
    /// Each match includes the following literal when one remains; positions
    /// without a match produce a literal-only token. Empty input yields no tokens.
    ///
    /// The brute-force search takes O(n * W * L) time in the worst case, where
    /// W is the search-window size and L is the match limit, and O(n) token space.
    pub fn encode(&self, input: &[u8]) -> Vec<Token> {
        let input_length = input.len();
        let mut pos: usize = 0;
        let mut data: Vec<Token> = Vec::new();

        let search_buffer: usize = 4096;
        let lookahead_buffer: usize = 258;

        while pos < input_length {
            let mut t = Token::from_values(0, 0, Some(input[pos]));

            let max_distance: usize = pos.min(search_buffer);
            let max_search_length: usize = lookahead_buffer.min(input_length - pos);

            for distance in 1..=max_distance {
                let mut len: usize = 0;

                // Reading from the original input also permits matches whose
                // source overlaps the sequence currently being encoded.
                while len < max_search_length {
                    if input[pos - distance + len] != input[pos + len] {
                        break;
                    }

                    len += 1;
                }

                if len > t.length {
                    t.length = len;
                    t.distance = distance;
                    t.character = input.get(pos + t.length).copied();
                }
            }

            // Consume the match and its trailing literal. If the match reaches
            // EOF, the extra step simply moves past the end and ends the loop.
            pos += t.length + 1;

            data.push(t);
        }

        data
    }
}
