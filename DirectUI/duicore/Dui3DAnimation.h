#ifndef __DUI3DANIMATION_H__
#define __DUI3DANIMATION_H__

#include "DuiD3DImpl.h"

class CCubic;
class iAttributeData;
class iStoryBoard;
	class iFrameSetBase;
		class iKeyFrameSet;
		class iFrameSet; // iFrameSetBase + iKeyFrame
	class iKeyFrame;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ���߲�ֵ������
class CCubic
{
public:
	float m_fa;
	float m_fb;
	float m_fc;
	float m_fd;
	float m_fe;

	CCubic(void) : m_fa(0), m_fb(0), m_fc(0), m_fd(0), m_fe(0) {}
	CCubic(float a, float b, float c, float d, float e) : m_fa(a), m_fb(b), m_fc(c), m_fd(d), m_fe(e) {}
	//~CCubic(void){};

	// u = [0..1] ������������ֵ��m_fe ����
	float eval(float u)
	{
		return ( (((m_fd * u) + m_fc) * u + m_fb) * u + m_fa);
	};
	// ������������ֵ��m_fe ������
	float line(float u)
	{
		return ( (m_fe - m_fa) * u + m_fa);
	};
};

//////////////////////////////////////////////////////////////////////////

// ��������ֵ��ֵ�����ɲ����ṩ
class iAttributeData : public CComVariant
{
public:
	// �����������ͣ��������ͨ���ͣ�����VT_I4��VT_R4������adt��vt��ֵ��ͬ��
	// ����Ƕ�Ԫ���ṹ���ͣ���vt==VT_DISPATCH,adt==__ClassName(class)
	// ���adt==NULL�����ʾ��ֵ��δ��ʼ������
	LPCOLESTR adt;

	iAttributeData() : adt(NULL) {}

	void operator = (const iAttributeData& other) { CopyFrom(&other); adt=other.adt; }

	void Create(LPCOLESTR type); // Create �� InitFromString ���߶�Ӧ�ø�����һ�Σ�����˳��Ҫ��
	bool InitFromString(LPCOLESTR szInit);
	bool CopyFrom(const VARIANT* pSrc); // �� VARIANT �������ݣ����Զ�Create
	bool Sum(iAttributeData* src, iAttributeData* src2); // ��ͣ���������ڵ�ǰ�����У��Զ�����
	bool Calc(iAttributeData* from, iAttributeData* to, float percent, CCubic* c0=NULL, CCubic* c1=NULL, CCubic* c2=NULL, CCubic* c3=NULL); // Calc ���Զ�����Create
	static ULONG GetSplineDim(LPCOLESTR type); // ��ȡԪ���ݸ�����������һ����1�����4
	bool SetSplineSample(float* s0, float* s1=NULL, float* s2=NULL, float* s3=NULL);
};

// �ؼ�֡������һ���ؼ�֡ʱ���ֵ�Ķ���
class iKeyFrame : public KeyFrame
	, public TOrderList<iKeyFrame,true,0,float> // ������ KeyFrameSet ��
{
public:
	iKeyFrameSet* m_keyframe_set; // �����ؼ�֡��
	float m_keytime; // �ؼ�֡ʱ�䣬��ʽ [[h:]m:]s
	iAttributeData m_keyvalue; // �ؼ�֡����ֵ
	CCubic* m_cubic[4]; // ��ǰ֡����һ֡�������㷨�����ڷǱպϣ����һ֡�޴�ֵ����ֵ�ɹؼ�֡�����ã��ɹؼ�֡��ͳһ�����ͷţ������ڴ��ͷš�������4��ԭ��

	iKeyFrame(iKeyFrameSet* kfs=NULL);
	float key_time() { return m_keytime; }

	void createAttributeData(LPCOLESTR type);

	void setSpline(ULONG count, ULONG index, CCubic* cubics0=NULL, CCubic* cubics1=NULL, CCubic* cubics2=NULL, CCubic* cubics3=NULL);
	//void Dispose() { delete this; }
};

// �ؼ�֡������һ����������
class iFrameSetBase : public TList<iFrameSetBase> // ������ StoryBoard ��
{
public:
	iStoryBoard* m_story;

	CComVariant m_target; // �󶨵Ķ��󣬿��������ƣ�Ҳ�����Ƕ��󣬲���Ϊ��
	CComBSTR m_target_attribute; // �󶨵Ķ������ԣ�����Ϊ��
	CComBSTR m_datatype; // ��������ֵ�����ͣ����� "float"
	
	bool m_reverse; // �Ƿ��Զ���ת��Ĭ�� false
	bool m_closure; // �Ƿ�պϣ�Ĭ��false��ͨ�� Reverse = 'closure' ���ñպ�ģʽ����ֱ���ṩ����
	ULONG m_repeat; // �ظ�������0��ʾ��Զ�ظ���Ĭ�� 1
	float m_delay; // �����ӳ�����ʱ�䣬Ĭ�� 0
	float m_idle; // �ظ�֮�����ͣʱ�䣬��Ҫ�ظ�֮ǰ�ȱ��ֶ��ʱ�䣬Ĭ�� 0

	iFrameSetBase(iStoryBoard* sb=NULL);
	virtual ~iFrameSetBase();
	
	struct __tagRuntime
	{
		bool finished; // ����״̬����ʾ��������ɣ�������Զ�ظ��Ķ�����Ч
		ULONG count; // ����ɴ���
		bool reversing; // �Ƿ����ڷ�ת
		iAttributeData vOld; // ��������ֵ����������ʱ�ж��Ƿ���ͬ
		iAttributeData vCurr, vFinished; // ���״̬�� STOP_PENDING����ִ�� Stop ʱҪ����������ֵ
	} __runtime;
	void clearRuntime();

	virtual void step(float fTimeDelta) = 0;
	virtual void onstart();
	virtual void onstop() = 0;
	virtual void onstopPending() = 0;
	virtual IDispatch* getDispatch() = 0;
	virtual LPCOLESTR getName() = 0;

	//void Dispose() { getDispatch()->Release(); }
	void unload();
	bool isFinished();

protected:
	CComDispatchDriver _get_object();
	HRESULT _set_property(iAttributeData* val);
	HRESULT _get_property(VARIANT* val);
};

class iKeyFrameSet : public KeyFrameSet
	, public iFrameSetBase
{
public:
	iKeyFrame* m_keyframes; // �ؼ�֡�ļ���
	bool m_spline; // �Ƿ�ʹ��B����
	CCubic* m_cubics[4]; // ���4����������ֻ�йؼ�֡����֧��B������ÿ���ؼ�֡����Ϊ������

	iKeyFrameSet(iStoryBoard* sb=NULL);
	~iKeyFrameSet();

	float get_duration()
	{
		if (m_keyframes==NULL || m_keyframes->Next()==NULL) return 0;
		return m_keyframes->getAt(m_keyframes->count()-1)->m_keytime;
	}

	virtual void step(float fTimeDelta);
	virtual void onstart();
	virtual void onstop();
	virtual void onstopPending();
	virtual IDispatch* getDispatch() { return KeyFrameSet::GetDispatch(); }
	virtual LPCOLESTR getName() { return Name; }

//private:
	void _clearSpline();
	void _createSpline();
};

// From/To/By �������͵�֡���ͣ�ͬʱ�ǹؼ�֡��
class iFrameSet : public FrameSet
	, public iFrameSetBase // ��Ϊһ�ֹؼ�֡��
	//, public iKeyFrame // ��Ϊһ�ֹؼ�֡
{
public:
	iAttributeData m_from, m_to, m_by; // From/To/By ֵ
	DWORD m_has_from:1; // From/To/Byֵ�Ƿ��ѳ�ʼ�������û�г�ʼ����������Ҫ�Ӷ����ȡ
	DWORD m_has_to:1;
	DWORD m_has_by:1;
	float m_duration; // ���ڣ�Ĭ�� 1 ��

	iFrameSet(iStoryBoard* sb=NULL);
	~iFrameSet();

	virtual void step(float fTimeDelta);
	virtual void onstart();
	virtual void onstop();
	virtual void onstopPending();
	virtual IDispatch* getDispatch() { return FrameSet::GetDispatch(); }
	virtual LPCOLESTR getName() { return Name; }

	//virtual void Dispose() { delete this; }
};

// ������ʾ�壬��ʾһ������
class iStoryBoard : public StoryBoard
	, public TList<iStoryBoard> // �������豸��
{
public:
	iDevice* m_device;
	iFrameSetBase* m_keyframe_sets; // �ؼ�֡���ļ���

	bool m_started;	// ʱ�����Ƿ�������
	bool m_stopped; // ʱ�����Ƿ���ֹͣ
	bool m_paused;	// ʱ�����Ƿ�����ͣ
	// 
	float m_current_time;	// ��ǰʱ�䡣һ��������ʼ���ţ���ʱ�佫��0��������

	CComVariant m_onstart, m_onstop, m_onpause, m_onresume, m_onstep; // �ű����õĻص�

	// ֹͣ��Ϊ����
	enum
	{
		stop_current = 0,
		stop_beginNow,
		stop_endNow,
		stop_begin,
		stop_end
	};
	int m_stop_behavior;
	bool m_stop_pending; // �Ƿ�����ִ��ֹͣ����
	float m_stop_time; // ֹͣ��������ʱ��

public:
	iStoryBoard(iDevice* device=NULL);
	~iStoryBoard();

	// �ж϶����Ƿ��������С�������������У���������Ⱦ��ʱ����������ֹ��ʱ��
	bool isRunning(bool bMeOnly=false);
	// step������Ҫ�ķ�����ÿ���豸��Ⱦ֮ǰ��Ҫִ�д˷���������Զ��������ò���
	void step(float fTimeDelta, bool bNext=true);

	void start();
	void stop(int stopBehavior=0, float stopTime=1.f);
	void pause();
	void resume();

	//void Dispose() { delete this; }
	void unload();
};



#endif // __DUI3DANIMATION_H__