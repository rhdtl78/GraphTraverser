#pragma once
#include <string>
using namespace std;
string* strSplit(string strOrigin, string strTok)
{
	int cutAt;  // 자르는 위치
	int index = 0;  // 문자열 인덱스
	string* strResult = new string[6]; // 결과 return 변수

									   // strTok을 찾을 때까지 반복
	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		if (cutAt > 0)  // 자르는 위치가 0보다 크면
		{
			// 결과 배열에 추가
			strResult[index++] = strOrigin.substr(0, cutAt);
		}
		// 원본은 자른 부분을 제외한 나머지
		strOrigin = strOrigin.substr(cutAt + 1);
	}

	if (strOrigin.length() > 0) // 원본이 아직 남았으면
	{
		// 나머지를 결과 배열에 추가
		strResult[index++] = strOrigin.substr(0, cutAt);
	}

	return strResult;
}
