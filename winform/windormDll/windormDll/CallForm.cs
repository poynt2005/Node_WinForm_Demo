using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CallForm {
    public delegate void ButtonClickDelegate(string userIdentify);

    public class CallForm {

        private Form1 form;

        public CallForm() {
            form = new Form1();
            form.FormBorderStyle = FormBorderStyle.FixedSingle;
            form.MaximizeBox = false;
        }

        public int AddTextBoxStrings(String inputString) {
            return form.AddTextBoxStrings(inputString);
        }

        public int RemoveTextBoxStringById(int id) {
            return form.RemoveTextBoxStringById(id);
        }

        public void AddToTextBox() {
            form.AddToTextBox();
        }

        public void SetButtonClickDelegate(ref ButtonClickDelegate callback) {
            form.SetButtonClickDelegate(ref callback);
        }

        public void ShowForm() {
            form.Show();
        }

        public void HideForm() {
            form.Hide();
        }

        public void RenderForm() {
            Application.DoEvents();
        }

        public int GetFormCount() {
            return Application.OpenForms.Count;
        }

        public void SetUserData(String id) {
            form.userData = id;
        }

        public String GetUserData() {
            return form.userData;
        }

    }

}