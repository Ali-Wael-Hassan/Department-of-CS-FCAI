namespace lossless {
namespace dict {

    public interface IDictCodec {
        string Name { get; }
        LZTuple[] Compress(byte[] data, UInt16 maxSearch, UInt16 maxLookahead);
        byte[] Decompresss(LZTuple[] tuples);
        bool Save(String pathname, LZTuple[] tuples);
        byte[] Load(String pathname);
    }

}
}