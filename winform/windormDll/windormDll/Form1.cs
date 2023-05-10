using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CallForm
{
    internal partial class Form1 : Form
    {
        private List<String> textBoxStrings;
        private int iterateIdx = 0;

        ButtonClickDelegate buttonClickDelegate = null;

        public string userData { get; set; }

        public Form1()
        {
            InitializeComponent();
            textBoxStrings = new List<String>();
            textBoxStrings.Add("Hello!");
            textBox1.ScrollBars = ScrollBars.Vertical;
        }

        public int AddTextBoxStrings(String inputString)
        {
            textBoxStrings.Add(inputString);
            return textBoxStrings.Count - 1;
        }

        public int RemoveTextBoxStringById(int id)
        {
            textBoxStrings[id] = null;
            return id;
        }

        public void AddToTextBox()
        {
            if (textBoxStrings.Count == 0)
            {
                return;
            }

            if (iterateIdx >= textBoxStrings.Count)
            {
                iterateIdx = 0;
                textBox1.Text = "";
                return;
            }

            var val = textBoxStrings[iterateIdx++];
            while (val == null && iterateIdx < textBoxStrings.Count)
            {
                val = textBoxStrings[iterateIdx++];
            }

            if (val != null)
            {
                textBox1.Text += (val + Environment.NewLine);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(buttonClickDelegate != null)
            {
                buttonClickDelegate(userData);
            }
        }

        public void SetButtonClickDelegate(ref ButtonClickDelegate callback)
        {
            buttonClickDelegate = callback;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textBox1.SelectionStart = textBox1.Text.Length;
            textBox1.ScrollToCaret();
        }
    }
}
