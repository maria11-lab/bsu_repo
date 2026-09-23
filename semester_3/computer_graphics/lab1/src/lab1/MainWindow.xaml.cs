using System.Windows;
using lab1.ViewModels;

using WinFormsColor = System.Drawing.Color;

namespace lab1
{
    public partial class MainWindow : Window
    {
        private readonly System.Windows.Forms.ColorDialog _colorDialog;

        public MainWindow()
        {
            InitializeComponent();

            _colorDialog = new System.Windows.Forms.ColorDialog
            {
                FullOpen = true
            };

            BtnOpenPalette.Click += BtnOpenPalette_Click;
            PreviewKeyDown += Window_PreviewKeyDown;
        }

        private void Window_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key != System.Windows.Input.Key.Enter) return;

            if (System.Windows.Input.Keyboard.FocusedElement is System.Windows.Controls.TextBox textBox)
            {
                textBox.GetBindingExpression(System.Windows.Controls.TextBox.TextProperty)?.UpdateSource();
                e.Handled = true;
            }
        }


        private void BtnOpenPalette_Click(object sender, RoutedEventArgs e)
        {
            if (_colorDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                WinFormsColor selected = _colorDialog.Color;

                if (DataContext is MainViewModel vm)
                {
                    vm.SetRgbFromPalette(selected.R, selected.G, selected.B);
                }
            }
        }
    }
}
