using System;
using System.Windows;
using Microsoft.Win32;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OpenButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Video files|*.mp4;*.avi;*.wmv;*.mov;*.mkv;*.mpeg|All files|*.*";

            if (openFileDialog.ShowDialog() == true)
            {
                VideoPlayer.Source = new Uri(openFileDialog.FileName);
                VideoPlayer.Play();
            }
        }

        private void PlayButton_Click(object sender, RoutedEventArgs e)
        {
            VideoPlayer.Play();
        }

        private void PauseButton_Click(object sender, RoutedEventArgs e)
        {
            VideoPlayer.Pause();
        }

        
    }
}