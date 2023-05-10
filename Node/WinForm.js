var path = require("path");
var fs = require("fs");

/** Custom Error: RuntimeError */
function RuntimeError(message) {
  this.name = "RuntimeError";
  this.message = message || "Error running the current script";
  this.stack = new Error().stack;
}

var _f = function () {};
_f.prototype = Error.prototype;
RuntimeError.prototype = new _f();
RuntimeError.prototype.constructor = RuntimeError;
/** */

var findRuntimeDll = function () {
  var dlls = ["WinForm.node", "winformDll.dll", "CallWinForm.dll"];
  dlls.forEach(function (dll) {
    if (!fs.existsSync(dll)) {
      throw new RuntimeError("dependice DLL: " + dll + " not found");
    }
  });
};

findRuntimeDll();

var nativeBinding = require("./WinForm.node");

/**
 * Native Functions
  CreateFormInstance: [Function (anonymous)],
  ReleaseFormInstance: [Function (anonymous)],
  CheckFormInstanceExists: [Function (anonymous)],
  AddTextBoxStrings: [Function (anonymous)],
  RemoveTextBoxStringById: [Function (anonymous)],
  AddToTextBox: [Function (anonymous)],
  ShowForm: [Function (anonymous)],
  HideForm: [Function (anonymous)],
  RenderForm: [Function (anonymous)],
  GetFormCount: [Function (anonymous)],
  SetButtonClickDelegate: [Function (anonymous)],
  HideConsole: [Function (anonymous)]
 */

var privateMap = new WeakMap();

/**
 * Creates a winform gui sample window
 * @class
 */
function WinForm() {
  /**
   * The privateVariable stores the private variable of gui sample window
   * @memberof WinForm
   */
  var privateVariable = {
    /**
     * Handle is a pointer to Winform instance
     * @memberof WinForm
     * @type {string}
     */
    handle: "0",

    /**
     * isRelease indicates whether th Winform instance is released
     * @memberof WinForm
     * @type {boolean}
     */
    isRelease: false,
  };

  privateVariable.handle = nativeBinding.CreateFormInstance();
  privateMap.set(this, privateVariable);
}

/**
 * This method releases the Winform instance,
 * you cannot call this method twice
 * @memberof WinForm
 */
WinForm.prototype.ReleaseFormInstance = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  nativeBinding.ReleaseFormInstance(privateVariable.handle);

  privateVariable.isRelease = true;
  privateVariable.handle = "0";
};

/**
 * This method add the text string to text box candidate store
 * @memberof WinForm
 * @param {string} text - text string to add
 * @returns {number} - the identifier of the string you add
 */
WinForm.prototype.AddTextBoxStrings = function (text) {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  return nativeBinding.AddTextBoxStrings(privateVariable.handle, text);
};

/**
 * This method removes the text string by identifier from text box candidate store,
 * you can get the identifier by calling AddTextBoxStrings
 * @memberof WinForm
 * @param {number} id - identifier to remove
 * @returns {number} - the identifier of the string you remove
 */
WinForm.prototype.RemoveTextBoxStringById = function (id) {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  return nativeBinding.RemoveTextBoxStringById(privateVariable.handle, id);
};

/**
 * This method adds text to textbox UI from text box candidate store,
 * it will emptys textbox UI when all the text are on textbox UI
 * @memberof WinForm
 */
WinForm.prototype.AddToTextBox = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  nativeBinding.AddToTextBox(privateVariable.handle);
};

/**
 * This method shows the winform,
 * you MUST call it before you render the form or the form WON'T show
 * @memberof WinForm
 */
WinForm.prototype.ShowForm = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  nativeBinding.ShowForm(privateVariable.handle);
};

/**
 * This method hides the winform
 * @memberof WinForm
 */
WinForm.prototype.HideForm = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  nativeBinding.HideForm(privateVariable.handle);
};

/**
 * This method renders the form,
 * call this method in a infinite loop to make the winform keep showing
 * @memberof WinForm
 */
WinForm.prototype.RenderForm = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  nativeBinding.RenderForm(privateVariable.handle);
};

/**
 * This method gets the current opened winforms,
 * if return value equals to 0, that means the winform is closed,
 * so you can release the instance
 * @memberof WinForm
 * @returns {boolean} - current opened winforms
 */
WinForm.prototype.GetFormCount = function () {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  return nativeBinding.GetFormCount(privateVariable.handle);
};

/**
 * Button Click handler function type
 * @typedef {Function} ButtonClickDelegate
 * @returns {undefined}
 */

/**
 * This method set the button clicking handler function
 * @memberof WinForm
 * @param {ButtonClickDelegate} callback - button clicking handler function
 */
WinForm.prototype.SetButtonClickDelegate = function (callback) {
  var privateVariable = privateMap.get(this);

  if (!nativeBinding.CheckFormInstanceExists(privateVariable.handle)) {
    throw new Error("Handle of current instance is not exists");
  }

  if (privateVariable.isRelease) {
    throw new Error("Handle of current instance has been released");
  }

  return nativeBinding.SetButtonClickDelegate(privateVariable.handle, callback);
};

/**
 * This method hides/shows the windows console
 * @memberof WinForm
 * @static
 * @param {boolean} isHide - set to true when you want to hide the console window, otherwise set to false
 */
WinForm.HideConsole = function (isHide) {
  return nativeBinding.HideConsole(isHide);
};

module.exports = WinForm;
