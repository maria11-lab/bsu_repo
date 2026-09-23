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

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            textBox4.Text = (Int32.Parse(textBox1.Text) + Int32.Parse(textBox2.Text)).ToString();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            textBox4.Text = (Int32.Parse(textBox1.Text) - Int32.Parse(textBox2.Text)).ToString();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            textBox4.Text = (Int32.Parse(textBox1.Text) * Int32.Parse(textBox2.Text)).ToString();
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            textBox4.Text = (Int32.Parse(textBox1.Text) / Int32.Parse(textBox2.Text)).ToString();
        }
    }
}
