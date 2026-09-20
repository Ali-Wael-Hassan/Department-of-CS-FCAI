namespace lossless {
namespace dict {

    public class CodecCLI {

        private readonly Dictionary<string, IDictCodec> codecs;

        public CodecCLI() {
            codecs = new Dictionary<string, IDictCodec>();
            foreach (Type t in System.Reflection.Assembly.GetExecutingAssembly().GetTypes()) {
                if (typeof(IDictCodec).IsAssignableFrom(t) && !t.IsAbstract && !t.IsInterface) {
                    IDictCodec codec = (IDictCodec)Activator.CreateInstance(t)!;
                    codecs[codec.Name.ToLower()] = codec;
                }
            }
        }

        public void Run() {
            Console.WriteLine("codec CLI - interactive");
            while (true) {
                Console.WriteLine();
                Console.WriteLine("commands: list | compress | decompress | quit");
                Console.Write("> ");
                string? cmd = Console.ReadLine()?.Trim().ToLower();
                switch (cmd) {
                    case null:
                    case "":
                    case "quit":
                    case "q":
                        return;
                    case "list":
                        ListCodecs();
                        break;
                    case "compress":
                        DoCompress();
                        break;
                    case "decompress":
                        DoDecompress();
                        break;
                    default:
                        Console.WriteLine($"unknown command '{cmd}'");
                        break;
                }
            }
        }

        private void ListCodecs() {
            int i = 1;
            foreach (KeyValuePair<string, IDictCodec> kv in codecs.OrderBy(kv => kv.Key))
                Console.WriteLine($"  {i++}. {kv.Value.Name}");
        }

        private IDictCodec? PickCodec() {
            ListCodecs();
            Console.Write("algorithm: ");
            string? sel = Console.ReadLine()?.Trim();
            if (sel == null)
                return null;
            if (int.TryParse(sel, out int n)) {
                int i = 1;
                foreach (KeyValuePair<string, IDictCodec> kv in codecs.OrderBy(kv => kv.Key)) {
                    if (i++ == n)
                        return kv.Value;
                }
                Console.WriteLine("invalid selection");
                return null;
            }
            if (codecs.TryGetValue(sel.ToLower(), out IDictCodec? codec) && codec != null)
                return codec;
            Console.WriteLine($"unknown algorithm '{sel}'");
            return null;
        }

        private string AskPath(string prompt, string def) {
            Console.Write($"{prompt} [{def}]: ");
            string? line = Console.ReadLine();
            return string.IsNullOrWhiteSpace(line) ? def : line.Trim();
        }

        private string? AskExistingFile(string prompt) {
            while (true) {
                string path = AskPath(prompt, "");
                if (path.Length == 0)
                    return null;
                if (File.Exists(path))
                    return path;
                Console.WriteLine($"file not found: {path}");
            }
        }

        private UInt16 AskUInt16(string prompt, UInt16 def) {
            Console.Write($"{prompt} [{def}]: ");
            string? line = Console.ReadLine();
            if (line == null)
                return def;
            if (UInt16.TryParse(line.Trim(), out UInt16 value))
                return value;
            Console.WriteLine($"'{line}' is not a number, using {def}");
            return def;
        }

        private void DoCompress() {
            IDictCodec? codec = PickCodec();
            if (codec == null)
                return;
            string? input = AskExistingFile("input file");
            if (input == null)
                return;
            string output = AskPath("output file", input + ".lz");
            UInt16 maxSearch = AskUInt16("max search", 4096);
            UInt16 maxLookahead = AskUInt16("max lookahead", 64);
            try {
                byte[] data = File.ReadAllBytes(input);
                LZTuple[] tuples = codec.Compress(data, maxSearch, maxLookahead);
                if (!codec.Save(output, tuples)) {
                    Console.WriteLine("failed to write output file");
                    return;
                }
                Console.WriteLine($"compressed {input} ({data.Length} bytes) -> {output} ({new FileInfo(output).Length} bytes)");
            } catch (Exception ex) {
                Console.WriteLine($"error: {ex.Message}");
            }
        }

        private void DoDecompress() {
            IDictCodec? codec = PickCodec();
            if (codec == null)
                return;
            string? input = AskExistingFile("input file");
            if (input == null)
                return;
            string output = AskPath("output file", input + ".out");
            try {
                byte[] data = codec.Load(input);
                File.WriteAllBytes(output, data);
                Console.WriteLine($"decompressed {input} -> {output} ({data.Length} bytes)");
            } catch (Exception ex) {
                Console.WriteLine($"error: {ex.Message}");
            }
        }
    }

}
}