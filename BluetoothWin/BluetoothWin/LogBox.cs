using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BluetoothWin
{
    public partial class LogBox : UserControl
    {
        public int MaxLinesToDisplay { get; set; } = 1000;
        public LogBox()
        {
            InitializeComponent();
        }

        public void AddColorText(string textToAdd, Color TextColor)
        {
            int index = RTF.SelectionStart;
            int length = textToAdd.Length;

            RTF.AppendText(textToAdd);
            RTF.SelectionStart = index;
            RTF.SelectionLength = length;
            RTF.SelectionColor = TextColor;
            RTF.SelectionStart = index + length;
            
            if (RTF.GetLineFromCharIndex(RTF.Text.Length - 1) > MaxLinesToDisplay)
            {
                RTF.Select(0, RTF.GetFirstCharIndexFromLine(1));
                RTF.SelectedText = "";
            }
            RTF.SelectionStart = RTF.Text.Length;
        }
        public void Clear()
        {
            RTF.Clear();
        }
        public void AppendText(string TextToAppend)
        {
            RTF.AppendText(TextToAppend);
        }
        public void SelectAll()
        {
            RTF.SelectAll();
        }
        public void SelectionColor(Color DesiredSelectionColor)
        {
            RTF.SelectionColor = DesiredSelectionColor;
        }
        
        public void AddError(string log)
        {
            //come here if you have a error and want it logged
            string log1 = $"{ DateTime.Now.ToString("hh:mm:ss")}: {log}\n";
            AddColorText(log1, Color.Red);
        }
        public void AddNotification(string log)
        {
            //come here if you have a error and want it logged
            string log1 = $"{ DateTime.Now.ToString("hh:mm:ss")}: {log}\n";
            AddColorText(log1, Color.Cyan);
        }
        public void AddWarning(string log)
        {
            //come here if you have a error and want it logged
            string log1 = $"{ DateTime.Now.ToString("hh:mm:ss")}: {log}\n";
            AddColorText(log1, Color.Yellow);
        }
        public void AddData(string data, bool hex = false)
        {
            if(!hex) AddColorText(data, Color.Cyan);
            else
            {
                AddHexData(Encoding.ASCII.GetBytes(data));
            }
        }
        public void AddHexData(byte[] dataToAdd, int numberofcharcterstoadd = 16)
        {//this will add the data from a byte array to the list box
            if (numberofcharcterstoadd > dataToAdd.Length) numberofcharcterstoadd = dataToAdd.Length;
            int count = 0;
            string tempString = "";
            string tempStringAscii = "";
            while (count < numberofcharcterstoadd)
            {
                tempString += String.Format("{0:x2} ", (int)dataToAdd[count]);
                //tempString += ' ';
                if ((dataToAdd[count] >= ' ') & (dataToAdd[count] <= 127))
                { tempStringAscii += (char)(dataToAdd[count]); }
                else
                {
                    tempStringAscii += ('.');
                }
                count++;
                if ((count & 7) == 0)//we just got to 8 characters so display them and go to next line
                {
                    tempString += ' ';
                    AddColorText(tempString, Color.Cyan);
                    if (tempStringAscii.Length > 8)
                    { tempStringAscii += tempStringAscii.Length.ToString(); }
                    AddColorText(tempStringAscii + "\n", Color.Cyan);

                    tempString = "";
                    tempStringAscii = "";
                }
            }
            int fill = (3 * (8 - (count & 7)));//lets see how many characters we need

            for (count = 0; count < fill - 1; count++)
            { tempString += '-'; }
            tempString += "  ";
            AddColorText(tempString, Color.Cyan); //addRedText(tempString);
            AddColorText(tempStringAscii + "\n", Color.Cyan);
        }
    }
}
