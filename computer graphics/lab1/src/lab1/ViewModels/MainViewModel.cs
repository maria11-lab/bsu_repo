using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Media;
using lab1.Core.Models;

namespace lab1.ViewModels
{
    
    public class MainViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private enum ColorSource { Rgb, Hls, Cmyk }

        private event Action<byte, byte, byte> RgbChanged;

        private bool _isSyncing;
        private ColorSource _editSource = ColorSource.Rgb;

        private double _r = 41, _g = 128, _b = 185;

        private double _h, _l, _s;

        private double _cmykC, _cmykM, _cmykY, _cmykK;

        private CmykAlgorithm _selectedCmykAlgorithm = CmykAlgorithm.Naive;
        private double _cmykStrength = 100;

        private Brush _previewBrush = new SolidColorBrush(Color.FromRgb(41, 128, 185));

        public MainViewModel()
        {
            RgbChanged += UpdateHlsListener;
            RgbChanged += UpdateCmykListener;
            RgbChanged += UpdatePreviewListener;

            _editSource = ColorSource.Rgb;
            RgbChanged?.Invoke((byte)Math.Round(_r), (byte)Math.Round(_g), (byte)Math.Round(_b));
        }


        public double R
        {
            get => _r;
            set => EditFromRgb(ClampByte(value), (byte)Math.Round(_g), (byte)Math.Round(_b));
        }

        public double G
        {
            get => _g;
            set => EditFromRgb((byte)Math.Round(_r), ClampByte(value), (byte)Math.Round(_b));
        }

        public double B
        {
            get => _b;
            set => EditFromRgb((byte)Math.Round(_r), (byte)Math.Round(_g), ClampByte(value));
        }

        private void EditFromRgb(byte r, byte g, byte b)
        {
            if (_isSyncing) return;
            _isSyncing = true;
            try
            {
                _editSource = ColorSource.Rgb;

                _r = r; _g = g; _b = b;
                OnPropertyChanged(nameof(R));
                OnPropertyChanged(nameof(G));
                OnPropertyChanged(nameof(B));

                RgbChanged?.Invoke(r, g, b);
            }
            finally { _isSyncing = false; }
        }

        public double H
        {
            get => _h;
            set => EditFromHls(NormalizeHue(value), _l, _s);
        }

        public double L
        {
            get => _l;
            set => EditFromHls(_h, ClampPercent(value), _s);
        }

        public double S
        {
            get => _s;
            set => EditFromHls(_h, _l, ClampPercent(value));
        }

        private void EditFromHls(double h, double l, double s)
        {
            if (_isSyncing) return;
            _isSyncing = true;
            try
            {
                _editSource = ColorSource.Hls;

                _h = h; _l = l; _s = s;
                OnPropertyChanged(nameof(H));
                OnPropertyChanged(nameof(L));
                OnPropertyChanged(nameof(S));

                var (r, g, b) = HlsConverter.HlsToRgb(h, l, s);
                _r = r; _g = g; _b = b;
                OnPropertyChanged(nameof(R));
                OnPropertyChanged(nameof(G));
                OnPropertyChanged(nameof(B));

                RgbChanged?.Invoke(r, g, b);
            }
            finally { _isSyncing = false; }
        }


        public double CmykC
        {
            get => _cmykC;
            set => EditFromCmyk(ClampPercent(value), _cmykM, _cmykY, _cmykK);
        }

        public double CmykM
        {
            get => _cmykM;
            set => EditFromCmyk(_cmykC, ClampPercent(value), _cmykY, _cmykK);
        }

        public double CmykYChannel
        {
            get => _cmykY;
            set => EditFromCmyk(_cmykC, _cmykM, ClampPercent(value), _cmykK);
        }

        public double CmykK
        {
            get => _cmykK;
            set => EditFromCmyk(_cmykC, _cmykM, _cmykY, ClampPercent(value));
        }

        private void EditFromCmyk(double c, double m, double y, double k)
        {
            if (_isSyncing) return;
            _isSyncing = true;
            try
            {
                _editSource = ColorSource.Cmyk;

                _cmykC = c; _cmykM = m; _cmykY = y; _cmykK = k;
                OnPropertyChanged(nameof(CmykC));
                OnPropertyChanged(nameof(CmykM));
                OnPropertyChanged(nameof(CmykYChannel));
                OnPropertyChanged(nameof(CmykK));

                var (r, g, b) = CmykConverter.CmykToRgb(c, m, y, k);
                _r = r; _g = g; _b = b;
                OnPropertyChanged(nameof(R));
                OnPropertyChanged(nameof(G));
                OnPropertyChanged(nameof(B));

                RgbChanged?.Invoke(r, g, b);
            }
            finally { _isSyncing = false; }
        }

        public CmykAlgorithm SelectedCmykAlgorithm
        {
            get => _selectedCmykAlgorithm;
            set
            {
                if (SetField(ref _selectedCmykAlgorithm, value))
                {
                    OnPropertyChanged(nameof(IsCmykStrengthApplicable));
                    RecalcCmykFromCurrentRgb();
                }
            }
        }
        public double CmykStrength
        {
            get => _cmykStrength;
            set
            {
                if (SetField(ref _cmykStrength, ClampPercent(value)))
                    RecalcCmykFromCurrentRgb();
            }
        }

        public bool IsCmykStrengthApplicable => _selectedCmykAlgorithm != CmykAlgorithm.Naive;

        public Brush PreviewBrush
        {
            get => _previewBrush;
            private set => SetField(ref _previewBrush, value);
        }

        public void SetRgbFromPalette(byte r, byte g, byte b) => EditFromRgb(r, g, b);

        private void UpdateHlsListener(byte r, byte g, byte b)
        {
            if (_editSource == ColorSource.Hls) return;

            var (h, l, s) = HlsConverter.RgbToHls(r, g, b);
            _h = h; _l = l; _s = s;
            OnPropertyChanged(nameof(H));
            OnPropertyChanged(nameof(L));
            OnPropertyChanged(nameof(S));
        }

        private void UpdateCmykListener(byte r, byte g, byte b)
        {
            if (_editSource == ColorSource.Cmyk) return;

            var (c, m, y, k) = CmykConverter.RgbToCmyk(r, g, b, _selectedCmykAlgorithm, _cmykStrength / 100.0);
            _cmykC = c; _cmykM = m; _cmykY = y; _cmykK = k;
            OnPropertyChanged(nameof(CmykC));
            OnPropertyChanged(nameof(CmykM));
            OnPropertyChanged(nameof(CmykYChannel));
            OnPropertyChanged(nameof(CmykK));
        }

        private void UpdatePreviewListener(byte r, byte g, byte b) => UpdatePreview();

        private void RecalcCmykFromCurrentRgb()
        {
            byte r = (byte)Math.Round(_r), g = (byte)Math.Round(_g), b = (byte)Math.Round(_b);
            var (c, m, y, k) = CmykConverter.RgbToCmyk(r, g, b, _selectedCmykAlgorithm, _cmykStrength / 100.0);
            _cmykC = c; _cmykM = m; _cmykY = y; _cmykK = k;
            OnPropertyChanged(nameof(CmykC));
            OnPropertyChanged(nameof(CmykM));
            OnPropertyChanged(nameof(CmykYChannel));
            OnPropertyChanged(nameof(CmykK));
        }

        private void UpdatePreview()
        {
            byte br = (byte)Math.Round(_r), bg = (byte)Math.Round(_g), bb = (byte)Math.Round(_b);
            PreviewBrush = new SolidColorBrush(Color.FromRgb(br, bg, bb));
        }

        private static double NormalizeHue(double h)
        {
            double result = h % 360.0;
            return result < 0 ? result + 360.0 : result;
        }

        private static byte ClampByte(double v) => (byte)Math.Round(v < 0 ? 0 : (v > 255 ? 255 : v));
        private static double ClampPercent(double v) => v < 0 ? 0 : (v > 100 ? 100 : v);

        private bool SetField<T>(ref T field, T value, [CallerMemberName] string propertyName = null)
        {
            if (Equals(field, value)) return false;
            field = value;
            OnPropertyChanged(propertyName);
            return true;
        }

        private void OnPropertyChanged([CallerMemberName] string propertyName = null) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}