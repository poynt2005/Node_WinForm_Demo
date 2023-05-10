var path = require("path");

var CallWinFormLIB = path
  .resolve("../csdll/CallWinForm/x64/Release/CallWinForm.lib")
  .replace(/\\/gm, "\\\\");

var CallWinFormIncl = path
  .resolve("../csdll/CallWinForm/CallWinForm")
  .replace(/\\/gm, "\\\\");

module.exports = {
  CallWinFormLIB: CallWinFormLIB,
  CallWinFormIncl: CallWinFormIncl,
};
