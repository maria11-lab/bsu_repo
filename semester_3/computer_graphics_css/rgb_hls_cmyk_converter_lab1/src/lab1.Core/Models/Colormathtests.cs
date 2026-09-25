using System.Text;
using lab1.Core.Models;

namespace lab1.Core.Test
{
    public static class ColorMathTests
    {
        public static string RunAllTests()
        {
            var report = new StringBuilder();
            int passed = 0, failed = 0;

            void Check(string name, double expected, double actual, double tolerance = 0.1)
            {
                bool ok = System.Math.Abs(expected - actual) <= tolerance;
                report.AppendLine(ok
                    ? $"OK   {name}"
                    : $"FAIL {name}: ожидали {expected}, получили {actual}");
                if (ok) passed++; else failed++;
            }

            var (h1, l1, s1) = HlsConverter.RgbToHls(255, 0, 0);
            Check("Красный: Hue", 0, h1);
            Check("Красный: Lightness", 50, l1);
            Check("Красный: Saturation", 100, s1);

            var (_, l2, s2) = HlsConverter.RgbToHls(255, 255, 255);
            Check("Белый: Lightness", 100, l2);
            Check("Белый: Saturation", 0, s2);

            var (_, _, s3) = HlsConverter.RgbToHls(128, 128, 128);
            Check("Серый: Saturation = 0", 0, s3);

            var (r4, g4, b4) = HlsConverter.HlsToRgb(0, 50, 100);
            Check("HLS красный -> R", 255, r4);
            Check("HLS красный -> G", 0, g4);
            Check("HLS красный -> B", 0, b4);

            var (c5, m5, y5, k5) = CmykConverter.RgbToCmyk(255, 0, 0, CmykAlgorithm.Naive, 1.0);
            Check("Красный CMYK: C", 0, c5);
            Check("Красный CMYK: M", 100, m5);
            Check("Красный CMYK: Y", 100, y5);
            Check("Красный CMYK: K", 0, k5);

            var (c6, m6, y6, k6) = CmykConverter.RgbToCmyk(0, 0, 0, CmykAlgorithm.Naive, 1.0);
            Check("Чёрный CMYK: K", 100, k6);
            Check("Чёрный CMYK: C=0", 0, c6);

            var (r7, g7, b7) = CmykConverter.CmykToRgb(0, 0, 0, 100);
            Check("CMYK чёрный -> R", 0, r7);
            Check("CMYK чёрный -> G", 0, g7);
            Check("CMYK чёрный -> B", 0, b7);

            var (_, _, _, k8) = CmykConverter.RgbToCmyk(100, 50, 20, CmykAlgorithm.GCR, 0.0);
            Check("GCR сила=0: K=0", 0, k8);

            var (_, _, _, k9) = CmykConverter.RgbToCmyk(240, 230, 220, CmykAlgorithm.UCR, 1.0);
            Check("UCR светлый: K=0", 0, k9);

            var (r10, g10, b10) = HlsConverter.HlsToRgb(0, 50, 100);
            var (c10, m10, y10, k10) = CmykConverter.RgbToCmyk(r10, g10, b10, CmykAlgorithm.Naive, 1.0);
            Check("HLS красный -> CMYK: M", 100, m10);
            Check("HLS красный -> CMYK: Y", 100, y10);
            Check("HLS красный -> CMYK: K", 0, k10);

            report.Insert(0, $"Пройдено: {passed}, провалено: {failed}\n\n");
            return report.ToString();
        }
    }
}
