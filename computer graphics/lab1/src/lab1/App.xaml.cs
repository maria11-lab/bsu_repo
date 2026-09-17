using System.Windows;

namespace lab1
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            MessageBox.Show(lab1.Core.Test.ColorMathTests.RunAllTests(), "Результаты тестов");
        }
    }
}
