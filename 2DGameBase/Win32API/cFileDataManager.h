#pragma once
#include "cSingletonBase.h"

#define g_pFileDataManager cFileDataManager::GetInstance()

class cFileDataManager : public cSingletonBase<cFileDataManager>
{
public:
	// ���̺�
	void txtSave(char* saveFileName, vector<string> vecData);
	// �ε�
	vector<string> txtLoad(char* loadFileName);

private:
	char* vectorArrayCombine(vector<string> vArray);
	vector<string> charArraySeparation(char charArray[]);
};

