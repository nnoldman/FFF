using UnityEngine;
using System.Collections;
using SevenZip.Compression.LZMA;
using System.IO;
using System;

public class Zip7Helper {

    public static byte[] CompressLZMA(byte[] src) {
        MemoryStream input = new MemoryStream(src);
        MemoryStream output = new MemoryStream();
        Compress(input, output);
        return output.ToArray();
    }

    public static byte[] DecompressLZMA(byte[] src) {
        MemoryStream input = new MemoryStream(src);
        MemoryStream output = new MemoryStream();
        Decompress(input, output);
        return output.ToArray();
    }

    public static void CompressFileLZMA(string inFile, string outFile) {
        FileStream input = new FileStream(inFile, FileMode.Open);
        FileStream output = new FileStream(outFile, FileMode.Create);
        Compress(input, output);
        output.Flush();
        output.Close();
        input.Close();
    }

    static void Compress(Stream input, Stream output ) {
        SevenZip.Compression.LZMA.Encoder coder = new SevenZip.Compression.LZMA.Encoder();
        // Write the encoder properties
        coder.WriteCoderProperties(output);

        // Write the decompressed file size.
        output.Write(BitConverter.GetBytes(input.Length), 0, 8);

        // Encode the file.
        coder.Code(input, output, input.Length, -1, null);
    }

    static void Decompress(Stream input, Stream output) {
        SevenZip.Compression.LZMA.Decoder coder = new SevenZip.Compression.LZMA.Decoder();
        // Read the decoder properties
        byte[] properties = new byte[5];
        input.Read(properties, 0, 5);

        // Read in the decompress file size.
        byte[] fileLengthBytes = new byte[8];
        input.Read(fileLengthBytes, 0, 8);
        long fileLength = BitConverter.ToInt64(fileLengthBytes, 0);

        // Decompress the file.
        coder.SetDecoderProperties(properties);
        coder.Code(input, output, input.Length, fileLength, null);
    }

    public static void DecompressFileLZMA(byte[] inFile, string outFile) {
        MemoryStream input = new MemoryStream(inFile);
        FileStream output = new FileStream(outFile, FileMode.Create);
        Decompress(input, output);
        output.Flush();
        output.Close();
        input.Close();
    }


}