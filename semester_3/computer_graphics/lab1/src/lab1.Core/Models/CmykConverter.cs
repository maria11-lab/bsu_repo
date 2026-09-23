using System;

namespace lab1.Core.Models
{
    public enum CmykAlgorithm
    {
        Naive, 
        UCR,
        GCR
    }

    public static class CmykConverter
    {
        private const double UcrShadowThreshold = 0.3;

        public static (double C, double M, double Y, double K) RgbToCmyk(
            byte r, byte g, byte b, CmykAlgorithm algorithm, double strength)
        {
            double rN = r / 255.0, gN = g / 255.0, bN = b / 255.0;

            double c0 = 1 - rN;
            double m0 = 1 - gN;
            double y0 = 1 - bN;

            double kFull = Math.Min(c0, Math.Min(m0, y0));

            if (kFull >= 1.0 - 1e-9)
                return (0, 0, 0, 100);

            double c, m, y, k;

            switch (algorithm)
            {
                case CmykAlgorithm.Naive:
                    k = kFull;
                    break;

                case CmykAlgorithm.GCR:
                    k = Clamp01(strength) * kFull;
                    break;

                case CmykAlgorithm.UCR:
                    double excess = Math.Max(0, kFull - UcrShadowThreshold);
                    k = Clamp01(strength) * excess;
                    break;

                default:
                    throw new ArgumentOutOfRangeException(nameof(algorithm));
            }

            double denom = 1.0 - k;
            c = denom > 1e-9 ? (c0 - k) / denom : 0;
            m = denom > 1e-9 ? (m0 - k) / denom : 0;
            y = denom > 1e-9 ? (y0 - k) / denom : 0;

            return (Clamp01(c) * 100.0, Clamp01(m) * 100.0, Clamp01(y) * 100.0, Clamp01(k) * 100.0);
        }

        public static (byte R, byte G, byte B) CmykToRgb(double c, double m, double y, double k)
        {
            double cN = c / 100.0, mN = m / 100.0, yN = y / 100.0, kN = k / 100.0;

            double r = 255.0 * (1 - cN) * (1 - kN);
            double g = 255.0 * (1 - mN) * (1 - kN);
            double bch = 255.0 * (1 - yN) * (1 - kN);

            return (
                (byte)Math.Round(ClampByte(r)),
                (byte)Math.Round(ClampByte(g)),
                (byte)Math.Round(ClampByte(bch)));
        }

        private static double Clamp01(double v) => v < 0 ? 0 : (v > 1 ? 1 : v);
        private static double ClampByte(double v) => v < 0 ? 0 : (v > 255 ? 255 : v);
    }
}
