#ifndef __MTTIMER_H__
#define __MTTIMER_H__


//////////////////////////////////////////////////////////////////////////
// multi thread timer
typedef void (CALLBACK* pfnTimerProc)(LPVOID pData, DWORD dwId);

/*
 *	dwPeriod	- ��ʱ�����ڣ���λ����
	dwCount		- ���������������0���ʾһֱ������������������ﵽ����ʱ�������Զ����٣�������� KillMtTimer
	proc		- �ص�
	pData		- �û����ݣ��ص������ĵ�һ������
	����ֵ��	- ��ʱ������ ID���ص������ĵڶ���������KillMtTimer�Ĳ�����
				  ������Ӷ�ʱ������ɹ�������ֵΪ����ID��0ҲΪ��ЧID�������ʧ�ܣ�����ֵ -1 (0xFFFFFFFF)
 */
DWORD SetMtTimer(DWORD dwCookie, DWORD dwPeriod, DWORD dwCount, pfnTimerProc proc, LPVOID pData);
void KillMtTimer(DWORD dwTimerId);

/*
 *	����Ҫʱ�ӵ��߳̽���ǰ����Ҫ���ô˷�������ʱ������
 */
void OnEndOfThread();

//class MtTimer
//{
//public:
//	static DWORD NewTimer(DWORD dwPeriod/*ms*/, pfnTimerProc proc, LPVOID pData, DWORD dwCount=0); // ����ID�����ID��0xFFFFFFFF��ʾʧ��
//};


#endif // __MTTIMER_H__