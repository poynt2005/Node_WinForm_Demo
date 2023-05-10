#include "CallWinform.h"

#include <Windows.h>
#include <Napi.h>
#include <string.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>

#define SET_BTN_FN_ID 0

using JSContextStore = struct jsContenxtStore
{
    unsigned int FuncId;
    Napi::ThreadSafeFunction tsfn;
};

std::unordered_map<FormHandle, std::vector<std::unique_ptr<JSContextStore>>> jsContenxtMapping;

Napi::Value Node_CreateFormInstance(const Napi::CallbackInfo &info)
{
    auto env = info.Env();
    const auto handle = CreateFormInstance(nullptr);

    if (handle == 0)
    {
        Napi::Error::New(env, "Cannot create the form instance").ThrowAsJavaScriptException();
        return env.Null();
    }
    auto handleString = std::to_string(handle);
    SetUserData(handle, handleString.data());

    std::vector<std::unique_ptr<JSContextStore>> contextStore;
    jsContenxtMapping.insert(std::pair<FormHandle, std::vector<std::unique_ptr<JSContextStore>>>(handle, std::move(contextStore)));

    return Napi::String::New(env, handleString);
}

Napi::Value Node_ReleaseFormInstance(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));

    auto &contextStore = jsContenxtMapping[handle];

    for (auto &&store : contextStore)
    {
        (store->tsfn).Abort();
        (store->tsfn).Release();
    }

    jsContenxtMapping.erase(handle);

    ReleaseFormInstance(handle);

    return env.Null();
}

Napi::Value Node_CheckFormInstanceExists(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));

    return Napi::Boolean::New(env, CheckFormInstanceExists(handle));
}

Napi::Value Node_AddTextBoxStrings(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong Arguments, wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString() && !info[1].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 and 1 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    const auto text = info[1].As<Napi::String>().Utf8Value();

        return Napi::Number::New(env, AddTextBoxStrings(handle, text.data()));
}

Napi::Value Node_RemoveTextBoxStringById(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong Arguments, wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a number").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    const auto id = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, RemoveTextBoxStringById(handle, id));
}

Napi::Value Node_AddToTextBox(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    AddToTextBox(handle);

    return env.Null();
}

Napi::Value Node_ShowForm(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    ShowForm(handle);

    return env.Null();
}

Napi::Value Node_HideForm(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    HideForm(handle);

    return env.Null();
}

Napi::Value Node_RenderForm(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    RenderForm(handle);

    return env.Null();
}

Napi::Value Node_GetFormCount(const Napi::CallbackInfo &info)
{
    auto env = info.Env();
    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    return Napi::Number::New(env, GetFormCount(handle));
}

Napi::Value Node_SetButtonClickDelegate(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong Arguments, wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a string").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[1].IsFunction())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a function").ThrowAsJavaScriptException();
        return env.Null();
    }

    const auto handle = static_cast<FormHandle>(std::stoull(info[0].As<Napi::String>().Utf8Value()));
    auto jsFn = info[1].As<Napi::Function>();

    auto &contextStore = jsContenxtMapping[handle];

    const auto findContext = std::find_if(contextStore.begin(), contextStore.end(), [](const auto &el) -> bool
                                          { return (el->FuncId) == SET_BTN_FN_ID; });

    if (findContext != contextStore.end())
    {
        (*findContext)->tsfn.Abort();
        (*findContext)->tsfn.Release();

        contextStore.erase(findContext);
    }

    auto tsfn = Napi::ThreadSafeFunction::New(
        env,
        std::move(jsFn),
        "ButtonClickDelegate",
        0,
        1);

    contextStore.emplace_back(std::make_unique<JSContextStore>(JSContextStore{
        SET_BTN_FN_ID,
        std::move(tsfn)}));

    auto ccCallback = [](const char *userData) -> void
    {
        auto tsfnCallbackWrapper = [](Napi::Env env, Napi::Function jsCallback) -> void
        {
            jsCallback.Call(env.Global(), {});
        };

        const auto handle = static_cast<FormHandle>(std::stoull(userData));
        const auto &contextStore = jsContenxtMapping[handle];

        for (const auto &store : contextStore)
        {
            if ((store->FuncId) == SET_BTN_FN_ID)
            {
                (store->tsfn).NonBlockingCall(tsfnCallbackWrapper);
            }
        }
    };

    SetButtonClickDelegate(handle, ccCallback);

    return env.Null();
}

Napi::Value Node_HideConsole(const Napi::CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong Argument, wrong number of argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsBoolean())
    {
        Napi::TypeError::New(env, "Wrong Argument, position 0 excepted a boolean").ThrowAsJavaScriptException();
        return env.Null();
    }

    const bool isHide = info[0].As<Napi::Boolean>().Value();

    if (isHide)
    {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }
    else
    {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    }

    return env.Null();
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "CreateFormInstance"), Napi::Function::New(env, Node_CreateFormInstance));
    exports.Set(Napi::String::New(env, "ReleaseFormInstance"), Napi::Function::New(env, Node_ReleaseFormInstance));
    exports.Set(Napi::String::New(env, "CheckFormInstanceExists"), Napi::Function::New(env, Node_CheckFormInstanceExists));
    exports.Set(Napi::String::New(env, "AddTextBoxStrings"), Napi::Function::New(env, Node_AddTextBoxStrings));
    exports.Set(Napi::String::New(env, "RemoveTextBoxStringById"), Napi::Function::New(env, Node_RemoveTextBoxStringById));
    exports.Set(Napi::String::New(env, "AddToTextBox"), Napi::Function::New(env, Node_AddToTextBox));
    exports.Set(Napi::String::New(env, "ShowForm"), Napi::Function::New(env, Node_ShowForm));
    exports.Set(Napi::String::New(env, "HideForm"), Napi::Function::New(env, Node_HideForm));
    exports.Set(Napi::String::New(env, "RenderForm"), Napi::Function::New(env, Node_RenderForm));
    exports.Set(Napi::String::New(env, "GetFormCount"), Napi::Function::New(env, Node_GetFormCount));
    exports.Set(Napi::String::New(env, "SetButtonClickDelegate"), Napi::Function::New(env, Node_SetButtonClickDelegate));
    exports.Set(Napi::String::New(env, "HideConsole"), Napi::Function::New(env, Node_HideConsole));

    return exports;
}

NODE_API_MODULE(WinForm, Initialize)