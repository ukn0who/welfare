/*********************************
��Ϸ�����˶������ļ�GamePhysics.cpp
*********************************/

#include "GamePhysics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���캯��*/
GamePhysics::GamePhysics()
{
	RECT rObject={0,0,0,0};
	RECT rBound={0,0,0,0};
	SetObject(rObject,rBound);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* ��ָ���Ķ���ķ�Χ���˶���Χ���������*/
GamePhysics::GamePhysics(RECT rObject,RECT rBound)
{
	SetObject(rObject,rBound);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ���Ķ���ķ�Χ���˶���ΧrBound�����㡢�ٶ�ptVelo�����ٶ�ptAccelerate��Ŀ���ptDes���˶�״̬bMove���������*/
GamePhysics::GamePhysics(RECT rObject,RECT rBound,POINTF ptFocus,
						POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove)
{
	SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,bMove);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*��������*/
GamePhysics::~GamePhysics()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ���Ķ���ΧrObject���˶���ΧrBound�����ö������*/
void GamePhysics::SetObject(RECT rObject,RECT rBound)
{
	POINTF ptPos={(float)rObject.left,(float)rObject.top};	//����λ������Ϊ����Χ���Ͻ�����
	POINTF ptFocus={0,0};		//���ý���Ϊ���Ͻ�
	POINTF ptVelo={0,0};		//�ٶ�Ϊ0
	POINTF ptAccelerate={0,0};	//���ٶ�Ϊ0
	POINTF ptDes=ptPos;			//��ЧĿ���Ϊ����Χ���Ͻ�����
	SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);
	m_bPathArrive=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ���Ķ���ķ�ΧrObject���˶���ΧrBound������ptFocus���ٶ�ptVelo�����ٶ�ptAccelerate��Ŀ���ptDes���˶�״̬bMove�����ö������ */
void GamePhysics::SetObject(RECT rObject,RECT rBound,POINTF ptFocus,
						POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove)
{
	
	
	SetObjectRect(rObject);;	//���ö���Χ

	SetRectBound(rBound);	//���ö����˶���Χ

	SetFocus(ptFocus);		//���ý���
	SetPos((float)rObject.left,(float)rObject.top);			//���ö���λ��

	m_bMove=bMove;			//���ö����˶�״̬
	m_bInitIndex=FALSE;

	//���ö����˶���Ŀ���
	SetDes(ptDes);

	//���ö����˶����ٶ�ʸ��
	SetVelo(ptVelo);

	//���ö����˶��ļ��ٶ�
	SetAccelerate(ptAccelerate);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �жϵ�pt�Ƿ��ھ��η�Χr�� */
BOOL  GamePhysics::IsPointInBound(POINTF pt,RECT r)
{
	if(pt.x>=r.left && pt.x<=r.right
		&& pt.y>=r.top && pt.y<=r.bottom)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �����˶�*/
void GamePhysics::UniformMove()
{
	POINTF ptAccelerate={0,0};	

	SetAccelerate(ptAccelerate);//���ü��ٶ�Ϊ0

	ShiftMove();	//����ShiftMove���������˶�
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ���ٶ��˶� */
void	GamePhysics::ShiftMove()
{
	if(! GetMoveState())	//����˶�״̬
		return ;

	//�����ƶ����λ��
	POINTF pt;
	pt=m_ptPos+m_ptVelo;

	//����ƶ����λ���Ƿ��ڽ����˶�����,������ڽ����˶�����,
	//��ͨ������MoveTo()�����ƶ�����ӽ���λ��,
	//��ֹͣ�˶�,�������˶�״̬ΪFALSE,�����ٶ�ptVelo�ͼ��ٶ�ptAccelerateΪ0
	if(!IsPointInBound(pt,m_rFocusBound))	
	{
		MoveToDes();
		SetMoveState(FALSE);
		m_ptVelo.x=0;
		m_ptVelo.y=0;
		m_ptAccelerate.x=0;
		m_ptAccelerate.y=0;
	}
	else
	{
		//����ƶ����λ���ڽ����˶�����,���ƶ�����λ��
		SetPos(pt);

		//�ı���ٶ�Ϊ���ٺ���ٶȣ����´ε���ʱ��ʹ�ü��ٺ���ٶ�Ϊ���ٶ�
		POINTF ptv=m_ptVelo;
		ptv=ptv+m_ptAccelerate;
		SetVelo(ptv);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �ƶ���Ŀ��㣬����������˶�״̬Ϊ��*/
void	GamePhysics::MoveToDes()
{
	if(! GetMoveState())	//����˶�״̬
		return ;

	//���������յ�������ˮƽ�ʹ�ֱ����
	float sx=m_ptDes.x-m_ptPos.x;
	float sy=m_ptDes.y-m_ptPos.y;

	//�ж�������Ŀ���ֱ�߾����Ƿ����һ���ƶ��Ĳ��������С�ڲ�������ֱ���������嵽��ЧĿ���
	if(hypot(sx,sy)<m_fStep)	
	{
		SetPos(m_ptDes);			//ֱ�����ö���Ŀ���
		SetMoveState(FALSE);		//�����˶�״̬
		return ;
	}

	//���������ƶ�����ЧĿ���ʱ���ƶ�һ�β�������Ҫ������ˮƽ�ʹ�ֱ����
	float x=(float)(m_fStep*sx/sqrt(sx*sx+sy*sy));
	float y=(float)(m_fStep*sy/sqrt(sx*sx+sy*sy));

	//�޸��ٶ�ʸ��
	POINTF pt={x,y};
	SetVelo(pt);		//����ptΪ�µ��ٶ�ʸ��

	//�������嵽��һ��Ҫ�ƶ�����λ��
	POINTF pt1={m_ptPos.x+x,m_ptPos.y+y};		//���������ƶ����λ��
	SetPos(pt1);		//��������λ��
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ָ��·��ptDesPath�ƶ�,nPtCountΪ·��������,bCycleָ���Ƿ�ѭ��*/
void	GamePhysics::MoveAlongPath(POINTF * ptDesPath,int nPtCount,BOOL bCycle)
{
	if(!m_bInitIndex)
	{		
		m_nPathIndex=0;			//��ʼ��·��������ֵ
		m_bInitIndex=TRUE;
	}
	//�ж��Ƿ����ȫ��·����
	if(m_nPathIndex <nPtCount)
	{
		SetMoveState(TRUE);			//���������˶�״̬
		SetDes(ptDesPath[m_nPathIndex]);
		MoveToDes();			//����MoveToDes()�ƶ���ptDes[m_nPathIndex]ָ����·����
		if(!GetMoveState())		//����ѵ���·���㣬��ʱMoveToDes()�������˶�״̬ΪFALSE
			m_nPathIndex++;		//·��������ֵ����	
		return;
	}
	else
	{
		m_bInitIndex=FALSE;
		if(bCycle)			//�Ƿ�ѭ��
		{
			m_bPathArrive=FALSE;		

		}
		else
			m_bPathArrive=TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Direction�����ƶ�, */
void	GamePhysics::MoveDirect(DIRECTION Direct)
{
	POINTF ptDes;
	//�ж��ƶ��ķ��򣬲�������һ����λ��
	switch(Direct)
	{
		case DI_LEFT:
			ptDes.x=m_ptPos.x-m_fStep;
			ptDes.y=m_ptPos.y;
			break;
		case DI_RIGHT:
			ptDes.x=m_ptPos.x+m_fStep;
			ptDes.y=m_ptPos.y;
			break;
		case DI_UP:
			ptDes.x=m_ptPos.x;
			ptDes.y=m_ptPos.y-m_fStep;
			break;
		case DI_DOWN:
			ptDes.x=m_ptPos.x;
			ptDes.y=m_ptPos.y+m_fStep;
			break;	
		default:
			ptDes=m_ptPos;
			break;
	}

	SetPos(ptDes);		//���ö�����һ����λ��
};


/*�������Ƿ��ѳ�����������δ����������FALSE;
����������򷵻�TRUE�����bRectifyΪTRUE�����Ѷ���λ�����õ�����Ľ�����Ե*/
BOOL GamePhysics::CheckErr(BOOL bRectify)
{	
	//�ж��Ƿ񳬳������
	if(IsPointInBound(m_ptPos,m_rFocusBound))
		return FALSE;
	//�ж��Ƿ���Ҫ����λ��
	if(bRectify)
	{
		//����ཹ�������λ��
		POINTF pt=m_ptPos;
	
		if(m_rFocusBound.left>m_ptPos.x)
			pt.x=(float)m_rFocusBound.left;
		else if(m_rFocusBound.right<m_ptPos.x)
			pt.x=(float)m_rFocusBound.right;

		if(m_rFocusBound.top>m_ptPos.y)
			pt.y=(float)m_rFocusBound.top;
		else if(m_rFocusBound.bottom<m_ptPos.y)
			pt.y=(float)m_rFocusBound.bottom;

		SetPos(pt);			//���õ��������λ��
		SetMoveState(FALSE);
	}
	return TRUE;
}