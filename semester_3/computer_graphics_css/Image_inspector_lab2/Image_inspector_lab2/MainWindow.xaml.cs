using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media.Imaging;
using Microsoft.Win32;

namespace ImageInspector;
using WpfAnimatedGif;

public partial class MainWindow : Window
{
    static readonly string[] Exts = { ".jpg", ".jpeg", ".gif", ".tif", ".tiff", ".bmp", ".png", ".pcx" };

    CancellationTokenSource? _cts;
    ICollectionView? _view;

    public MainWindow() { InitializeComponent(); }


    void Choose_Click(object sender, RoutedEventArgs e)
    {
        var dlg = new OpenFolderDialog();
        if (dlg.ShowDialog() == true) _ = Scan(dlg.FolderName);
    }

    void Window_Drop(object sender, DragEventArgs e)
    {
        if (e.Data.GetData(DataFormats.FileDrop) is string[] p && p.Length > 0 && Directory.Exists(p[0]))
            _ = Scan(p[0]);
    }

    void Stop_Click(object sender, RoutedEventArgs e) => _cts?.Cancel();

    async Task Scan(string folder)
    {
        if (_cts != null) return;
        _cts = new CancellationTokenSource();
        var ct = _cts.Token;

        BtnFolder.IsEnabled = false;
        BtnStop.IsEnabled = true;
        Table.ItemsSource = null;
        ShowPreview(null);
        Status.Text = "Поиск файлов…";
        Bar.IsIndeterminate = true;
        var sw = Stopwatch.StartNew();
        bool sub = ChkSub.IsChecked == true;

        try
        {
            var opt = new EnumerationOptions { RecurseSubdirectories = sub, IgnoreInaccessible = true };
            var files = await Task.Run(() => Directory.GetFiles(folder, "*", opt)
                .Where(f => Exts.Contains(Path.GetExtension(f).ToLower())).ToArray());

            Bar.IsIndeterminate = false;
            Bar.Maximum = Math.Max(1, files.Length);
            Bar.Value = 0;
            var rows = new Row?[files.Length];
            int done = 0;

            var work = Task.Run(() => Parallel.For(0, files.Length, new ParallelOptions { CancellationToken = ct, MaxDegreeOfParallelism = 8 }, i =>
            {
                rows[i] = Parser.Read(files[i]);
                Interlocked.Increment(ref done);
            }));

            while (!work.IsCompleted)
            {
                await Task.Delay(100);
                Bar.Value = done;
                Status.Text = $"Обработано {done} из {files.Length}";
            }
            try { await work; } catch (OperationCanceledException) { }

            var result = rows.Where(r => r != null).Cast<Row>().ToArray();
            _view = CollectionViewSource.GetDefaultView(result);
            _view.Filter = Match;
            Table.ItemsSource = _view;

            Bar.Value = done;
            Status.Text = (ct.IsCancellationRequested ? "Остановлено: " : "Готово: ") +
                          $"{result.Length} файлов за {sw.Elapsed.TotalSeconds:0.0} с";
        }
        catch (Exception ex)
        {
            Status.Text = "Ошибка: " + ex.Message;
        }
        finally
        {
            _cts = null;
            BtnFolder.IsEnabled = true;
            BtnStop.IsEnabled = false;
            Bar.IsIndeterminate = false;
        }
    }


    bool Match(object o) =>
        o is Row r && (string.IsNullOrWhiteSpace(FilterBox.Text) ||
                       r.Name.Contains(FilterBox.Text.Trim(), StringComparison.OrdinalIgnoreCase));

    void Filter_Changed(object sender, TextChangedEventArgs e) => _view?.Refresh();


    void Table_SelectionChanged(object sender, SelectionChangedEventArgs e) =>
        ShowPreview(Table.SelectedItem as Row);

    void ShowPreview(Row? row)
    {
        ImageBehavior.SetAnimatedSource(Preview, null);
        Preview.Source = null;
        PreviewNote.Visibility = Visibility.Visible;
        if (row == null) { PreviewNote.Text = "Выберите файл в таблице"; return; }

        try
        {
            var bi = new BitmapImage();
            if (row.Format == "GIF")
            {
                bi.BeginInit();
                bi.UriSource = new Uri(row.FullPath);
                bi.EndInit();
                ImageBehavior.SetAnimatedSource(Preview, bi);
            }
            else
            {
                using var fs = File.OpenRead(row.FullPath);
                bi.BeginInit();
                bi.CacheOption = BitmapCacheOption.OnLoad;
                bi.DecodePixelWidth = 400;
                bi.StreamSource = fs;
                bi.EndInit();
                bi.Freeze();
                Preview.Source = bi;
            }
            PreviewNote.Visibility = Visibility.Collapsed;
        }
        catch
        {
            PreviewNote.Text = "Предпросмотр недоступен для этого файла (например, PCX WPF не показывает)";
        }
    }
}