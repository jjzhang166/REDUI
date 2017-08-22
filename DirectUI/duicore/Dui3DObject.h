#ifndef __DUI3DOBJECT_H__
#define __DUI3DOBJECT_H__

#include "DuiD3DImpl.h"

class iCamera;
class iSceneTarget;
class iScene;
class iAmbientLight;
//class iLight;
	class iPointLight;
	class iDirectionLight;
	class iSpotLight;
class iLightGroup;
class iModelBase;
	class iModel;
	class iQuadModel;
	class iBoxModel;
	class iCylinderModel;
	class iPolygonModel;
	class iSphereModel;
	class iTorusModel;
	class iTextModel;
	class iTeapotModel;
	class iXModel;
	class iNullModel;
class iEntity;


#define __foreach_model(v) \
	v(Model) \
	v(QuadModel) \
	v(BoxModel) \
	v(CylinderModel) \
	v(PolygonModel) \
	v(SphereModel) \
	v(TorusModel) \
	v(TextModel) \
	v(TeapotModel) \
	v(XModel) \
	v(NullModel)

#define cookie_child 1
#define cookie_sibling 2

// scene m_target
class iSceneTarget : public iRenderTarget
{
public:
	iScene* m_scene;

public:
	iSceneTarget(iScene* scene);
	~iSceneTarget();

	virtual void render_content();
};

// camera
class iCamera : public Camera
	//, TList<iCamera>
{
public:
	iScene* m_scene;

	iCamera(iScene* scene);
	~iCamera();

	void reset_params();


	D3DXVECTOR3 m_right; // ������ҷ�
	D3DXVECTOR3 m_up; // ������Ϸ�
	D3DXVECTOR3 m_ahead; // �����ǰ��

	//D3DXMATRIX m_world; // ָʾ������򣬵�һ�б�ʾ�ң��ڶ��б�ʾ�ϣ������б�ʾǰ�������б�ʾ�۾�λ�ã���ʱ���ã�
	//
	//const D3DXVECTOR3* getWorldRight()	{ return (D3DXVECTOR3*)&m_world._11; }
	//const D3DXVECTOR3* getWorldUp()		{ return (D3DXVECTOR3*)&m_world._21; }
	//const D3DXVECTOR3* getWorldAhead()	{ return (D3DXVECTOR3*)&m_world._31; }
	//const D3DXVECTOR3* getWorldEyePt()	{ return (D3DXVECTOR3*)&m_world._41; }

	D3DXMATRIX get_view_matrix();
	D3DXMATRIX get_projection_matrix();
};

// ambient light
class iAmbientLight : public AmbientLight
{
public:
	iAmbientLight(bool enable);
};

// point light
class iPointLight : public PointLight
{
public:
	iPointLight();
	//~iPointLight();
};

// direction light
class iDirectionLight : public DirectionLight
{
public:
	iDirectionLight();
	//~iDirectionLight();
};

// spot light
class iSpotLight : public SpotLight
{
public:
	iSpotLight();
	//~iSpotLight();
};

// lights group
class iLightGroup //: public LightGroup
{
public:
	iAmbientLight m_ambientLight; // �û�������
	Light m_lights[8]; // ��Դ���ϣ����8����Դ

	iLightGroup();
	~iLightGroup();

	//bool setLight(ULONG index, Light* light);
	static HRESULT CALLBACK OnUpdated(long index, LPCOLESTR name, CComVariant& value, LPVOID data);
};

// Ч�����������ڱ���Ч���ļ��еĲ���ֵ����Щֵ��XML��ʼ�������ɽű��趨
class iEffectParams
{
public:
	CComBSTR params_string; // ���� "g_fTime:2.5; g_vPos:0 0 -1.5;"

	CSimpleMap<D3DXHANDLE, EffectParamValue*> params;

	iEffectParams() : _effect(NULL), _cached(false) {}
	~iEffectParams();
	void clear();

	void set_params_string(LPCOLESTR szParams);
	EffectParamValue* get_param_value(iEffect* e, D3DXHANDLE hParam, bool bAutoCreate=false);

private:
	iEffect* _effect;
	bool _cached;
	void _cache(iEffect* e);
};

// ������Ϣ
class iMaterial : public Material
{
public:
	CComPtr<IDirect3DDevice9> device;
	long index; // ���ʶ�Ӧ������������ȡ��2D���е��[0-x]������� AutoValue ��ʾ��̬��ȡ��2D�-1��ʾ��Ч
	CComBSTR texname; // ���ʶ�Ӧ���������ƣ�������ͼƬ�ļ�����Ҳ������ͼƬ��ԴID��Ҳ�����ǿؼ�ID�������������Ҫ�����á�
	CComPtr<IDirect3DBaseTexture9> texture; // ���������һ���ļ�����Դ����ȡ�󻺴浽��������������ͨ����Volumn�������Cube��������ǿؼ�����Ӧ��NULL

	CComBSTR technique; // ���Ӧ����Ч������������ָ���������ơ����δָ�������������ϵͳĬ��Ч��
	iEffect* effect; // �����Ч�������ݼ�����������Ч��
	iEffectParams effect_params; // �����л����Ч������

	iMaterial();
	~iMaterial();

	bool load(IDirect3DDevice9* dev);
	virtual void on_reset();
	void resetName(LPCOLESTR szName);
	void resetName(long lName); // ���ö�̬������������̬����ͨ���ǵ�ǰ��������������ӱ��档
private:
	CDownload download;
	static void CALLBACK onDownloadComplete(LPVOID pData, LPSTREAM pStream);
};

typedef BOOL (* FINDMODELPROC)(iModelBase* pModel, LPVOID data); 

// model base
// ģ����һ����Դ���������豸�У����ڳ�����ʵ��ʹ��ʱ����Ҫ����һ��ʵ�����
class iModelBase : public TList<iModelBase>
				, public TList<iModelBase, cookie_child>
				, public TList<iModelBase, cookie_sibling>
{
	friend iEntity;
public:
	iDevice* m_device;
	CMarkupNode m_node;
	iModelBase* m_parent;
	CComBSTR m_name;

	iModelBase* m_children;
	iModelBase* m_siblings;

	CComPtr<ID3DXMesh> m_mesh; // ���û�ж�������Ӧ���ṩһ����Ч��MESH
	iMaterial* m_materials; // ��������
	DWORD m_matNum; // ��������
	bool m_useMaterials; // �Ƿ�ʹ�ò��ʣ�Ĭ�� true

	Transform3D m_local_transform; // ��Ը�ģ�͵ı��ر任
	//CSimpleArray<iMaterial*> m_mapped_materials; // ӳ��Ĳ��ʣ������滻ģ���е�ԭʼ���ʣ�ͨ������ӳ��

	// �����MESH����
	struct _MeshInfo
	{
		DWORD numVertices;
		DWORD numFaces;
		DWORD bytesPerVertex;
		CComPtr<IDirect3DIndexBuffer9> ib;
		CComPtr<IDirect3DVertexBuffer9> vb;
		CComPtr<IDirect3DVertexDeclaration9> decl;
		D3DXVECTOR3 boundMin, boundMax, boundCenter;
		D3DXVECTOR3 sphereCenter;
		float sphereRadius;

		_MeshInfo() : numFaces(0), numVertices(0), bytesPerVertex(0), boundMin(0,0,0), boundMax(0,0,0), boundCenter(0,0,0), sphereCenter(0,0,0), sphereRadius(0) {}
		void clear() { /*numFaces=numVertices=bytesPerVertex=0;*/ ib=NULL;vb=NULL;decl=NULL; }
	} m_meshInfo;

	iEntity* m_entities; // ʹ�ø�ģ�͵�ʵ���б�
	iEffectParams effect_params; // ģ���л����Ч������

	CComVariant onTransform;
	CComVariant onRender;
	CComVariant onPrepareEffect;
	CComVariant onMouseEnter;
	CComVariant onMouseLeave;
	CComVariant onClick;
	CComVariant onDblClick;

	iModelBase(iDevice* device=NULL);
	~iModelBase();

	virtual void on_reset();
	void unload();

	void setParent(iDevice* device);
	void setParent(iModelBase* parent);

	virtual void createMesh() = 0; // ��ʼ�����߸ı�MESH���Ժ���Ҫ���´���MESH
	virtual iEntity* createEntity();
	virtual void pre_render();
	virtual void render();
	virtual IDispatch* getDispatch() = 0;
	virtual void getMaterials(CDispatchArray* pArr);

	// helper
	void setFVF(DWORD fvf); // �ı䶥��� FVF
	void setVertexDecl(const D3DVERTEXELEMENT9* pDecl, bool bSplitVertexForOptimalTangents = false); // �ı䶥������

	void resetMesh(); // �������MESH�Ĳ��������˱仯�����ô˺������´���MESH������Ӱ�������Ϣ

	void enumAllModels(FINDMODELPROC proc, LPVOID data);

	static iModelBase* fromObject(IUnknown* unk); // �������ȡ iModelBase ָ��
	static void createModelByNode(HANDLE node, iDevice* device=NULL, iModelBase* parent=NULL, IDispatch** ppDisp=NULL);
	// �ݹ����ñ任����
	void updateMatrices(const D3DXMATRIX* mtParent);

protected:
	static BOOL _enumModel(iModelBase* pStart, FINDMODELPROC proc, LPVOID data);
	void _updateMeshInfo(); // ���泣��MESH����
	D3DXMATRIX m_world; // ����������������Ⱦ֮ǰ�������� updateMatrices ������
};

#define impletement_model_virtual() \
	virtual IDispatch* getDispatch() { return GetDispatch(); }

// Null model
class iNullModel : public NullModel
	, public iModelBase
{
public:
	iNullModel(iDevice* device=NULL) : iModelBase(device) {}

	virtual void createMesh() {}
	impletement_model_virtual()
};

// custom model
class iModel : public Model
				, public iModelBase
{
public:
	static const DWORD m_defFVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;
	struct ModelVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		float u,v;

		ModelVertex() : normal(0,0,1) {}
	};

	iModel(iDevice* device=NULL);
	~iModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iQuadModel : public QuadModel
				, public iModelBase
{
public:
	iQuadModel(iDevice* device=NULL);
	~iQuadModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iBoxModel : public BoxModel
				, public iModelBase
{
public:
	iBoxModel(iDevice* device=NULL);
	~iBoxModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iCylinderModel : public CylinderModel
				, public iModelBase
{
public:
	iCylinderModel(iDevice* device=NULL);
	~iCylinderModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iPolygonModel : public PolygonModel
				, public iModelBase
{
public:
	iPolygonModel(iDevice* device=NULL);
	~iPolygonModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iSphereModel : public SphereModel
				, public iModelBase
{
public:
	iSphereModel(iDevice* device=NULL);
	~iSphereModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iTorusModel : public TorusModel
				, public iModelBase
{
public:
	iTorusModel(iDevice* device=NULL);
	~iTorusModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iTextModel : public TextModel
				, public iModelBase
{
public:
	iTextModel(iDevice* device=NULL);
	~iTextModel();

	virtual void createMesh();
	impletement_model_virtual()
};

class iTeapotModel : public TeapotModel
				, public iModelBase
{
public:
	iTeapotModel(iDevice* device=NULL);
	~iTeapotModel();

	virtual void createMesh();
	impletement_model_virtual()
};

// ���XMODELӵ�ж�������������ģ��Ϊÿ��ʵ�崴��һ�� xAnimInstance
class iAnimInstance
{
public:
	iXModel* model;
	CComPtr<ID3DXAnimationController> spAC;
	CComPtr<ID3DXAnimationSet> spAS; // ��ǰ����
	DWORD curTrack;	// ��ǰTRACE��һ���豸ͨ����2��TRACK
	float curTime;	// ��ǰʱ��
	float speedAdjust;	// �ٶȵ������ӣ�Ĭ��1.0��Խ���ٶ�Խ��
	float moveTransitionTime;	// ��һ�������л�����һ��������ʱ�䣬Խ��Խ����Ĭ��0.25

	iAnimInstance(iXModel* m, ID3DXAnimationController* ac);
};

// x mesh model
class iXModel : public iModelBase
		, public XModel
		, public iObjectState
		//, public TList<iXModel> // �ֵ�����
{
	CDownload download;

public:
	struct MeshContainerEx;
	struct FrameEx;

	// mesh ֡������Ϣ
	struct MeshContainerEx : public D3DXMESHCONTAINER
	{
		CComBSTR name; // ���û����Name��ת����UNICODE
		FrameEx* frame; // ����֡

		//IDirect3DTexture9**  exTextures;		// Array of texture pointers  
		iMaterial* exMaterials; // �������飬���û����pMaterials

		// Skinned mesh variables
		CComPtr<ID3DXMesh>   exSkinMesh;			// ��Ƥ����
		D3DXMATRIX*			 exBoneOffsets;			// ����ƫ�ƾ������飬ÿ������һ��
		D3DXMATRIX**		 exFrameCombinedMatrixPointer;	// ֡����ָ�����飬ÿ������һ��
		
		MeshContainerEx()
		{
			frame=NULL; exMaterials=NULL; exBoneOffsets=NULL; exFrameCombinedMatrixPointer=NULL;
			ZeroMemory((D3DXMESHCONTAINER*)this, sizeof(D3DXMESHCONTAINER));
		}
	};

	// mesh ֡��Ϣ
	struct FrameEx : public D3DXFRAME
	{
		CComBSTR name; // ���û����Name��ת����UNICODE
		D3DXMATRIX exCombinedTransformationMatrix;
	};

	// mesh ֡ϵ�з�����
	class MeshAllocator : public ID3DXAllocateHierarchy
	{
	public:
		STDMETHOD(CreateFrame)(LPCSTR Name, LPD3DXFRAME *ppNewFrame );
		STDMETHOD(CreateMeshContainer)(LPCSTR Name, 
			CONST D3DXMESHDATA *pMeshData, 
			CONST D3DXMATERIAL *pMaterials, 
			CONST D3DXEFFECTINSTANCE *pEffectInstances, 
			DWORD NumMaterials, 
			CONST DWORD *pAdjacency, 
			LPD3DXSKININFO pSkinInfo, 
			LPD3DXMESHCONTAINER *ppNewMeshContainer);
		STDMETHOD(DestroyFrame)(LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(LPD3DXMESHCONTAINER pMeshContainerToFree);
	};

	// �Ƕ���������ͨMESH�����浽����
	CComPtr<ID3DXMesh> m_meshCache;
	// Animation Objects
	FrameEx* m_frameRoot;	// ��֡
	MeshContainerEx* m_meshRoot;	// ���������ڵݹ����ù�������ʱ����
	CComPtr<ID3DXAnimationController> m_animController;
	
	D3DXMATRIX* m_boneMatrices;	// ������������
	DWORD m_maxBones;	// ������MESH�е���������

public:
	iXModel(iDevice* device=NULL, LPCOLESTR xurl=NULL, LPCOLESTR name=NULL);
	~iXModel();

	bool load(LPCOLESTR xurl, LPCOLESTR name=NULL);
	void unload();

	virtual void on_reset();
	virtual iEntity* createEntity();
	virtual void createMesh();
	virtual void getMaterials(CDispatchArray* pArr);
	virtual void pre_render();
	impletement_model_virtual()

private:

	static void CALLBACK onDownloadComplete(LPVOID pData, LPSTREAM pStream);

	CComPtr<IStream> _stream; // cache
	void _create();

	// �ݹ����ù�������
	void updateBonesPtr(FrameEx* frame);
	void updateGetMaterials(FrameEx* frame, CDispatchArray* pArr);
	void clearCaches(FrameEx* frame);
};

//////////////////////////////////////////////////////////////////////////
// animation set
class iAnimationSet : public AnimationSet
{
public:
	CComPtr<ID3DXAnimationSet> m_as;
};


typedef BOOL (* FINDENTITYPROC)(iEntity* entity, LPVOID data);
//////////////////////////////////////////////////////////////////////////
// entity
// һ��ʵ��������һ��ģ�͵�ʵ�������һ��ģ�Ϳ��Դ������ʵ����󣬲�ͬ����ʹ�ò�ͬ���������
// ʵ���б�����ģ����
class iEntity : public Entity
			, public TList<iEntity> // ������ģ����
			, public TList<iEntity, cookie_child> // ��ʵ��
			, public TList<iEntity, cookie_sibling> // �ֵ�ʵ��
{
public:
	iScene* m_scene;
	// �����XML�ڵ㣬�����������ʽָ��ʵ�壬�������Ч
	CMarkupNode m_node;
	iEntity* m_parent;
	iModelBase* m_model;	// ʵ��ʹ�õ�ģ��
	iAnimInstance* m_anim; // ���ģ�;��ж����������������õ�����
	CDispatchArray* m_animations; // ���ģ�;��ж������������˳�Ա��Ч��������ȡ����������
	D3DXMATRIX m_mtWorld;	// ʵ��ĳ�ʼ������󣬳�ʼֵ��XML��̬��ȡ������Ķ�̬ת�����Ӵ� Entity �̳У�ͨ���ýű�����ת������
	iMaterial m_Material; // ��ǰӦ�õĲ���
	iEffectParams effect_params; // ʵ���л����Ч������

	iEntity* m_children; // ��ʵ��
	iEntity* m_siblings; // �ֵ�ʵ��

	iEntity(iModelBase* model, iScene* scene=NULL, iEntity* parent=NULL);
	~iEntity();

	void setParent(iScene* scene); // ��Ϊ�����еĸ�ʵ��
	void setParent(iEntity* parent); // ��Ϊĳʵ�����ʵ��

	void render();
	virtual void on_reset();

	void unload();

	D3DXMATRIX* updateWorldMatrix();

	bool fireMouseEnter(iEntity* eOld=NULL);
	bool fireMouseLeave(iEntity* eNew=NULL);
	bool fireClick();
	bool fireDblClick();

	// �����ཻ��Ϣ
	struct IntersectInfo
	{
		BOOL hit;	// �Ƿ����С������ȫ���У�ֵΪ1��������б߽�У�ֵΪ2��������б߽���ֵΪ3
		DWORD face;	// ������
		float u, v, dist;	// ���е�� BARY ���ꣻ���е㵽����ԭ��ľ���
		BOOL isBox; // �� XML �����г�ʼ���������ֶ�
		BOOL isSphere;

		IntersectInfo() { ZeroMemory(this, sizeof(IntersectInfo)); }
	};
	IntersectInfo m_hit;
	void updateIntersectInfo(iEntity*& eDst/*, iEntity* parent=NULL*/);

	// ����ж���������ķ�����Ч
	void setAnim(iAnimInstance* ai);
	void frameMove(float elapsedTime);
	UINT getAnimationSetCount();
	void setAnimationSet(ID3DXAnimationSet* as);
	void setAnimationSet(DWORD index);
	bool findAnimationSet(LPCOLESTR name, ID3DXAnimationSet** ppAnimationSet=NULL);
	void resetTime();

	static void createEntityByNode(HANDLE node, iScene* scene=NULL, iEntity* parent=NULL);

	void enumAllEntities(FINDENTITYPROC proc, LPVOID data, bool meFirst=true);
	void enumAllParents(FINDENTITYPROC proc, LPVOID data, bool meFirst=true);

	iEntity* getCoParent(iEntity* e1, iEntity* e2); // Ѱ������ʵ�����ӽ��Ĺ�����ʵ��

private:
	// �ݹ���Ⱦһ��֡���������е�����������֡���ֵ�֡
	void drawFrame(iXModel::FrameEx* frame=NULL);
	// ��Ⱦһ������
	void drawMeshContainer(iXModel::MeshContainerEx* cont);

	// �ݹ����ñ任����
	static void updateFrameMatrices(iXModel::FrameEx* frame, const D3DXMATRIX* mtParent);

	static BOOL _enumEntity(iEntity* pStart, FINDENTITYPROC proc, LPVOID data, bool meFirst=true);
	static BOOL _enumParent(iEntity* pStart, FINDENTITYPROC proc, LPVOID data, bool meFirst=true);

	bool _fireMouseEnter(iEntity* eStop);
	bool _fireMouseLeave(iEntity* eStop);
};


// scene
class iScene : public Scene
			, public TList<iScene> // ��Ϊ��Դ�������豸��
			, public IExtension
			, public ISinkIsMyEvent
{
	DECLARE_CLASS_NAME2(iScene, Scene)
	//DECLARE_GET_CLASS_NAME(iScene)
	//DECLARE_MODULE_HANDLE()
	DECLARE_NO_DELETE_THIS(iScene)
	DECLARE_CLASS_CAST(iScene, ISinkIsMyEvent)

public:
	iDevice* m_device;
	iSceneTarget m_target;
	iCamera m_camera;	// �����
	iLightGroup m_lightGroup; // ��Դ����
	iEntity* m_entities; // ʵ������б�
	static const DWORD m_defAmbientLight = 0xffffffff; // Ĭ�ϻ����⣬����û���������ã�������Ĭ�ϻ����⣨��ɫ��

	D3DXMATRIX m_world; // ������󣬽����ض������£�����������������
	bool m_mirror; // �Ƿ��о���
	bool m_current_mirror; // ��ǰ�Ƿ��ھ���״̬
	//D3DXPLANE m_mirror_plane; // �����������棬��ԭ��ͷ��ߴ���
	D3DXVECTOR3 m_mirror_orig; // Ĭ�� 0,-1, 0
	D3DXVECTOR3 m_mirror_dir; // Ĭ�� 0, 1, 0

	bool m_rendered;

	bool m_mouse_inside; // ������Ƿ��ڳ�����
	COLOR m_mouse_light; // ������ƹ����ɫ�����ȫ 0 ��ʾ��ʹ�ô˵ƹ�
	POINT m_ptMouse;
	iEntity* m_hover_entity; // ��������ʵ���ϣ����ʵ���ǡ��ȡ�ʵ�塣�п�����һ������ʵ��

	long m_current_child_index; // �����Զ���ȡ��GDI����������ţ�ÿ��ȡһ�ξ�����һ��
public:
	iScene(iDevice* device=NULL);
	~iScene();
	//virtual void Dispose();

	virtual void on_reset();

	void render_scene();
	void render();
	void pre_render();

	D3DXMATRIX get_world_matrix();
	LPCSTR get_technique();

	void update_mirror_matrix();
	void set_current_mirror(bool bMirror);
	bool get_current_mirror();

	float width();
	float height();

	// �����ӿ����꣨����ӿ����Ͻǣ�������������ڵ�ǰ�����е����ߣ�����ֵΪ������㣬pvDirΪ��������߷��򣨿�ѡ��
	D3DXVECTOR3 point_to_ray(POINT pt, D3DXVECTOR3* pvDir=NULL, D3DXMATRIX* pmtWorld=NULL);
	void update_state(); // �������λ�ã����µ�ǰ״̬����������HOVERʵ��

	// ���������������ã�����Ѱ�Ҷ�Ӧ������
	// ����Ӧ�������Լ�����������������������������ٵ����豸����������
	IDirect3DTexture9* find_texture(iMaterial* m, bool bImageFirst=false);

	virtual BOOL IsMyEvent(HANDLE h, DuiEvent* pEvent);

	void unload();
};

#endif // __DUI3DOBJECT_H__