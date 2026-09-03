namespace WinFormsApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hello Word!");
            Console.Beep(5000, 300);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
