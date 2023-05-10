var WinForm = require("./WinForm");

var poems = [
  "How do I love thee? Let me count the ways.",
  "I love thee to the depth and breadth and height",
  "My soul can reach, when feeling out of sight",
  "For the ends of Being and ideal Grace.",
  "I love thee to the level of everyday's",
  "Most quiet need, by sun and candlelight.",
  "I love thee freely, as men strive for Right;",
  "I love thee purely, as they turn from Praise.",
  "I love thee with the passion put to use",
  "In my old griefs, and with my childhood's faith.",
  "I love thee with a love I seemed to lose",
  "With my lost saints,I love thee with the breath,",
  "Smiles, tears, of all my life! and, if God choose,",
  "I shall but love thee better after death.",
];

console.log("Create Form Instance");
var form = new WinForm();

poems.forEach(function (poem) {
  console.log("Add poem string to textbox candidate store: " + poem);
  form.AddTextBoxStrings(poem);
});

console.log("Set button click handler");
form.SetButtonClickDelegate(function () {
  console.log("Button Clicked");
  form.AddToTextBox();
});

console.log("Show form");
form.ShowForm();

console.log("hide console");
WinForm.HideConsole(true);

console.log("Render form");
var interval = setInterval(function () {
  if (form.GetFormCount() == 0) {
    console.log("Form closed");
    clearInterval(interval);
    console.log("Release form instance");
    form.ReleaseFormInstance();
    console.log("End");
    return;
  }

  form.RenderForm();
}, 10);
