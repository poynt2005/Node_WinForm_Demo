#include "CallWinForm.h"

#include <Windows.h>
#include <string>
#include <string.h>
#include <vector>
#include <filesystem>

ref class GlobalVariable {
public:
	static System::Reflection::Assembly^ dllAsm = nullptr;
	static System::Type^ callFormType = nullptr;
	static System::Collections::Generic::Dictionary<System::IntPtr, System::Object^>^ instanceMapping = nullptr;
};

void MarshalString(System::String^% inputStr, std::string& outStr) {
	auto csPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalUni(inputStr);
	char* chars = reinterpret_cast<char*>(static_cast<void*>(csPtr));
	outStr = std::string(chars);
	System::Runtime::InteropServices::Marshal::FreeHGlobal(csPtr);
}

FormHandle CreateFormInstance(const char* dllPath) {
	if (GlobalVariable::dllAsm == nullptr) {
		std::string dllRealpath;
		if (dllPath == nullptr) {
			GlobalVariable::dllAsm = System::Reflection::Assembly::LoadFile(gcnew System::String(std::filesystem::absolute("winformDll.dll").string().data()));
		}
		else {
			GlobalVariable::dllAsm = System::Reflection::Assembly::LoadFile(gcnew System::String(std::filesystem::absolute(dllPath).string().data()));
		}
		GlobalVariable::callFormType = GlobalVariable::dllAsm->GetType("CallForm.CallForm");
		GlobalVariable::instanceMapping = gcnew System::Collections::Generic::Dictionary<System::IntPtr, System::Object^>();
	}

	
	auto callFormInstance = System::Activator::CreateInstance(GlobalVariable::callFormType);
	auto instancePtr = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(callFormInstance);
	
	GlobalVariable::instanceMapping->Add(instancePtr, callFormInstance);

	auto cHandle = static_cast<FormHandle>(static_cast<intptr_t>(instancePtr));
	return cHandle;
}

void ReleaseFormInstance(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	GlobalVariable::instanceMapping->Remove(instancePtr);
}

int CheckFormInstanceExists(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	return static_cast<int>(GlobalVariable::instanceMapping->ContainsKey(instancePtr));
}

int AddTextBoxStrings(const FormHandle cHandle, const char* inputString) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("AddTextBoxStrings");
	
	array<System::Object^>^ param = { gcnew System::String(inputString) };
	auto result = instanceMethodInfo->Invoke(callFormInstance, param);

	return static_cast<int>(safe_cast<System::Int32>(result));
}

int RemoveTextBoxStringById(const FormHandle cHandle, int id) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("RemoveTextBoxStringById");

	array<System::Object^>^ param = { id };
	auto result = instanceMethodInfo->Invoke(callFormInstance, param);

	return static_cast<int>(safe_cast<System::Int32>(result));
}

void AddToTextBox(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("AddToTextBox");

	array<System::Object^>^ param = {  };
	instanceMethodInfo->Invoke(callFormInstance, param);
}

void ShowForm(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("ShowForm");

	array<System::Object^>^ param = {  };
	instanceMethodInfo->Invoke(callFormInstance, param);
}

void HideForm(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("HideForm");

	array<System::Object^>^ param = {  };
	instanceMethodInfo->Invoke(callFormInstance, param);
}


void RenderForm(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("RenderForm");

	array<System::Object^>^ param = {  };
	instanceMethodInfo->Invoke(callFormInstance, param);
}

int GetFormCount(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("GetFormCount");

	array<System::Object^>^ param = {  };
	auto result = instanceMethodInfo->Invoke(callFormInstance, param);

	return static_cast<int>(safe_cast<System::Int32>(result));
}

void SetUserData(const FormHandle cHandle, const char* userData) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("SetUserData");

	array<System::Object^>^ param = { gcnew System::String(userData) };
	instanceMethodInfo->Invoke(callFormInstance, param);
}

const char* GetUserData(const FormHandle cHandle) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("GetUserData");

	array<System::Object^>^ param = {  };
	auto result = instanceMethodInfo->Invoke(callFormInstance, param);

	auto csOutString = safe_cast<System::String^>(result);
	std::string outString;
	MarshalString(csOutString, outString);
	return outString.c_str();
}

void SetButtonClickDelegate(const FormHandle cHandle, void(*callbackPtr)(const char*)) {
	auto instancePtr = static_cast<System::IntPtr>(static_cast<intptr_t>(cHandle));
	auto callFormInstance = GlobalVariable::instanceMapping[instancePtr];

	auto buttonDelegateType = GlobalVariable::dllAsm->GetType("CallForm.ButtonClickDelegate");
	auto csCallbackPtr = static_cast<System::IntPtr>(callbackPtr);

	auto delegateInstance = System::Runtime::InteropServices::Marshal::GetDelegateForFunctionPointer(csCallbackPtr, buttonDelegateType);
	auto instanceMethodInfo = GlobalVariable::callFormType->GetMethod("SetButtonClickDelegate");

	array<System::Object^>^ param = { delegateInstance };
	instanceMethodInfo->Invoke(callFormInstance, param);
}
