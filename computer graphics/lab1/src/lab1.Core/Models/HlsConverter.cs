using System;

namespace lab1.Core.Models
{
    public static class HlsConverter
    {
        public static (double H, double L, double S) RgbToHls(byte r, byte g, byte b)
        {
            double rN = r / 255.0;
            double gN = g / 255.0;
            double bN = b / 255.0;

            double max = Math.Max(rN, Math.Max(gN, bN));
            double min = Math.Min(rN, Math.Min(gN, bN));
            double delta = max - min;

            double l = (max + min) / 2.0;

            double h = 0.0;
            double s = 0.0;

            if (delta > 1e-9)
            {
                s = l <= 0.5 ? delta / (max + min) : delta / (2.0 - max - min);

                if (max == rN)
                    h = (gN - bN) / delta + (gN < bN ? 6.0 : 0.0);
                else if (max == gN)
                    h = (bN - rN) / delta + 2.0;
                else
                    h = (rN - gN) / delta + 4.0;

                h *= 60.0;
            }

            return (h, l * 100.0, s * 100.0);
        }

        public static (byte R, byte G, byte B) HlsToRgb(double h, double l, double s)
        {
            double hN = ((h % 360.0) + 360.0) % 360.0 / 360.0;
            double lN = Clamp01(l / 100.0);
            double sN = Clamp01(s / 100.0);

            double r, g, b;

            if (sN <= 1e-9)
            {
                r = g = b = lN;
            }
            else
            {
                double q = lN < 0.5 ? lN * (1 + sN) : lN + sN - lN * sN;
                double p = 2 * lN - q;

                r = HueToChannel(p, q, hN + 1.0 / 3.0);
                g = HueToChannel(p, q, hN);
                b = HueToChannel(p, q, hN - 1.0 / 3.0);
            }

            return (
                (byte)Math.Round(Clamp01(r) * 255.0),
                (byte)Math.Round(Clamp01(g) * 255.0),
                (byte)Math.Round(Clamp01(b) * 255.0));
        }

        private static double HueToChannel(double p, double q, double t)
        {
            if (t < 0) t += 1;
            if (t > 1) t -= 1;

            if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
            if (t < 1.0 / 2.0) return q;
            if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
            return p;
        }

        private static double Clamp01(double v) => v < 0 ? 0 : (v > 1 ? 1 : v);
    }
}
