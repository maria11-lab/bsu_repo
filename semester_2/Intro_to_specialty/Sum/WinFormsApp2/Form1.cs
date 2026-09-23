namespace WinFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string a = textBox1.Text;
            string b = textBox2.Text;
            int ai = Convert.ToInt32(a);
            int bi = Convert.ToInt32(b);
            int sum = ai + bi;
            textBox3.Text = sum.ToString();

        }
    }
}
