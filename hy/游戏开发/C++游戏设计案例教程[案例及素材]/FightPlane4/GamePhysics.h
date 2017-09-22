/*********************************
	��Ϸ������ͷ�ļ�GamePhysics.h
*********************************/

#ifndef DEF_GAMEPHYSICS		//�������룬Ŀ���Ƿ�ֹ�ļ����ظ�����

#define DEF_GAMEPHYSICS  1

#include "windows.h"
#include "stdio.h"
#include "math.h"

//������ײ��Ķ�������
typedef		int		BOUNDACTION;
const BOUNDACTION	BA_STOP=0,
					BA_LOOP=1,
					BA_REBOUND=2,
					BA_CLEAR=3;	

//���巽����
typedef int DIRECTION;			
const DIRECTION DI_STOP=0,
				DI_LEFT=1,
				DI_RIGHT=2,
				DI_UP=3,
				DI_DOWN=4;

//����float�͵�ṹPOINTF
typedef struct POINTFtag
{
public:
	float x;
	float y;
	
	//���帳ֵ�������
	const	POINTFtag  & operator   =(const POINTFtag &pt)   
	{   
		x=pt.x;
		y=pt.y;
		return * this ;
	}
	
	//����ӷ��������
	const	POINTFtag  operator	+(const POINTFtag &pt)
	{	
		POINTFtag ptTmp;
		ptTmp.x=x+pt.x;
		ptTmp.y=y+pt.y;
		return ptTmp;
	}

	//������������-
	const 	POINTFtag  operator	-(const POINTFtag &pt)
	{
		POINTFtag ptTmp;
		ptTmp.x=x-pt.x;
		ptTmp.y=y-pt.y;
		return ptTmp;
	}
} POINTF;


/*��Ϸ��������*/

class GamePhysics
{
protected:
	POINTF	m_ptFocus;			//���󽹵����꣬������ڶ������Ͻǵ�ƫ��λ������ʾ
	POINTF	m_ptPos;			//�Զ��󽹵��ȫ����������ʾ�ģ������ڻ����е�λ��
	RECT	m_rObject;			//����Χ	
	RECT	m_rFocusBound;		//���󽹵��˶���Χ
	RECT	m_rBound;			//�����˶���Χ


	POINTF	m_ptVelo;			//�ٶ�ʸ��
	POINTF	m_ptAccelerate;		//���ٶ�
	float	m_fStep;			//�ƶ�ʱ�Ĳ������൱���ٶ�ʸ��m_ptVelo���ٶ�(������)		
	POINTF	m_ptDes;			//�ƶ�ʱ����ЧĿ���

	DIRECTION	m_Direct;		//�˶�����
	
	BOOL	m_bMove;			//�����Ƿ��˶��ı�־

	BOOL	m_bPathArrive;		//�����Ƿ񵽴�·���յ�
	int		m_nPathIndex;		//·�����±�����
	BOOL	m_bInitIndex;		//·�������Ƿ��ʼ��

	BOOL	m_bVisible;			//�����Ƿ�ɼ�
	/*����������ײ��������*/
	BOUNDACTION		m_BoundAction;		//����ײ���˶��߿��Ķ���

	RECT	m_rCheckBox;		//��ײ����

public:
	//���캯��
	GamePhysics();	

	//��ָ���Ķ���ķ�Χ���˶���Χ���������
	GamePhysics(RECT rObject,RECT rBound);

	//��ָ���Ķ���ķ�ΧrObject���˶���ΧrBound������ptFocus���ٶ�ptVelo�����ٶ�ptAccelerate��Ŀ���ptDes���˶�״̬bMove���������
	GamePhysics(RECT rObject,RECT rBound,POINTF ptFocus,POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove);

	//��������
	~GamePhysics();


	/*���ʶ������Է���*/

	//���ö���Χ
	void SetObjectRect(RECT r)
	{
		CopyRect(&m_rObject,&r);
		SetCheckBox(m_rObject);			//������ײ������
	};
	void SetObjectRect(int left,int top,int right,int bottom)
	{
		m_rObject.left=left;
		m_rObject.top=top;
		m_rObject.right=right;
		m_rObject.bottom=bottom;
	};
	//��ȡ����Χ
	RECT GetObjectRect()
	{
		return m_rObject;
	};

	//��ȡ���
	int GetWidth()
	{
		return m_rObject.right-m_rObject.left;
	};


	//��ȡ�߶�	
	int GetHeight()
	{
		return m_rObject.bottom-m_rObject.top;
	};
	
	//���ö��󽹵�λ��(����ڶ������Ͻǵ�ƫ��ֵ)
	void SetFocus(POINTF ptFocus)
	{	
		m_ptFocus=ptFocus;
		
		//ͬʱӦ�ı����Ľ����˶���Χ
		m_rFocusBound.left=(int)m_ptFocus.x+m_rBound.left;	
		m_rFocusBound.top=(int)m_ptFocus.y+m_rBound.top;
		m_rFocusBound.right=m_rBound.right-(GetWidth()-(int)m_ptFocus.x);
		m_rFocusBound.bottom=m_rBound.bottom-(GetHeight()-(int)m_ptFocus.y);
	};
	void SetFocus(float x,float y)
	{	
		POINTF pt={x,y};
		SetFocus(pt);
	};
	//��ȡ���󽹵�λ��
	POINTF GetFocus()
	{
		return m_ptFocus;
	};

	//��ȡ���󽹵���˶���Χ
	RECT GetFocusBound()
	{
		return m_rFocusBound;
	};

	//���á���ȡ���������(�Խ�����ȫ�ֻ����е�λ�ñ�ʾ)
	void SetPos(POINTF ptPos)
	{	
		m_ptPos=ptPos;
	
		POINTF pt=ptPos-m_ptFocus;	//����������Ͻ�����

		int w=m_rObject.right-m_rObject.left;
		int h=m_rObject.bottom-m_rObject.top;

		m_rObject.left=(int)pt.x;
		m_rObject.top=(int)pt.y;
		m_rObject.right=(int)pt.x+w;
		m_rObject.bottom=(int)pt.y+h;
		SetCheckBox(m_rObject);			//������ײ������
	};
	void SetPos(float x,float y)
	{	
		POINTF pt={x,y};
		SetPos(pt);
	};
	//��ȡ���������
	POINTF GetPos()
	{
		return m_ptPos;
	};

	//�ı�������Ͻǵ������
	void SetLeftTop(POINTF pt)
	{
		int nWidth=m_rObject.right-m_rObject.left;
		int nHeight=m_rObject.bottom-m_rObject.top;

		m_rObject.left=(int)pt.x;	//�ı����ķ�Χ����
		m_rObject.top=(int)pt.y;
		m_rObject.right=(int)pt.x+nWidth;
		m_rObject.bottom=(int)pt.y+nHeight;

		SetCheckBox(m_rObject);			//������ײ������
	};
	void SetLeftTop(int x,int y)
	{
		int nWidth=m_rObject.right-m_rObject.left;
		int nHeight=m_rObject.bottom-m_rObject.top;

		m_rObject.left=x;
		m_rObject.top=y;
		m_rObject.right=x+nWidth;
		m_rObject.bottom=y+nHeight;

		SetCheckBox(m_rObject);			//������ײ������

	};		
	//��ȡ�������Ͻǵ������
	POINTF GetLeftTop()
	{
		POINTF pt={(float)m_rObject.left,(float)m_rObject.top};
		return pt;
	};

	//�����˶���Χ
	void SetRectBound(RECT rc)
	{
		CopyRect(&m_rBound,&rc);
	};
	void SetRectBound(int left,int top,int right,int bottom)
	{
		m_rBound.left=left;
		m_rBound.top=top;
		m_rBound.right=right;
		m_rBound.bottom=bottom;
	};
	//��ȡ�˶���Χ
	RECT GetRectBound()
	{
		return m_rBound;
	};
	
	//����Ŀ���pt�������˶�ʱ����ЧĿ���
	void SetDes(POINTF pt)
	{
		if(pt.x<m_rFocusBound.left) 			//������󳬳�
			pt.x=(float)m_rFocusBound.left;
		else if(pt.x>m_rFocusBound.right) 		//������ҳ���
			pt.x=(float)m_rFocusBound.right;

		if(pt.y<m_rFocusBound.top)				//������ϳ���
			pt.y=(float)m_rFocusBound.top;
		else if(pt.y>m_rFocusBound.bottom) 		//������³���
			pt.y=(float)m_rFocusBound.bottom;

		m_ptDes=pt;				//������ЧĿ���
		m_bPathArrive=FALSE;	//���õ���·���յ�״̬ΪFALSE
	};
	void SetDes(float x,float y)
	{
		POINTF pt={x,y};
		SetDes(pt);

	};
	//��ȡ��ЧĿ���
	POINTF GetDes()
	{
		return m_ptDes;
	};

	//��ȡ�����Ƿ񵽴�Ŀ����״̬
	BOOL GetPathArrive()
	{
		return m_bPathArrive;
	}

	//�����ٶȣ��ٶȸı�����˶������뷽��Ҳ��֮�ı�
	void SetVelo(POINTF ptVelo)
	{
		m_ptVelo=ptVelo;	//�����ٶ�
		m_fStep=(float)hypot(ptVelo.x,ptVelo.y);	//�����˶��Ĳ���
		
		//�����˶�����
		if(fabs(m_ptVelo.x)<0.001 && fabs(m_ptVelo.y)<0.001)
			m_Direct=DI_STOP;
		else if((m_ptVelo.x+m_ptVelo.y)>0)
		{
			if(m_ptVelo.x>=m_ptVelo.y)
				m_Direct=DI_RIGHT;
			else
				m_Direct=DI_DOWN;
		}
		else
		{
			if(m_ptVelo.x>m_ptVelo.y)
				m_Direct=DI_UP;
			else
				m_Direct=DI_LEFT;
		}
	};
	void SetVelo(float x,float y)
	{
		POINTF pt={x,y};
		SetVelo(pt);
	};
	//��ȡ�ٶ�
	POINTF GetVelo()
	{
		return m_ptVelo;
	};

	//��ȡ�˶�����
	DIRECTION GetDirect()
	{
		return m_Direct;
	};

	//���ü��ٶ�
	void SetAccelerate(POINTF ptAccelerate)
	{
		m_ptAccelerate=ptAccelerate;
	};
	void SetAccelerate(float x,float y)
	{
		m_ptAccelerate.x=x;
		m_ptAccelerate.y=y;
	};

	//���ö����˶�״̬
	void SetMoveState(BOOL bMove)
	{
		m_bMove=bMove;
	};
	//��ȡ�����˶�״̬	
	BOOL GetMoveState()
	{
		return m_bMove;
	};

	//  ���á���ȡ�����Ƿ�ɼ�
	void SetVisible(BOOL bVisible)
	{
		m_bVisible=bVisible;
	};

	BOOL GetVisible()
	{
		return m_bVisible;
	};
	
	/*���淽��*/

	//��ָ���Ķ���ΧrObject���˶���ΧrBound�����ö������
	void SetObject(RECT rObject,RECT rBound);

	// ��ָ���Ķ���ķ�ΧrObject���˶���ΧrBound������ptFocus���ٶ�ptVelo�����ٶ�ptAccelerate��Ŀ���ptDes���˶�״̬bMove�����ö������
	void SetObject(RECT rObject,RECT rBound,POINTF ptFocus,POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove);

	//�����˶�
	void	UniformMove();

	//���ٶ��˶�
	void	ShiftMove();
	
	//�ƶ���Ŀ���
	void	MoveToDes();

	//��ָ��·���ƶ�
	void	MoveAlongPath(POINTF * ptDesPath,int nPtCount,BOOL bCycle=FALSE);

	//����Direction�ƶ�
	void	MoveDirect(DIRECTION Direct);

	// �жϵ�pt�Ƿ��ھ��η�Χr��
	BOOL  IsPointInBound(POINTF pt,RECT r);

	BOOL CheckErr(BOOL bRectify);


	/*����������ײ������ط���*/


	//������ײ������
	void SetCheckBox(RECT rObject)
	{
		int w=(int)((rObject.right-rObject.left)*0.1);
		int h=(int)((rObject.bottom-rObject.top)*0.1);

		m_rCheckBox.left=rObject.left+w;
		m_rCheckBox.right=rObject.right-w;
		m_rCheckBox.top=rObject.top+h;
		m_rCheckBox.bottom=rObject.bottom-h;
	}

	//��ȡ��ײ������
	RECT GetCheckBox()
	{
		return m_rCheckBox;
	}

	// ���ٶ�m_ptVelo���о���ֱ���ƶ�,���Ա߿���ײ���м��,��������ײʱ,��actionָ���ķ�ʽ����
	void	UniformMove2(BOUNDACTION action);

	// ��ǰ���尴�����ٶȽ���ֱ���ƶ�,��һ����phҲ��������ٶȽ���ֱ���˶�,�������������ײ���м��,��������ײʱ,��actionָ���ķ�ʽ����
	BOOL	Collision(GamePhysics  * ph, BOUNDACTION action,RECT * rCollision);

};

#endif