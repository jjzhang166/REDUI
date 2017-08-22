#ifndef __DUID3D_H__
#define __DUID3D_H__

#include "Dui3DAuto.h"
#include "DirectUI.h"

extern LPCWSTR prop_device;

// forward declaration
class Device;
class SubDevice;
class ImageResource;
class ImageLayer;
class GdiLayer;
class RenderTarget;
class Effect;

class Scene;
class Camera;

//class LightGroup;
struct Light;
	class AmbientLight;
	class PointLight;
	class SpotLight;
	class DirectionLight;
//class LightCollection;

class Material;

class Model;
class XModel;
class BoxModel;
class CylinderModel;
class PolygonModel;
class SphereModel;
class TorusModel;
class TextModel;
class TeapotModel;

class AnimationSet;
class Entity;

class KeyFrame;
class KeyFrameSet;
class FrameSet;
class StoryBoard;


#define disallow_copy_and_assign(x) \
	private: \
		x(const x& xref); \
		void operator=(const x& xref); \
	public:

#define disallow_implicit_constructors(x) \
	protected: x(){} virtual ~x(){} \
	disallow_copy_and_assign(x) \
	public:

#define declare_protect_constructor(x) protected: x(); public:

// ObjectStateType
enum ObjectStateType
{
	ost_visible = 0,
	ost_enable,

	ost_dword_align = 0x7fffffff
};

//////////////////////////////////////////////////////////////////////////
//
typedef enum
{
	ilt_unknown			= 0,

	ilt_normal,		// Image��׼ģʽ�����϶���
	ilt_center,		// Image����ģʽ
	ilt_tile,		// Imageƽ��ģʽ
	ilt_stretch,	// Image����ģʽ
	ilt_maxfit,		// Image����ģʽ������ʺϣ�����ͼƬ��߱���
	ilt_squares,	// Image�Ź���ģʽ

} ImageLayoutType;

typedef enum
{
	FRT_ALL			= 0,
	FRT_IMAGE		= 0x00000001,	// by image.name
	FRT_EFFECT		= 0x00000002,	// by effect.technique
	FRT_STORY		= 0x00000004,	// by story.name
	FRT_MODEL		= 0x00000008,	// by model.name
	FRT_SCENE		= 0x00000010,	// by scene.name
	FRT_ENTITY		= 0x00000020,	// by entity.name

	FRT_FORCE_DWORD	= 0x7fffffff
} FindResourceType;

namespace d3d
{
	bool IsValid(bool bAutoCreate=false);
	HWND SetActiveScriptWindow(HWND hwnd);

	// �������Ӧ�����߳̽���ǰ����
	void OnThreadFinish();

	COLORREF KeyColor();
};

//////////////////////////////////////////////////////////////////////////
class GdiPath
{
public:
	GdiPath();

	BOOL IsValid() { return _path_type!=pt_unknown; }
	DWORD Time() { return _timestamp; }
	BOOL Parse(LPCOLESTR strPath);

	BOOL Draw(HDC hdc, RECT rc);

private:
	// RelativePoint ��POINT���ͣ��� x/y �����ֵ���Ǿ���ֵ����Է����� xDir/yDir ָ��������ֵ����ʱ�Ӳ������룬�Թ��������ĵ�ֵ
	struct RelativePoint 
	{
		union
		{
			struct
			{
				DWORD xDir:1;	// ˮƽ����FALSE - �������ߣ�TRUE - ������ұߡ�Ĭ�� FALSE
				DWORD yDir:1;	// ��ֱ����FALSE - ������ϱߣ�TRUE - ������±ߡ�Ĭ�� FALSE
				DWORD xPercent:1;	// fx ֵ��һ���ٷֱ�������ʱ x �������float���ͣ����ݴ���Ŀ��ָ��
				DWORD yPercent:1;	// fy ֵ�ǰٷֱ�
			};
			DWORD flags;
		};
		union
		{
			LONG x;			// ˮƽ���ֵ
			float fx;
		};
		union
		{
			LONG y;			// ��ֱ���ֵ
			float fy;
		};

		RelativePoint(LONG _x=0, LONG _y=0) : flags(0), x(_x), y(_y) {}
		BOOL Parse(LPCOLESTR szx, LPCOLESTR szy);
		long GetX(const RECT& rc);
		long GetY(const RECT& rc);
	};

	CSimpleArray<RelativePoint> _points;
	CSimpleArray<BYTE> _types;

	DWORD _timestamp;

	enum PathType
	{
		pt_unknown			= 0,
		pt_rectangle,				// rectangle [left [top [right [bottom]]]] (0-2 points) ���Σ����δָ����������Ч���� pt_unknown ��ͬ
		pt_roundrect,				// roundrect [corner_cx [, corner_cy]] (0-1 point) Բ�Ǿ���
		pt_polygon,					// polygon point1 point2 [point3 [... pointN]]  (2-N points) �����
		pt_ellipse,					// ellipse [left [top [right [bottom]]]] (0-2 points) ��Բ
		pt_chord,					// chord point1 point2 [left [top [right [bottom]]]] (2-4 points) ��Բ���߶��ཻ
		pt_pie,						// pie point1 point2 [left [top [right [bottom]]]] (2-4 points) ��Բ�������뾶�ཻ
		pt_polydraw,
	};
	PathType _path_type;

	BOOL Draw_Custom(HDC hdc, RECT rc);
	BOOL Draw_Rectangle(HDC hdc, RECT rc);
	BOOL Draw_RoundRect(HDC hdc, RECT rc);
	BOOL Draw_Polygon(HDC hdc, RECT rc);
	BOOL Draw_Ellipse(HDC hdc, RECT rc);
	BOOL Draw_Chord(HDC hdc, RECT rc);
	BOOL Draw_Pie(HDC hdc, RECT rc);
};

// 3D�豸
class Device
{
public:
	// Allocator
	static Device* New(HWND hwnd);
	void Dispose();
	void Relayout(); // ������׼���������µ�ҳ�棬�����������ͷ�������Դ

	// Render one frame, call all RenderTarget::Render and ImageLayer::Render
	void Render();

	void Reset(); // notify that size of window is changed

	// for GDI operations, toplevel
	HDC GetDC();
	void ReleaseDC(HDC hdc);

	// caret for layed window
	BOOL CreateCaret(HBITMAP hBitmap, int nWidth, int nHeight, GdiLayer* pOwner);
	BOOL DestroyCaret();
	BOOL ShowCaret(BOOL bShow);
	BOOL SetCaretPos(int X, int Y);
	BOOL IsBlindTimer(UINT nID);

	BOOL IsLayeredWindow();
	HWND Handle();

	// children window
	void AddChild(HWND hWnd);
	void RemoveChild(HWND hWnd);
	void ResizeChild(HWND hWnd);
	//void UpdateChild(HWND hWnd, HDC hdc, RECT rc);

	HWND GetGhostWindow();

	//void RegisterNamedObject(LPCOLESTR name, IDispatch* disp);
	//void UnRegisterNamedObject(IDispatch* disp);
	void SetWindowObject(IDispatch* disp);
	void SetScriptObject(HANDLE handle);

	//IDispatch* FindModel(LPCOLESTR name);
	Scene* FindScene(LPCOLESTR nameorindex);
	BOOL FindNamedObject(LPCOLESTR name, DWORD findType=FRT_ALL, IDispatch** ppDisp=NULL);

	// XML Parser Filter
	BOOL IsChildNode(HANDLE pNode, IDispatch** ppDisp=NULL);

	disallow_implicit_constructors(Device)

	HRESULT GetStoryBoards(VARIANT* val); // ������ʾ�弯��
	HRESULT PutNewStoryBoard(VARIANT* val); // ����һ���µ���ʾ��

	// ����ʱ������
	HRESULT GetCurrentScene(VARIANT* val);
	HRESULT GetCurrentEntity(VARIANT* val);
	HRESULT GetCurrentModel(VARIANT* val);
	HRESULT GetCurrentMaterial(VARIANT* val);
	HRESULT GetCurrentEffect(VARIANT* val);
	HRESULT GetCurrentTextureAspectRatio(VARIANT* val); // ��ȡ��ǰ�����߱ȣ������ǰ�������ڣ��򷵻�Ĭ��ֵ 1

	Begin_Disp_Map(Device)
		Disp_PropertyGet(10, StoryBoards)	Disp_Alias(10, Stories)
		Disp_PropertyPut(11, NewStoryBoard)
		Disp_PropertyGet(20, CurrentScene)
		Disp_PropertyGet(21, CurrentEntity)
		Disp_PropertyGet(22, CurrentModel)
		Disp_PropertyGet(23, CurrentMaterial)
		Disp_PropertyGet(24, CurrentEffect)
		Disp_PropertyGet(25, CurrentTextureAspectRatio)
	End_Disp_Map()
};

// subdevice
class SubDevice
{
public:
	static SubDevice* New(Device* parent, HWND hwnd);
	void Dispose();
};

// ԭʼͼƬ��Դ�����첽����URL
class ImageResource
{
public:
	// Allocator
	static ImageResource* New(Device* device, LPCOLESTR url, LPCOLESTR name=NULL);
	//void Dispose();

	bool IsLoaded();

	long GetWidth();
	long GetHeight();

	void SetClipRect(LPCRECT pClip=NULL);

	disallow_implicit_constructors(ImageResource)
};

// 2D��̬�������ܽ�����������ɫ��Ҳ���ܰ���ͼƬ���������Ĵ�С��GdiLayer��ȫ��ͬ������������ǰ��
class ImageLayer
{
public:
	//// Allocator
	//static ImageLayer* New(GdiLayer* owner); // ʹ�ô��ַ�ʽ������������������ǰ���������������� GdiLayer ��ֱ�ӻ�ȡ
	//void Dispose();
	void SetColor(COLORREF clrTopLeft, COLORREF clrTopRight=0, COLORREF clrBottomRight=0, COLORREF clrBottomLeft=0);
	void SetImage(ImageResource* img, int imageLayoutType = ilt_normal);
	void Clear();

	// texture is valid
	//bool isValid() {return false;}

	disallow_implicit_constructors(ImageLayer)
};

// 2D��̬GDI����棬��ֱ��ִ��GDI����
class PaintCallback
{
public:
	virtual void Do3DPaint() = 0;
};

class GdiLayer
{
public:
	// Allocator
	static GdiLayer* New(Device* device, LONG x, LONG y, LONG width, LONG height, GdiLayer* parent=NULL);
	void Dispose();
	Device* GetDevice() const;

	void SetPaintCallback(PaintCallback* cbPaint);
	IExtensionContainer* GetExtensionContainer();
	void SetExtensionContainer(IExtensionContainer* pExtContainer);

	// for GDI operations
	HDC GetDC();
	void ReleaseDC(HDC hdc);

	bool Parent(GdiLayer* p, BOOL bOrder=false);
	GdiLayer* Parent();
	void ZIndex(long z);

	// background and foreground
	ImageLayer* Background();
	//void ForegroundCount(ULONG count);
	ImageLayer* Foreground();
	void RemoveForeground(ImageLayer* il);

	void Resize(LONG width, LONG height);
	void Move(LONG left, LONG top, LONG right, LONG bottom);
	void Move(LPCRECT prc);
	void Clip(GdiPath* path); // ���ڲü�����
	void ClipContent(LPCRECT prcClip); // ���ڲü��ӿؼ�
	BOOL State(ObjectStateType ost);
	void State(ObjectStateType ost, BOOL value);
	void SetAsTarget(BOOL bTarget=FALSE);
	void SetScene(Scene* scene);
	void SetName(LPCOLESTR name);
	void BindWindow(HWND hwnd, IPropertyBag* pb=NULL/*, BOOL bTransparent=FALSE, LPCOLESTR anotherWinClassName=NULL, long lRenderType=0*/);

	void Invalidate(BOOL bDrawNow=FALSE);

	Begin_Disp_Map(GdiLayer)
		//Disp_PropertyGet(1, Camera, Camera)
		//Disp_PropertyGet(2, AmbientLight, AmbientLight)
		//Disp_PropertyGet(3, Lights)
		//Disp_PropertyGet(4, Entities)
		//Disp_PropertyPut(11, NewEntity)
	End_Disp_Map()

	disallow_implicit_constructors(GdiLayer)
};

// ��ȾĿ��
//class RenderTarget
//{
//public:
//	// Allocator
//	static RenderTarget* New(Device* device, LONG width, LONG height);
//	virtual void Dispose();
//
//	// viewport
//	//void setViewport(ULONG x, ULONG y, ULONG w, ULONG h);
//	//void setViewport(const RECT& rc);
//
//
//	disallow_implicit_constructors(RenderTarget)
//};

// ��Ч�����첽����

class Effect
{
public:
	// Allocator
	static Effect* New(Device* device, LPCOLESTR url=NULL, LPCOLESTR name=NULL, LPCOLESTR data=NULL);
	//void Dispose();

	bool IsLoaded();

	// ������ǰ�����Ŀ��ò�������Ϊ���Զ�д
	BOOL __DispidOfName(LPCOLESTR szName, DISPID* pDispid);
	HRESULT __Invoke(DISPID dispid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT *pVarResult);

	Begin_Disp_Map(Effect)
	End_Disp_Map()

	disallow_implicit_constructors(Effect)
};

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////// 
// ��������3D����
// 
// ������;���� GdiLayer ��ʱ�����ĸ���
enum SceneUsage
{
	SU_NONE				= 0,	// ������Ч
	SU_BACKGROUND		,		// ���������滻������
	SU_PRECONTENT		,		// ����λ�ڱ���֮�ϣ�����֮��
	SU_CONTENT			,		// ���������滻���ݲ㣬��ΪĬ��ֵ
	SU_POSTCONTENT		,		// ����λ������֮�ϣ�ǰ��֮��
	SU_FOREGROUND		,		// ���������滻ǰ����
	SU_ALL					// �����滻�������ݣ����������ݡ�ǰ����
};

// ��������Ϊ2D��3D��Ŧ����Ҳ��һ����������ȾĿ�꣬�ڲ���һ�������3D���磬���豸�б���󶨵�һ�� GdiLayer ����
// ������DUI����Ϊһ����ʽ������Ϊһ�ֶ����ؼ������Դ���Ϊ���
class Scene //: public GdiLayer
{
public:
	static Scene* New(Device* device);
	//void Dispose();

	HRESULT InitNamedItem(DISPPARAMS* params) { return S_OK; }

	// ����XML�ӽڵ�
	void ParseAttribute(HANDLE hNode);
	BOOL IsChildNode(HANDLE hChild);

	void SetMousePos(POINT* ppt); // ppt==NULL means that mouse leaves.

	static Scene* NewAutoInstance();
	static void DeleteAutoInstance(Scene* p);

	CComBSTR Name;
	bool LightEnabled;
	SceneUsage Usage;

	CComVariant RenderCallback; // callback. string or dispatch

	HRESULT GetScene(VARIANT* val);
	Camera& GetCameraRef();
	COLOR& GetMouseLightRef();
	AmbientLight& GetAmbientLightRef();
	//HRESULT GetAmbientLight(VARIANT* ret);
	HRESULT GetLights(VARIANT* ret); // ȡ���ռ��ϣ����8����Դ
	HRESULT GetEntities(VARIANT* ret); // ȡʵ����󼯺�
	HRESULT GetActiveEntity(VARIANT* ret); // ȡ����µ�ʵ�����
	void Update();
	
	HRESULT PutNewEntity(VARIANT* val); // ����һ����ʵ�壬���Դ��� Entity������ xxxModel���������ģ�Ͷ������Զ���ģ���д���һ����ʵ��

	Begin_Auto_Disp_Map(Scene)
		Disp_Property(1, Name, CComBSTR)
		Disp_PropertyGet(2, Camera, Camera)
		Disp_Property(3, LightEnabled, bool)
		Disp_PropertyGet(4, AmbientLight, AmbientLight)
		Disp_PropertyGet(5, Lights)
		Disp_PropertyGet(6, Entities)
		Disp_Property(7, Usage, long)		Disp_Alias(7, As)
		Disp_Property_Member(8, OnRender, RenderCallback, CComVariant)
		Disp_Property(9, MouseLight, COLOR)
		Disp_PropertyGet(10, Scene)
		Disp_PropertyPut(11, NewEntity)
		Disp_PropertyGet(12, ActiveEntity)

		Disp_Method(100, Update, void, 0)
	End_Disp_Map()

	disallow_implicit_constructors(Scene)
};
Implement_Creatable_NamedItem(Scene)

// ����������Ծ����ӿھ����ͶӰ����
class Camera
{
public:
	//static Camera* New(Scene* scene, float x, float y, float z);
	//void Dispose();

	D3DXVECTOR3 m_Position; // �����λ��

	float m_Pitch; // ̧ͷ��ͷ�Ƕȣ���X����ת������15��ʾ15��
	float m_Yaw; // ��ת��ת�Ƕȣ���Y����ת��
	float m_Roll; // ������ת�Ƕȣ���Z����ת��

	float m_Zoom; // ���ű�����Ĭ��1
	float m_Fov; // ��Ұ�Ƕȣ�Ĭ��45��
	//float Aspect; // �������������ȾĿ��ȷ��
	float m_NearPlane; // �ӿڿ��ӽ��棬Ĭ��0
	float m_FarPlane; // �ӿڿ���Զ�棬Ĭ��1000
	bool m_Ortho; // �Ƿ�����ͶӰ��Ĭ��false
	// 

	HRESULT SetProperties(VARIANT* val);

	void ParseAttribute(HANDLE hNode);

	Begin_Disp_Map(Camera)
		Disp_Property_Member(101, Zoom, m_Zoom, float)
		Disp_Property_Member(102, Fov, m_Fov, float)
		Disp_Property_Member(103, Pitch, m_Pitch, float)
		Disp_Property_Member(104, Yaw, m_Yaw, float)
		Disp_Property_Member(105, Roll, m_Roll, float)
		Disp_Property_Member(106, NearPlane, m_NearPlane, float)
		Disp_Property_Member(107, FarPlane, m_FarPlane, float)
		Disp_Property_Member(108, Ortho, m_Ortho, bool)
		Disp_Property_Member(109, Position, m_Position, D3DXVECTOR3)
		Disp_PropertyPut(200, Properties)
	End_Disp_Map()

	disallow_implicit_constructors(Camera)
};
Implement_Ref_Creator(Camera)

//////////////////////////////////////////////////////////////////////////
// �����ƹ�
class AmbientLight
{
	disallow_implicit_constructors(AmbientLight)
public:
	bool m_Enabled;
	COLOR m_Color;

	void ParseAttribute(HANDLE hNode);

	Begin_Disp_Map(AmbientLight)
		Disp_Property_Member(100, Enable, m_Enabled, bool)
		//Disp_Property_Member(101, r, m_Color.r, float)
		//Disp_Property_Member(102, g, m_Color.g, float)
		//Disp_Property_Member(103, b, m_Color.b, float)
		//Disp_Property_Member(104, a, m_Color.a, float)
		//Disp_PropertyPut(200, Properties)
		Disp_Property_Member(110, Color, m_Color, COLOR)
	End_Disp_Map()
};
Implement_Ref_Creator(AmbientLight)

// ��Դ
struct Light
{
	bool m_Enabled;
	CComBSTR m_Name;
	D3DLIGHT9 m_Light;

	void ParseAttribute(HANDLE hNode);
	//HRESULT InitNamedItem(DISPPARAMS* params) { return S_OK; }

	Begin_Disp_Map(Light)
		Disp_Property_Member(1, Enable, m_Enabled, bool)
		Disp_Property_Member(2, Name, m_Name, CComBSTR)
	End_Disp_Map()
};
//Implement_DispCollection(LightCollection, Light);

// ���Դ
class PointLight : public Light
{
	disallow_implicit_constructors(PointLight)
public:
	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		DispParams dp(params);
		// ��ǰֻ֧�ֵ�һ����������ENABLE
		if (dp.Count()>0) dp.GetBool(0,m_Enabled);

		return S_OK;
	}


	// �������������Զ�����CreateInstance/DeleteInstance���ã�ʵ���������������Բ��� NEW/delete �Լ�������ʵ�ʴ���������
	static PointLight* NewAutoInstance();
	static void DeleteAutoInstance(PointLight* p);

	Begin_Auto_Disp_Map(PointLight, Light)
		//Disp_Property_Member(100, Enable, m_Enabled, bool)
		Disp_Property_Member(101, Diffuse, m_Light.Diffuse, D3DCOLORVALUE) // color
		Disp_Property_Member(102, Specular, m_Light.Specular, D3DCOLORVALUE) // color
		Disp_Property_Member(103, Ambient, m_Light.Ambient, D3DCOLORVALUE) // color
		Disp_Property_Member(104, Position, m_Light.Position, D3DVECTOR) // vector3
		Disp_Property_Member(105, Range, m_Light.Range, float) // ���վ���
		// ����������˥���㷨��Atten = 1/( att0 + att1 * d + att2 * d^2)
		Disp_Property_Member(107, Attenuation0, m_Light.Attenuation0, float) // ����˥�����ӣ�Ĭ��0
		Disp_Property_Member(108, Attenuation1, m_Light.Attenuation1, float) // ����˥�����ӣ�Ĭ��1
		Disp_Property_Member(109, Attenuation2, m_Light.Attenuation2, float) // ƽ��˥�����ӣ�Ĭ��0
		//Disp_PropertyPut(200, Properties)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(PointLight)
Implement_Ref_Creator(PointLight)

// �۹��
class SpotLight : public Light
{
	disallow_implicit_constructors(SpotLight)
public:
	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		DispParams dp(params);
		// ��ǰֻ֧�ֵ�һ����������ENABLE
		if (dp.Count()>0) dp.GetBool(0,m_Enabled);

		return S_OK;
	}

	// �������������Զ�����CreateInstance/DeleteInstance���ã�ʵ���������������Բ��� NEW/delete �Լ�������ʵ�ʴ���������
	static SpotLight* NewAutoInstance();
	static void DeleteAutoInstance(SpotLight* p);

	Begin_Auto_Disp_Map(SpotLight, Light)
		//Disp_Property_Member(100, Enable, m_Enabled, bool)
		Disp_Property_Member(101, Diffuse, m_Light.Diffuse, D3DCOLORVALUE) // color
		Disp_Property_Member(102, Specular, m_Light.Specular, D3DCOLORVALUE) // color
		Disp_Property_Member(103, Ambient, m_Light.Ambient, D3DCOLORVALUE) // color
		Disp_Property_Member(104, Position, m_Light.Position, D3DVECTOR) // vector3
		Disp_Property_Member(105, Direction, m_Light.Direction, D3DVECTOR) // vector3
		Disp_Property_Member(106, Range, m_Light.Range, float)
		Disp_Property_Member(107, Attenuation0, m_Light.Attenuation0, float)
		Disp_Property_Member(108, Attenuation1, m_Light.Attenuation1, float)
		Disp_Property_Member(109, Attenuation2, m_Light.Attenuation2, float)
		Disp_Property_Member(110, Falloff, m_Light.Falloff, float) // default 1.0
		Disp_Property_Member(111, Theta, m_Light.Theta, float) // angel,in andians. range(0 - Phi)
		Disp_Property_Member(112, Phi, m_Light.Phi, float) // angel, in andias. range(0 - PI)
		//Disp_PropertyPut(200, Properties)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(SpotLight)
Implement_Ref_Creator(SpotLight)

// ƽ�й�Դ
class DirectionLight : public Light
{
	disallow_implicit_constructors(DirectionLight)
public:
	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		DispParams dp(params);
		// ��ǰֻ֧�ֵ�һ����������ENABLE
		if (dp.Count()>0) dp.GetBool(0,m_Enabled);

		return S_OK;
	}

	// �������������Զ�����CreateInstance/DeleteInstance���ã�ʵ���������������Բ��� NEW/delete �Լ�������ʵ�ʴ���������
	static DirectionLight* NewAutoInstance();
	static void DeleteAutoInstance(DirectionLight* p);

	Begin_Auto_Disp_Map(DirectionLight, Light)
		//Disp_Property_Member(100, Enable, m_Enabled, bool)
		Disp_Property_Member(101, Diffuse, m_Light.Diffuse, D3DCOLORVALUE) // color
		Disp_Property_Member(102, Specular, m_Light.Specular, D3DCOLORVALUE) // color
		Disp_Property_Member(103, Ambient, m_Light.Ambient, D3DCOLORVALUE) // color
		Disp_Property_Member(104, Direction, m_Light.Direction, D3DVECTOR) // vector3
		//Disp_PropertyPut(200, Properties)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(DirectionLight)
Implement_Ref_Creator(DirectionLight)


//////////////////////////////////////////////////////////////////////////
class Material
{
	disallow_implicit_constructors(Material)
public:
	bool m_Enabled; // default:true��������ʵ��ʱ��default:false
	D3DMATERIAL9 material;

	CComVariant onTransform; // ���ñ任֮ǰ�Ļص�
	CComVariant onRender;
	CComVariant onPrepareEffect;

	void ParseAttribute(HANDLE hNode);

#ifdef _DEBUG
	void __DebugOnAddRef();
	void __DebugOnRelease();
#endif // _DEBUG

	CComBSTR& GetTextureNameRef();
	HRESULT PutTextureName(VARIANT* val);
	CComBSTR& GetTechniqueRef();

	void OnPropertyChanged(DISPID dispid, LPCOLESTR name);

	Begin_Disp_Map(Material) // ע�⣺���ʲ��ܴ�����ֻ�ܴ�����������ͨ�����Զ�ȡ
		Disp_Property_Member(1, Enabled, m_Enabled, bool)
		Disp_Property(2, TextureName, CComBSTR)
		Disp_Property(3, Technique, CComBSTR)
		Disp_Property(4, onRender, CComVariant)
		Disp_Property(5, onPrepareEffect, CComVariant)
		Disp_Property_Member(101, Diffuse, material.Diffuse, D3DCOLORVALUE) // color
		Disp_Property_Member(102, Specular, material.Specular, D3DCOLORVALUE) // color
		Disp_Property_Member(103, Ambient, material.Ambient, D3DCOLORVALUE) // color
		Disp_Property_Member(104, Emissive, material.Emissive, D3DCOLORVALUE) // color
		Disp_Property_Member(105, Power, material.Power, float)
	End_Disp_Map()
};

//////////////////////////////////////////////////////////////////////////
// 3D ģ��
// ��XML�����У�ʹ����ͬ��model��ǩ��ͨ��typeָ��ģ�����ͣ�����type="box"��ʾ������ģ�ͣ������ָ����Ĭ��Ϊ��ͨģ��
// �ⲿXģ��Ҳ����ָ��type���ԣ�����ָ��src����ָʾ�ⲿ�ļ�·��

#define public_model_methods(model) \
public: \
	static model* New(Device* device); \
	static model* NewAutoInstance(); \
	static void DeleteAutoInstance(model* p); \
	HRESULT InitNamedItem(DISPPARAMS* params) { return S_OK; } \
	CComBSTR& GetNameRef(); \
	Transform3D& GetTransformRef(); \
	CComVariant& GetonTransformRef(); \
	CComVariant& GetonRenderRef(); \
	CComVariant& GetonPrepareEffectRef(); \
	CComVariant& GetonMouseEnterRef(); \
	CComVariant& GetonMouseLeaveRef(); \
	CComVariant& GetonClickRef(); \
	CComVariant& GetonDblClickRef(); \
	HRESULT GetMaterials(VARIANT* val); \
	HRESULT GetParent(VARIANT* val); \
	HRESULT GetChildren(VARIANT* val); \
	HRESULT GetEntities(VARIANT* val); \
	IDispatch* CreateEntity(); \
	IDispatch* SubmitChange(); \
	void Remove();

#define public_model_disp() \
	Disp_Property(1001, Name, CComBSTR) \
	Disp_PropertyGet(1002, Transform, Transform3D) \
	Disp_PropertyGet(1003, Materials) \
	Disp_PropertyGet(1004, Parent) \
	Disp_PropertyGet(1005, Children) \
	Disp_PropertyGet(1006, Entities) \
	Disp_Property(1050, onTransform, CComVariant) \
	Disp_Property(1051, onRender, CComVariant) \
	Disp_Property(1052, onPrepareEffect, CComVariant) \
	Disp_Property(1053, onMouseEnter, CComVariant) \
	Disp_Property(1054, onMouseLeave, CComVariant) \
	Disp_Property(1055, onClick, CComVariant) \
	Disp_Property(1056, onDblClick, CComVariant) \
	Disp_Method(2000, Remove, void, 0) \
	Disp_Method(2001, CreateEntity, IDispatch*, 0) \
	Disp_Method(2002, SubmitChange, IDispatch*, 0) /* ���Ӱ��ģ�ʹ��������Ա��ı䣬������ô˷���֪ͨģ�͸��� */

// ��ͨģ�ͣ���������������Զ���
class Model
{
	disallow_implicit_constructors(Model)
	public_model_methods(Model)
public:
	/*
	*	���δָ�����ߣ������ǵ����ɽ�ȡ�����Ƿ�Ϊ����ָ���������������� 
	*	���ָ�����������������򽫿��������������ɷ������� 
	*	���δָ������������������ֵֻ�Զ�Ӧ�������������á� ����ܵ����������γ�Сƽ�档
	 */
	Vector3DCollection m_Normals;		// ���������ϣ���ѡ
	Vector3DCollection m_Points;		// ���㼯�ϣ���ѡ
	Point2DCollection m_TextureCoordinates;	// �������꼯�ϣ���ѡ��ͨ��ȡֵ��Χ [0,1]
	IntCollection m_TriangleIndices;		// �����������ϣ��Ǹ��������飬������3�ı�������ѡ������˳�����ĳ�������������滹�Ǳ���

	void ParseAttribute(HANDLE hNode);

	// ���¼���������ǰֻ֧���ַ������͸�ֵ������ "1,0,1 2,1,0 3,4,6"���ö��Ż�ո�ָ�
	HRESULT PutNormals(VARIANT* val);
	HRESULT PutPoints(VARIANT* val);
	HRESULT PutTextureCoordinates(VARIANT* val);
	HRESULT PutTriangleIndices(VARIANT* val);

	Begin_Auto_Disp_Map(Model)
		public_model_disp()
		Disp_Property_Member(1, Normals, m_Normals, Vector3DCollection)
		Disp_Property_Member(2, Points, m_Points, Vector3DCollection)
		Disp_Property_Member(3, TextureCoordinates, m_TextureCoordinates, Point2DCollection)
		Disp_Property_Member(4, TriangleIndices, m_TriangleIndices, IntCollection)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(Model)

// ��ģ����һ����Ч��ģ�ͣ�������ִ���κ���Ⱦ
class NullModel
{
	disallow_implicit_constructors(NullModel)
	public_model_methods(NullModel)
public:

	Begin_Auto_Disp_Map(NullModel)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(NullModel)

// Xģ�ͣ�ģ�������������ⲿX�ļ�
class XModel
{
	disallow_implicit_constructors(XModel)
	public_model_methods(XModel)
public:

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(XModel)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(XModel)

// ����ģ��
class QuadModel
{
	disallow_implicit_constructors(QuadModel)
	public_model_methods(QuadModel)
public:

	float Width;	// ��ȣ�Ĭ�� 2.0
	float Height;	// �߶ȣ�Ĭ�� 2.0

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(QuadModel)
		Disp_Property(1, Width, float)
		Disp_Property(2, Height, float)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(QuadModel)

// ������ģ��
class BoxModel
{
	disallow_implicit_constructors(BoxModel)
	public_model_methods(BoxModel)
public:

	float Width;	// ��ȣ�Ĭ�� 100.0
	float Height;	// �߶ȣ�Ĭ�� 100.0
	float Depth;	// ��ȣ�Ĭ�� 100.0

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(BoxModel)
		Disp_Property(1, Width, float)
		Disp_Property(2, Height, float)
		Disp_Property(3, Depth, float)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(BoxModel)

// Բ����ģ��
class CylinderModel
{
	disallow_implicit_constructors(CylinderModel)
	public_model_methods(CylinderModel)
public:

	float Radius1;
	float Radius2;
	float Length;
	ULONG Slices;	// ������Ƭ������Ĭ�� 5
	ULONG Stacks;	// ����ջ������Ĭ�� 5

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(CylinderModel)
		Disp_Property(1, Radius1, float)
		Disp_Property(2, Radius2, float)
		Disp_Property(3, Length, float)
		Disp_Property(4, Slices, ULONG)
		Disp_Property(5, Stacks, ULONG)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(CylinderModel)

// �����ģ��
class PolygonModel
{
	disallow_implicit_constructors(PolygonModel)
	public_model_methods(PolygonModel)
public:

	float Length;	// ÿ���ߵĳ��ȣ�Ĭ�� 50
	ULONG Sides;	// ������������������3��Ĭ���� 5

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(PolygonModel)
		public_model_disp()
		Disp_Property(1, Length, float)
		Disp_Property(2, Sides, ULONG)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(PolygonModel)

// ����ģ��
class SphereModel
{
	disallow_implicit_constructors(SphereModel)
	public_model_methods(SphereModel)
public:

	float Radius;	// �뾶������>=0��Ĭ�� 50
	ULONG Slices;	// ������Ƭ������Ĭ�� 5
	ULONG Stacks;	// ����ջ������Ĭ�� 5

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(SphereModel)
		public_model_disp()
		Disp_Property(1, Radius, float)
		Disp_Property(4, Slices, ULONG)
		Disp_Property(5, Stacks, ULONG)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(SphereModel)

// Բ���壨��̥��ģ��
class TorusModel
{
	disallow_implicit_constructors(TorusModel)
	public_model_methods(TorusModel)
public:

    float InnerRadius;	// ��Ȧ�뾶��Ĭ�� 30
    float OuterRadius;	// ��Ȧ�뾶��Ĭ�� 50
    ULONG Sides;		// ����α�������С��3��Ĭ�� 5
    ULONG Rings;		// Բ��������С��3��Ĭ�� 5

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(TorusModel)
		public_model_disp()
		Disp_Property(1, InnerRadius, float)
		Disp_Property(2, OuterRadius, float)
		Disp_Property(3, Sides, ULONG)
		Disp_Property(4, Rings, ULONG)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(TorusModel)

// ����ģ��
class TextModel
{
	disallow_implicit_constructors(TextModel)
	public_model_methods(TextModel)
public:

	// ���������������� TRUETYPE ����
	FONT Font;

	CComBSTR Text;		// Ҫ��Ⱦ���ı�
    float Deviation;	// ���������������ƫ�TrueType�����һ�����ԣ�����>=0�����Ϊ0����ʹ������Ĭ��ֵ��Ĭ���� 0
    float Extrusion;	// �ı������ڸ� Z �᷽�����ȡ�Ĭ�� 0.1
    bool Center;		// �Ƿ���ģ�;��У�Ĭ�� false����ԭ��λ���ı����½�

	void ParseAttribute(HANDLE hNode);

	//D3DXVECTOR3& GetCenterRef();

	Begin_Auto_Disp_Map(TextModel)
		public_model_disp()
		Disp_Property(1, Text, CComBSTR)
		Disp_Property(2, Deviation, float)
		Disp_Property(3, Extrusion, float)
		Disp_Property(4, Font, FONT)
		Disp_Property(6, Center, bool)
		//Disp_Property(5, Center, D3DXVECTOR3)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(TextModel)

// ���ģ��
class TeapotModel
{
	disallow_implicit_constructors(TeapotModel)
	public_model_methods(TeapotModel)
public:

	void ParseAttribute(HANDLE hNode);

	Begin_Auto_Disp_Map(TeapotModel)
		public_model_disp()
	End_Disp_Map()
};
Implement_Creatable_NamedItem(TeapotModel)

// ��������ֻ�� XModel �ſ����ж�����
class AnimationSet
{
	disallow_implicit_constructors(AnimationSet)
public:
	static AnimationSet* NewAutoInstance();
	static void DeleteAutoInstance(AnimationSet* p);

	Begin_Auto_Disp_Map(AnimationSet)
	End_Disp_Map()
};

//////////////////////////////////////////////////////////////////////////
// 3D ����ʵ�壬ÿ��ʵ��Ӧ�ù���һ��ģ�ͣ�ʵ�岻��ֱ�Ӵ����������ģ���д���
class Entity
{
	disallow_implicit_constructors(Entity)
public:
	bool m_Enabled; // Ĭ�� true
	CComBSTR m_Name;
	Transform3D m_WorldTransform; // �ṩ����任
	
	// �¼��ص�
	CComVariant onTransform; // ���ñ任֮ǰ�Ļص�
	CComVariant onRender;
	CComVariant onPrepareEffect;
	CComVariant onMouseEnter;
	CComVariant onMouseLeave;
	CComVariant onClick;
	CComVariant onDblClick;

	void SetEffectParameters(LPCOLESTR params);

	void Remove();		// ɾ���Լ�

	static void DeleteAutoInstance(Entity* p);

	Material& GetMaterialRef();
	CComBSTR& GetParametersRef();
	HRESULT GetScene(VARIANT* val);
	HRESULT GetModel(VARIANT* val);
	HRESULT GetParent(VARIANT* val);
	HRESULT GetParentIndex(VARIANT* val); // ���ڸ�ʵ��򳡾�����ʵ�弯�ϵ�������
	HRESULT GetChildren(VARIANT* val);
	HRESULT PutParameters(VARIANT* val);

	// ��������ط���
	HRESULT GetAnimationSets(VARIANT* val); // ��ȡ����������
	void ResetTime(); // ��λ����ʱ��
	void SetAnimationSet(VARIANT as); // ���õ�ǰ���������������������������ƻ��� AnimationSet ����

	Begin_Auto_Disp_Map(Entity)
		Disp_Property_Member(1, Enable, m_Enabled, bool)
		Disp_Property_Member(2, Name, m_Name, CComBSTR)
		Disp_PropertyGet_Member(3, Transform, m_WorldTransform, Transform3D)
		Disp_PropertyGet(4, Material, Material)
		Disp_PropertyGet(5, AnimationSets)
		Disp_Property(6, Parameters, CComBSTR)
		Disp_PropertyGet(19, Scene)
		Disp_PropertyGet(20, Model)
		Disp_PropertyGet(21, Parent)
		Disp_PropertyGet(22, ParentIndex)
		Disp_PropertyGet(23, Children)
		Disp_Property(50, onTransform, CComVariant)
		Disp_Property(51, onRender, CComVariant)
		Disp_Property(52, onPrepareEffect, CComVariant)
		Disp_Property(53, onMouseEnter, CComVariant)
		Disp_Property(54, onMouseLeave, CComVariant)
		Disp_Property(55, onClick, CComVariant)
		Disp_Property(56, onDblClick, CComVariant)
		Disp_Method(100, ResetTime, void, 0)
		Disp_Method(101, SetAnimationSet, void, 1, VARIANT)
		Disp_Method(201, Remove, void, 0)
	End_Disp_Map()
};

//////////////////////////////////////////////////////////////////////////

// �ؼ�֡
class KeyFrame
{
	disallow_implicit_constructors(KeyFrame)
public:
	// ��ͨ����ʵ���������ṩ��Ч��keyframeset����
	static KeyFrame* New(KeyFrameSet* keyframeset);

	// �����Զ�������ʵ��������ű�������keyframeset�������Ժ������� AddTo ����
	static KeyFrame* NewAutoInstance();
	static void DeleteAutoInstance(KeyFrame* p);

	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		return S_OK;
	}

	void ParseAttribute(HANDLE hNode);

	CComBSTR Name; // ����

	HRESULT GetKeyTime(VARIANT* val);	// ��ȡ�ؼ�֡ʱ��ֵ(float)
	HRESULT PutKeyTime(VARIANT* val);	// ���ùؼ�֡ʱ��ֵ(float/string['h:m:s'])
	HRESULT GetKeyValue(VARIANT* val);	// ��ȡ�ؼ�֡����ֵ(float/long/ulong/double/COLOR/Vector3d...)
	HRESULT PutKeyValue(VARIANT* val);	// ���ùؼ�֡����ֵ(float/..., ����string)

	IDispatch* AddTo(IDispatch* keyframeset);	// ���ӵ��ؼ�֡����
	void Remove();

	Begin_Auto_Disp_Map(KeyFrame)
		Disp_Property(1, Name, CComBSTR)

		Disp_Property(10, KeyTime)		Disp_Alias(10, Time)
		Disp_Property(11, KeyValue)		Disp_Alias(11, Value)

		Disp_Method(200, AddTo, IDispatch*, 1, IDispatch*)
		Disp_Method(201, Remove, void, 0)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(KeyFrame)

// �ؼ�֡��
class KeyFrameSet
{
	disallow_implicit_constructors(KeyFrameSet)
public:
	// ��ͨ����ʵ���������ṩ��Ч��story����
	static KeyFrameSet* New(StoryBoard* story);

	// �����Զ�������ʵ��������ű�������story�������Ժ������� AddTo ����
	static KeyFrameSet* NewAutoInstance();
	static void DeleteAutoInstance(KeyFrameSet* p);

	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		return S_OK;
	}

	void ParseAttribute(HANDLE hNode);
	BOOL IsChildNode(HANDLE hChild);

	void OnPropertyChanged(DISPID dispid, LPCOLESTR name);

	CComBSTR Name; // ����

	CComBSTR& GetTargetTypeRef();				// �ַ��������� "float"�����ֶα���
	HRESULT GetTarget(VARIANT* val);			// ��ȡĿ����󣬿��������ƣ�Ҳ�����Ƕ���
	HRESULT PutTarget(VARIANT* val);			// ����Ŀ����󣬿��������ƣ�Ҳ�����Ƕ���
	CComBSTR& GetTargetAttributeRef();			// Ŀ������������ƣ��ַ���
	bool& GetReverseRef();						// �Ƿ�ִ�ж�����ת��Ĭ�� false
	HRESULT PutReverse(VARIANT* val);			// �����Ƿ�ִ�ж�����ת���������õ�ֵ�� true/false/"closure"(�պϷ�ת)
	ULONG& GetRepeatRef();						// �����ظ���������������0 ��ʾ�����ظ�
	HRESULT PutRepeat(VARIANT* val);			// ���ö����ظ�����������������"forever"��Ĭ��Ϊ 1
	bool& GetSplineRef();						// �Ƿ�ʹ�� B ������Ĭ�� false
	float& GetDelayRef();						// �����ӳ�����ʱ�䣬��λ�룬Ĭ�� 0
	HRESULT PutDelay(VARIANT* val);
	float& GetIdleRef();						// ÿ���ظ�֮ǰ�Ŀ�����ͣʱ�䣬Ĭ�� 0
	HRESULT PutIdle(VARIANT* val);
	bool& GetIsClosureRef();					// ֻ�����Ƿ�պϷ�ת

	IDispatch* AddTo(IDispatch* story);			// ���ӵ���ʾ����
	void Remove();

	HRESULT GetKeyFrames(VARIANT* val);
	HRESULT PutNewKeyFrame(VARIANT* val);

	Begin_Auto_Disp_Map(KeyFrameSet)
		Disp_Property(1, Name, CComBSTR)
		Disp_PropertyGet(2, KeyFrames)
		Disp_PropertyPut(3, NewKeyFrame)

		Disp_PropertyPut(10, TargetType, CComBSTR)
		Disp_Property(11, Target)
		Disp_Property(12, TargetAttribute, CComBSTR)
		Disp_Property(13, Reverse, bool)
		Disp_Property(14, Repeat, ULONG)
		Disp_Property(15, Spline, bool)
		Disp_Property(16, Delay, float)
		Disp_Property(17, Idle, float)
		Disp_PropertyGet(18, IsClosure, bool)

		Disp_Method(200, AddTo, IDispatch*, 1, IDispatch*)
		Disp_Method(201, Remove, void, 0)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(KeyFrameSet)

// From/To/By����֡������һ������� KeyFrameSet
class FrameSet
{
	disallow_implicit_constructors(FrameSet)
public:
	// ��ͨ����ʵ���������ṩ��Ч��story����
	static FrameSet* New(StoryBoard* story);

	// �����Զ�������ʵ��������ű�������story�������Ժ������� AddTo ����
	static FrameSet* NewAutoInstance();
	static void DeleteAutoInstance(FrameSet* p);

	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		return S_OK;
	}

	void ParseAttribute(HANDLE hNode);

	CComBSTR Name; // ����

	CComBSTR& GetTargetTypeRef();				// �ַ��������� "float"�����ֶα���
	CComBSTR& GetTargetAttributeRef();			// Ŀ������������ƣ��ַ���
	bool& GetReverseRef();						// �Ƿ�ִ�ж�����ת��Ĭ�� false
	ULONG& GetRepeatRef();						// �����ظ���������������0 ��ʾ�����ظ�
	float& GetDurationRef();					// ����ʱ�����ڣ�����������λ��
	float& GetDelayRef();						// �����ӳ�����ʱ�䣬��λ�룬Ĭ�� 0
	HRESULT PutDelay(VARIANT* val);
	float& GetIdleRef();						// ÿ���ظ�֮ǰ�Ŀ�����ͣʱ�䣬Ĭ�� 0
	HRESULT PutIdle(VARIANT* val);
	VARIANT& GetFromRef();						// From ֵ������ȡ����Ŀ������
	VARIANT& GetToRef();						// To ֵ������ȡ����Ŀ������
	VARIANT& GetByRef();						// By ֵ������ȡ����Ŀ������

	HRESULT GetTarget(VARIANT* val);			// ��ȡĿ����󣬿��������ƣ�Ҳ�����Ƕ���
	HRESULT PutTarget(VARIANT* val);			// ����Ŀ����󣬿��������ƣ�Ҳ�����Ƕ���
	HRESULT PutRepeat(VARIANT* val);			// ���ö����ظ�����������������"forever"��Ĭ��Ϊ 1
	HRESULT PutDuration(VARIANT* val);			// ���ö���ʱ�����ڣ�����������λ�룬Ĭ�� 1 ��
	HRESULT PutFrom(VARIANT* val);				// ���� From ֵ�����ͱ���ƥ��Ŀ�����ͣ������ַ�����ʼ������������ã����ʾ�Ӷ����ȡ��ǰֵ
	HRESULT PutTo(VARIANT* val);				// ���� To ֵ�����ͱ���ƥ��Ŀ�����ͣ������ַ�����ʼ������������ã����ʾ To = From + By�����δ����By����Ӷ����ȡ��ǰֵ
	HRESULT PutBy(VARIANT* val);				// ���� By ֵ�����ͻ���ƥ��Ŀ�����ͣ�������һ�������򸡵���ֵ�������ַ�����To �� By ������������һ����

	IDispatch* AddTo(IDispatch* story);			// ���ӵ���ʾ����
	void Remove();								// ɾ���Լ�

	Begin_Auto_Disp_Map(FrameSet)
		Disp_Property(1, Name, CComBSTR)

		Disp_PropertyPut(10, TargetType, CComBSTR)
		Disp_Property(11, Target)
		Disp_Property(12, TargetAttribute, CComBSTR)
		Disp_Property(13, Reverse, bool)
		Disp_Property(14, Repeat, ULONG)
		Disp_Property(15, Delay, float)
		Disp_Property(16, Idle, float)
		
		Disp_Property(17, Duration, float)
		Disp_Property(18, From, VARIANT)
		Disp_Property(19, To, VARIANT)
		Disp_Property(20, By, VARIANT)

		Disp_Method(200, AddTo, IDispatch*, 1, IDispatch*)
		Disp_Method(201, Remove, void, 0)
	End_Disp_Map()
};
Implement_Creatable_NamedItem(FrameSet)

// ������ʾ�壬����һ������
class StoryBoard
{
	disallow_implicit_constructors(StoryBoard)
public:
	// ��ͨ����ʵ���������ṩ��Ч��device����
	static StoryBoard* New(Device* device);

	// �����Զ�������ʵ��������ű��������豸�����Զ����
	static StoryBoard* NewAutoInstance();
	static void DeleteAutoInstance(StoryBoard* p);

	HRESULT InitNamedItem(DISPPARAMS* params)
	{
		return S_OK;
	}

#ifdef _DEBUG
	void __DebugOnAddRef();
	void __DebugOnRelease();
#endif // _DEBUG

	void ParseAttribute(HANDLE hNode);
	BOOL IsChildNode(HANDLE hChild);

	CComBSTR Name; // ����

	bool& GetStartedRef();
	bool& GetStoppedRef();
	bool& GetPausedRef();

	// ����4�����Ʒ��������ض�������
	/*
	 *	Stop ��������˵����
	 *		stopBehavior - �ַ������ͣ�����ָ����ֹͣ����ʱ����ʾ��Ӧ����ζ���������������ֵ֮һ��
	 *			* current  - ���ֵ�ǰֵ���� Stop ������ִ��ʱ���������Ƶ�����ֵ���ֵ�ǰ����ʱֵ��stopTime �������ԣ�onstop �ص�����ִ�С�����Ĭ��ֵ��
	 *			* beginNow - �����ص���ʼֵ���� Stop ������ִ��ʱ���������Ƶ�����ֵ�������õ���ʼֵ��stopTime �������ԣ�onstop �ص�����ִ�С�
	 *			* endNow   - �����ص�����ֵ���� Stop ������ִ��ʱ���������Ƶ�����ֵ�������õ�����ֵ��stopTime �������ԣ�onstop �ص�����ִ�С�
	 *			* begin    - �Զ�����ʽ�ص���ʼֵ���� Stop ������ִ��ʱ���������Ƶ�����ֵ�� stopTime ָ����ʱ���ڴӵ�ǰֵ�仯����ʼֵ��onstop �ص�Ҳ���ӳ�ִ�С�
	 *			* end      - �Զ�����ʽ�ص�����ֵ���� Stop ������ִ��ʱ���������Ƶ�����ֵ�� stopTime ָ����ʱ���ڴӵ�ǰֵ�仯������ֵ��onstop �ص�Ҳ���ӳ�ִ�С�
	 *			
	 *		stopTime - �������ͣ���ʾ�Զ�����ʽֹͣ��ǰ����ʱ��ֹͣ������������ڣ���λ�롣Ĭ��ֵΪ 1 �롣
	 */
	IDispatch* Start();
	IDispatch* Stop(VARIANT stopBehavior=CComVariant(), float stopTime=1.0f);
	IDispatch* Pause();
	IDispatch* Resume();

	// �¼�����
	HRESULT GetOnStart(VARIANT* val);
	HRESULT PutOnStart(VARIANT* val);
	HRESULT GetOnStop(VARIANT* val);
	HRESULT PutOnStop(VARIANT* val);
	HRESULT GetOnPause(VARIANT* val);
	HRESULT PutOnPause(VARIANT* val);
	HRESULT GetOnResume(VARIANT* val);
	HRESULT PutOnResume(VARIANT* val);
	HRESULT GetOnStep(VARIANT* val);
	HRESULT PutOnStep(VARIANT* val);
	HRESULT PutEventHandler(VARIANT* val); // �����¼���ͨ���˷���һ��������

	HRESULT GetFrameSets(VARIANT* val);
	HRESULT PutNewFrameSet(VARIANT* val);

	IDispatch* AddTo(IDispatch* window);				// ���ӵ������豸�У����ض�������
	void Remove();			// ���豸��ɾ���Լ�

	Begin_Auto_Disp_Map(StoryBoard)
		Disp_Property(1, Name, CComBSTR)
		Disp_PropertyGet(2, FrameSets)
		Disp_PropertyPut(3, NewFrameSet)

		Disp_PropertyGet(10, Started, bool)
		Disp_PropertyGet(11, Stopped, bool)
		Disp_PropertyGet(12, Paused, bool)
		Disp_PropertyPut(22, EventHandler)
		Disp_Property(23, OnStart)
		Disp_Property(24, OnStop)
		Disp_Property(25, OnPause)
		Disp_Property(26, OnResume)
		Disp_Property(27, OnStep)

		Disp_Method(100, Start, IDispatch*, 0)
		//Disp_Method(101, Stop, UseParamsMap)
		Disp_Method_Ext(101, Stop)
		Disp_Method(102, Pause, IDispatch*, 0)
		Disp_Method(103, Resume, IDispatch*, 0)

		Disp_Method(200, AddTo, IDispatch*, 1, IDispatch*)
		Disp_Method(201, Remove, void, 0)
	End_Disp_Map()

	Begin_Method_Params_Map(StoryBoard)
		Method_Params(Stop, 2, 2, IDispatch*, VARIANT, float)
	End_Method_Params_Map()
};
Implement_Creatable_NamedItem(StoryBoard)

#endif // __DUID3D_H__