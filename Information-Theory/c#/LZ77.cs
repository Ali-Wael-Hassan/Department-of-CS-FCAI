namespace lossless {
namespace dict {

    public class LZ77 : IDictCodec {

        public string Name { get { return "LZ77"; } }

        public LZTuple[] Compress(byte[] data, UInt16 maxSearch, UInt16 maxLookahead) {
            if (data == null)
                throw new ArgumentNullException(nameof(data));
            if (maxSearch < 1)
                throw new ArgumentOutOfRangeException(nameof(maxSearch), "maxSearch must be at least 1");
            if (maxLookahead < 2)
                throw new ArgumentOutOfRangeException(nameof(maxLookahead), "maxLookahead must be at least 2");
            if (data.Length == 0)
                return Array.Empty<LZTuple>();

            List<LZTuple> tuples = new List<LZTuple>();
            for (int pos = 0; pos < data.Length; ) {
                int searchStart = Math.Max(0, pos - maxSearch);

                UInt16 bestDistance = 0;
                UInt16 bestLength = 0;
                for (int d = searchStart; d < pos; d++) {
                    int dist = pos - d;
                    int len = 0;
                    while (len < maxLookahead && pos + len < data.Length && data[d + (len % dist)] == data[pos + len])
                        len++;
                    if (len > bestLength) {
                        bestLength = (UInt16)len;
                        bestDistance = (UInt16)dist;
                        if (len == maxLookahead || pos + len == data.Length)
                            break;
                    }
                }

                int room = data.Length - pos - 1;
                if (bestLength > room)
                    bestLength = (UInt16)room;

                if (bestLength >= 2) {
                    tuples.Add(new LZTuple(bestDistance, bestLength, data[pos + bestLength]));
                    pos += bestLength + 1;
                } else {
                    tuples.Add(new LZTuple(0, 0, data[pos]));
                    pos += 1;
                }
            }

            return tuples.ToArray();
        }

        public byte[] Decompresss(LZTuple[] tuples) {
            if (tuples == null)
                throw new ArgumentNullException(nameof(tuples));

            List<byte> output = new List<byte>();
            foreach (LZTuple t in tuples) {
                if (t.IsLiteral) {
                    output.Add(t.Next);
                } else {
                    for (int i = 0; i < t.Length; i++)
                        output.Add(output[output.Count - t.Distance]);
                    output.Add(t.Next);
                }
            }
            return output.ToArray();
        }

        public bool Save(String pathname, LZTuple[] tuples) {
            if (pathname == null)
                throw new ArgumentNullException(nameof(pathname));
            if (tuples == null)
                throw new ArgumentNullException(nameof(tuples));

            UInt16 maxDistance = 0;
            UInt16 maxLength = 0;
            foreach (LZTuple t in tuples) {
                if (t.Distance > maxDistance) maxDistance = t.Distance;
                if (t.Length > maxLength) maxLength = t.Length;
            }

            int distBits = BitWidth(maxDistance);
            int lenBits = BitWidth(maxLength);

            List<byte> bytes = new List<byte>();
            bytes.Add((byte)distBits);
            bytes.Add((byte)lenBits);
            bytes.AddRange(BitConverter.GetBytes((UInt32)tuples.Length));

            int buffer = 0;
            int bitCount = 0;
            foreach (LZTuple t in tuples) {
                WriteBits(t.Distance, distBits, ref buffer, ref bitCount, bytes);
                WriteBits(t.Length, lenBits, ref buffer, ref bitCount, bytes);
                WriteBits(t.Next, 8, ref buffer, ref bitCount, bytes);
            }
            if (bitCount > 0)
                bytes.Add((byte)(buffer << (8 - bitCount)));

            try {
                File.WriteAllBytes(pathname, bytes.ToArray());
            } catch {
                return false;
            }
            return true;
        }

        public byte[] Load(String pathname) {
            if (pathname == null)
                throw new ArgumentNullException(nameof(pathname));

            byte[] bytes = File.ReadAllBytes(pathname);

            int distBits = bytes[0];
            int lenBits = bytes[1];
            UInt32 count = BitConverter.ToUInt32(bytes, 2);

            LZTuple[] tuples = new LZTuple[count];
            int byteIndex = 6;
            int bitOfs = 0;
            for (int i = 0; i < count; i++) {
                UInt16 distance = ReadBits(distBits, bytes, ref byteIndex, ref bitOfs);
                UInt16 length = ReadBits(lenBits, bytes, ref byteIndex, ref bitOfs);
                byte next = (byte)ReadBits(8, bytes, ref byteIndex, ref bitOfs);
                tuples[i] = new LZTuple(distance, length, next);
            }

            return Decompresss(tuples);
        }

        private static int BitWidth(UInt16 value) {
            int width = 0;
            while (value > 0) {
                width++;
                value >>= 1;
            }
            return width;
        }

        private static void WriteBits(UInt16 value, int width, ref int buffer, ref int bitCount, List<byte> bytes) {
            for (int i = width - 1; i >= 0; i--) {
                buffer = (buffer << 1) | ((value >> i) & 1);
                bitCount++;
                if (bitCount == 8) {
                    bytes.Add((byte)buffer);
                    buffer = 0;
                    bitCount = 0;
                }
            }
        }

        private static UInt16 ReadBits(int width, byte[] bytes, ref int byteIndex, ref int bitOfs) {
            UInt16 value = 0;
            for (int i = 0; i < width; i++) {
                value = (UInt16)((value << 1) | ((bytes[byteIndex] >> (7 - bitOfs)) & 1));
                bitOfs++;
                if (bitOfs == 8) {
                    bitOfs = 0;
                    byteIndex++;
                }
            }
            return value;
        }
    }

}
}