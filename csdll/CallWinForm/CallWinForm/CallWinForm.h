#pragma once

#ifdef BUILDEXPORTAPI
#define EXPORTAPI __declspec(dllexport)
#else
#define EXPORTAPI __declspec(dllimport)
#endif

typedef unsigned long long FormHandle;

#ifdef __cplusplus
extern "C" {
#endif
	EXPORTAPI FormHandle CreateFormInstance(const char*);
	EXPORTAPI void ReleaseFormInstance(const FormHandle);
	EXPORTAPI int CheckFormInstanceExists(const FormHandle);
	EXPORTAPI int AddTextBoxStrings(const FormHandle, const char*);
	EXPORTAPI int RemoveTextBoxStringById(const FormHandle, int);
	EXPORTAPI void AddToTextBox(const FormHandle);
	EXPORTAPI void ShowForm(const FormHandle);
	EXPORTAPI void HideForm(const FormHandle);
	EXPORTAPI void RenderForm(const FormHandle);
	EXPORTAPI int GetFormCount(const FormHandle);
	EXPORTAPI void SetUserData(const FormHandle, const char*);
	EXPORTAPI const char* GetUserData(const FormHandle);
	EXPORTAPI void SetButtonClickDelegate(const FormHandle, void(*)(const char*));
#ifdef __cplusplus
}
#endif