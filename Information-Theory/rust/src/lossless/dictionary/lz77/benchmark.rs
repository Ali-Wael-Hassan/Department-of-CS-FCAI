use super::Token;

/// Prints token-count statistics relative to the original byte count.
///
/// `Ratio` is bytes per token, and `Saved` is the percentage reduction from the
/// byte count to the token count. Neither measures actual compressed byte size:
/// each in-memory token contains multiple fields and no serialization is defined.
/// A zero denominator yields zero for the corresponding metric.
pub fn print_benchmark(original: &[u8], tokens: &[Token]) {
    let original_size = original.len();
    let token_count = tokens.len();

    let reduction = if original_size > 0 {
        (1.0 - token_count as f64 / original_size as f64) * 100.0
    } else {
        0.0
    };

    let ratio = if token_count > 0 {
        original_size as f64 / token_count as f64
    } else {
        0.0
    };

    println!("========== LZ77 Benchmark ==========");
    println!("Original size : {} bytes", original_size);
    println!("Token count   : {} tokens", token_count);
    println!("Ratio         : {:.2}:1", ratio);
    println!("Saved         : {:.2}%", reduction);
    println!("====================================");
}
