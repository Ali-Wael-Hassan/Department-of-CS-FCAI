namespace lossless {
namespace dict {

    public struct LZTuple {

        private UInt16 distance;
        private UInt16 length;
        private byte   next;

        public UInt16 Distance { get { return distance; } set { distance = value; } }
        public UInt16 Length   { get { return length;   } set { length   = value; } }
        public byte   Next     { get { return next;     } set { next     = value; } }

        public LZTuple(UInt16 distance, UInt16 length, byte next) {
            this.distance = distance;
            this.length   = length;
            this.next     = next;
        }

        public bool IsLiteral { get { return distance == 0 && length == 0; } }

        public override string ToString() {
            return IsLiteral ? "(" + next + ")" : "(" + distance + "," + length + "," + next + ")";
        }
    }

}
}