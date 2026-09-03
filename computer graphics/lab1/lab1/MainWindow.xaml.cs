using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;

// Псевдоним, чтобы не было путаницы между классами Color в WPF и WinForms
using WinFormsColor = System.Drawing.Color;

namespace lab1
{
    public partial class MainWindow : Window
    {
        // Создаем палитру один раз на уровне класса, чтобы она помнила выбранные/пользовательские цвета
        private readonly System.Windows.Forms.ColorDialog _colorDialog;

        public MainWindow()
        {
            InitializeComponent();

            // Инициализируем диалог палитры
            _colorDialog = new System.Windows.Forms.ColorDialog
            {
                FullOpen = true // Разрешаем сразу открывать расширенную палитру с настроенными цветами
            };

            // Подписываемся на событие нажатия кнопки выбора палитры
            BtnOpenPalette.Click += BtnOpenPalette_Click;
        }

        private void BtnOpenPalette_Click(object sender, RoutedEventArgs e)
        {
            // Открываем тот же самый экземпляр диалога
            if (_colorDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                WinFormsColor selectedColor = _colorDialog.Color;

                // Переносим полученные RGB-значения в ползунки
                SliderR.Value = selectedColor.R;
                SliderG.Value = selectedColor.G;
                SliderB.Value = selectedColor.B;

                // Обновляем визуализацию цвета внизу окна
                ColorPreviewBorder.Background = new SolidColorBrush(
                    Color.FromRgb(selectedColor.R, selectedColor.G, selectedColor.B));
            }
        }
    }
}
