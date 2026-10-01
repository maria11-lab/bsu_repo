using System;
using System.IO;

namespace ImageInspector;

public class Row
{
    public string Name { get; set; } = "";
    public string Format { get; set; } = "";
    public string Size { get; set; } = "—";
    public string Dpi { get; set; } = "—";
    public string Depth { get; set; } = "—";
    public string Compression { get; set; } = "—";
    public string FullPath { get; set; } = "";
}

public static class Parser
{
    static uint Num(Stream s, int n, bool big)
    {
        uint v = 0;
        for (int i = 0; i < n; i++)
        {
            int b = s.ReadByte();
            if (b < 0) throw new EndOfStreamException();
            if (big) v = (v << 8) | (uint)b;
            else v |= (uint)b << (8 * i);
        }
        return v;
    }

    public static Row Read(string path)
    {
        var r = new Row { Name = Path.GetFileName(path), FullPath = path };
        try
        {
            using var s = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read, 4096, FileOptions.RandomAccess); var h = new byte[8];
            s.Read(h, 0, 8);
            s.Position = 0;

            if (h[0] == 0x89 && h[1] == 0x50) Png(s, r);
            else if (h[0] == 0xFF && h[1] == 0xD8) Jpeg(s, r);
            else if (h[0] == 'G' && h[1] == 'I') Gif(s, r);
            else if (h[0] == 'B' && h[1] == 'M') Bmp(s, r);
            else if ((h[0] == 'I' && h[1] == 'I') || (h[0] == 'M' && h[1] == 'M')) Tiff(s, r, h[0] == 'M');
            else if (h[0] == 0x0A) Pcx(s, r);
            else r.Format = "не изображение";
        }
        catch (Exception ex)
        {
            r.Compression = "ошибка: " + ex.Message;
        }
        return r;
    }

    static void Png(Stream s, Row r)
    {
        r.Format = "PNG";
        s.Position = 16;
        uint w = Num(s, 4, true), h = Num(s, 4, true);
        int bits = s.ReadByte(), colorType = s.ReadByte();
        int channels = colorType switch { 0 => 1, 2 => 3, 3 => 1, 4 => 2, _ => 4 };
        r.Size = $"{w} × {h}";
        r.Depth = $"{bits * channels} бит";
        r.Compression = "Deflate";

        s.Position = 33;
        while (true)
        {
            uint len = Num(s, 4, true), type = Num(s, 4, true);
            if (type == 0x70485973)
            {
                uint px = Num(s, 4, true);
                Num(s, 4, true);
                if (s.ReadByte() == 1) r.Dpi = (px * 0.0254).ToString("0.##");
                break;
            }
            if (type == 0x49444154 || type == 0x49454E44) break;
            s.Position += len + 4;
        }
    }

    static void Jpeg(Stream s, Row r)
    {
        r.Format = "JPEG";
        s.Position = 2;
        while (true)
        {
            if (s.ReadByte() != 0xFF) throw new Exception("нарушена структура");
            int m = s.ReadByte();
            while (m == 0xFF) m = s.ReadByte();
            if (m < 0) throw new EndOfStreamException();
            if (m == 0xD8 || m == 0x01 || (m >= 0xD0 && m <= 0xD7)) continue;

            int len = (int)Num(s, 2, true);
            long end = s.Position + len - 2;

            if (m == 0xE0 && len >= 16)
            {
                s.Position += 7;
                int units = s.ReadByte();
                uint x = Num(s, 2, true);
                if (units == 1) r.Dpi = x.ToString();
                else if (units == 2) r.Dpi = (x * 2.54).ToString("0.##");
            }
            else if (m >= 0xC0 && m <= 0xCF && m != 0xC4 && m != 0xC8 && m != 0xCC)
            {
                int prec = s.ReadByte();
                uint h = Num(s, 2, true), w = Num(s, 2, true);
                int comps = s.ReadByte();
                r.Size = $"{w} × {h}";
                r.Depth = $"{prec * comps} бит";
                r.Compression = m == 0xC0 ? "Baseline DCT (Huffman)" : m == 0xC2 ? "Progressive DCT (Huffman)" : $"JPEG SOF{m - 0xC0}";
                return;
            }
            s.Position = end;
        }
    }

    static void Gif(Stream s, Row r)
    {
        r.Format = "GIF";
        s.Position = 6;
        uint w = Num(s, 2, false), h = Num(s, 2, false);
        int packed = s.ReadByte();
        r.Size = $"{w} × {h}";
        r.Depth = $"{(packed & 7) + 1} бит";
        r.Compression = "LZW";
    }

    static void Bmp(Stream s, Row r)
    {
        r.Format = "BMP";
        s.Position = 18;
        int w = (int)Num(s, 4, false), h = (int)Num(s, 4, false);
        Num(s, 2, false);
        uint bpp = Num(s, 2, false), comp = Num(s, 4, false);
        Num(s, 4, false);
        int xppm = (int)Num(s, 4, false);
        r.Size = $"{w} × {Math.Abs(h)}";
        r.Depth = $"{bpp} бит";
        if (xppm > 0) r.Dpi = (xppm * 0.0254).ToString("0.##");
        r.Compression = comp switch
        {
            0 => "BI_RGB (без сжатия)",
            1 => "BI_RLE8",
            2 => "BI_RLE4",
            3 => "BI_BITFIELDS",
            _ => $"код {comp}"
        };
    }

    static void Tiff(Stream s, Row r, bool big)
    {
        r.Format = "TIFF";
        s.Position = 4;
        s.Position = Num(s, 4, big);
        int n = (int)Num(s, 2, big);
        uint w = 0, h = 0, bps = 1, spp = 1, comp = 1, unit = 2;
        double xr = 0;

        for (int i = 0; i < n; i++)
        {
            int tag = (int)Num(s, 2, big), type = (int)Num(s, 2, big);
            uint cnt = Num(s, 4, big);
            long vp = s.Position;
            uint v = Num(s, type == 3 ? 2 : 4, big);
            s.Position = vp + 4;
            switch (tag)
            {
                case 256: w = v; break;
                case 257: h = v; break;
                case 259: comp = v; break;
                case 277: spp = v; break;
                case 296: unit = v; break;
                case 258:
                    if (cnt <= 2) bps = v;
                    else { s.Position = v; bps = Num(s, 2, big); s.Position = vp + 4; }
                    break;
                case 282:
                    s.Position = v;
                    uint num = Num(s, 4, big), den = Num(s, 4, big);
                    xr = den == 0 ? 0 : (double)num / den;
                    s.Position = vp + 4;
                    break;
            }
        }

        r.Size = $"{w} × {h}";
        r.Depth = $"{bps * spp} бит";
        if (xr > 0) r.Dpi = (unit == 3 ? xr * 2.54 : xr).ToString("0.##");
        r.Compression = comp switch
        {
            1 => "без сжатия",
            2 => "CCITT RLE",
            3 => "CCITT Group 3",
            4 => "CCITT Group 4",
            5 => "LZW",
            6 or 7 => "JPEG",
            8 or 32946 => "Deflate",
            32773 => "PackBits",
            _ => $"код {comp}"
        };
    }

    static void Pcx(Stream s, Row r)
    {
        r.Format = "PCX";
        s.Position = 3;
        int bpp = s.ReadByte();
        int xmin = (int)Num(s, 2, false), ymin = (int)Num(s, 2, false), xmax = (int)Num(s, 2, false), ymax = (int)Num(s, 2, false);
        uint dpi = Num(s, 2, false);
        s.Position = 65;
        int planes = s.ReadByte();
        r.Size = $"{xmax - xmin + 1} × {ymax - ymin + 1}";
        r.Depth = $"{bpp * planes} бит";
        if (dpi > 0) r.Dpi = dpi.ToString();
        r.Compression = "RLE";
    }
}