#pragma once
#include <string>
using namespace std;
string* strSplit(string strOrigin, string strTok)
{
	int cutAt;  // �ڸ��� ��ġ
	int index = 0;  // ���ڿ� �ε���
	string* strResult = new string[6]; // ��� return ����

									   // strTok�� ã�� ������ �ݺ�
	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		if (cutAt > 0)  // �ڸ��� ��ġ�� 0���� ũ��
		{
			// ��� �迭�� �߰�
			strResult[index++] = strOrigin.substr(0, cutAt);
		}
		// ������ �ڸ� �κ��� ������ ������
		strOrigin = strOrigin.substr(cutAt + 1);
	}

	if (strOrigin.length() > 0) // ������ ���� ��������
	{
		// �������� ��� �迭�� �߰�
		strResult[index++] = strOrigin.substr(0, cutAt);
	}

	return strResult;
}
