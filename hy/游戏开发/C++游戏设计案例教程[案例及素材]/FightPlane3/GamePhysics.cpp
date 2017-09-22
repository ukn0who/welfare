/*********************************
游戏物理运动程序文件GamePhysics.cpp
*********************************/

#include "GamePhysics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*构造函数*/
GamePhysics::GamePhysics()
{
	RECT rObject={0,0,0,0};
	RECT rBound={0,0,0,0};
	SetObject(rObject,rBound);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 按指定的对象的范围和运动范围来构造对象*/
GamePhysics::GamePhysics(RECT rObject,RECT rBound)
{
	SetObject(rObject,rBound);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 按指定的对象的范围、运动范围rBound、焦点、速度ptVelo、加速度ptAccelerate、目标点ptDes和运动状态bMove来构造对象*/
GamePhysics::GamePhysics(RECT rObject,RECT rBound,POINTF ptFocus,
						POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove)
{
	SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,bMove);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*析构函数*/
GamePhysics::~GamePhysics()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 按指定的对象范围rObject和运动范围rBound来设置对象参数*/
void GamePhysics::SetObject(RECT rObject,RECT rBound)
{
	POINTF ptPos={(float)rObject.left,(float)rObject.top};	//设置位置坐标为对象范围左上角坐标
	POINTF ptFocus={0,0};		//设置焦点为左上角
	POINTF ptVelo={0,0};		//速度为0
	POINTF ptAccelerate={0,0};	//加速度为0
	POINTF ptDes=ptPos;			//有效目标点为对象范围左上角坐标
	SetObject(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);
	m_bPathArrive=TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 按指定的对象的范围rObject、运动范围rBound、焦点ptFocus、速度ptVelo、加速度ptAccelerate、目标点ptDes和运动状态bMove来设置对象参数 */
void GamePhysics::SetObject(RECT rObject,RECT rBound,POINTF ptFocus,
						POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove)
{
	
	
	SetObjectRect(rObject);;	//设置对象范围

	SetRectBound(rBound);	//设置对象运动范围

	SetFocus(ptFocus);		//设置焦点
	SetPos((float)rObject.left,(float)rObject.top);			//设置对象位置

	m_bMove=bMove;			//设置对象运动状态
	m_bInitIndex=FALSE;

	//设置对象运动的目标点
	SetDes(ptDes);

	//设置对象运动的速度矢量
	SetVelo(ptVelo);

	//设置对象运动的加速度
	SetAccelerate(ptAccelerate);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 判断点pt是否在矩形范围r内 */
BOOL  GamePhysics::IsPointInBound(POINTF pt,RECT r)
{
	if(pt.x>=r.left && pt.x<=r.right
		&& pt.y>=r.top && pt.y<=r.bottom)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 均速运动*/
void GamePhysics::UniformMove()
{
	POINTF ptAccelerate={0,0};	

	SetAccelerate(ptAccelerate);//设置加速度为0

	ShiftMove();	//调用ShiftMove方法进行运动
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 加速度运动 */
void	GamePhysics::ShiftMove()
{
	if(! GetMoveState())	//检查运动状态
		return ;

	//计算移动后的位置
	POINTF pt;
	pt=m_ptPos+m_ptVelo;

	//检查移动后的位置是否在焦点运动框内,如果不在焦点运动框内,
	//则通过调用MoveTo()方法移动到最接近的位置,
	//并停止运动,即设置运动状态为FALSE,设置速度ptVelo和加速度ptAccelerate为0
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
		//如果移动后的位置在焦点运动框内,则移动到该位置
		SetPos(pt);

		//改变初速度为加速后的速度，在下次调用时将使用加速后的速度为初速度
		POINTF ptv=m_ptVelo;
		ptv=ptv+m_ptAccelerate;
		SetVelo(ptv);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 移动到目标点，到达后设置运动状态为假*/
void	GamePhysics::MoveToDes()
{
	if(! GetMoveState())	//检查运动状态
		return ;

	//计算起点和终点两点间的水平和垂直距离
	float sx=m_ptDes.x-m_ptPos.x;
	float sy=m_ptDes.y-m_ptPos.y;

	//判断物体离目标的直线距离是否大于一次移动的步长，如果小于步长，则直接设置物体到有效目标点
	if(hypot(sx,sy)<m_fStep)	
	{
		SetPos(m_ptDes);			//直接设置对象到目标点
		SetMoveState(FALSE);		//设置运动状态
		return ;
	}

	//计算物体移动到有效目标点时，移动一次步长所需要经过的水平和垂直距离
	float x=(float)(m_fStep*sx/sqrt(sx*sx+sy*sy));
	float y=(float)(m_fStep*sy/sqrt(sx*sx+sy*sy));

	//修改速度矢量
	POINTF pt={x,y};
	SetVelo(pt);		//设置pt为新的速度矢量

	//设置物体到下一步要移动到的位置
	POINTF pt1={m_ptPos.x+x,m_ptPos.y+y};		//计算物体移动后的位置
	SetPos(pt1);		//设置物体位置
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 沿指定路径ptDesPath移动,nPtCount为路径点总数,bCycle指定是否循环*/
void	GamePhysics::MoveAlongPath(POINTF * ptDesPath,int nPtCount,BOOL bCycle)
{
	if(!m_bInitIndex)
	{		
		m_nPathIndex=0;			//初始化路径点索引值
		m_bInitIndex=TRUE;
	}
	//判断是否完成全部路径点
	if(m_nPathIndex <nPtCount)
	{
		SetMoveState(TRUE);			//设置物体运动状态
		SetDes(ptDesPath[m_nPathIndex]);
		MoveToDes();			//调用MoveToDes()移动到ptDes[m_nPathIndex]指定的路径点
		if(!GetMoveState())		//如果已到达路径点，此时MoveToDes()中设置运动状态为FALSE
			m_nPathIndex++;		//路径点索引值递增	
		return;
	}
	else
	{
		m_bInitIndex=FALSE;
		if(bCycle)			//是否循环
		{
			m_bPathArrive=FALSE;		

		}
		else
			m_bPathArrive=TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 向Direction方向移动, */
void	GamePhysics::MoveDirect(DIRECTION Direct)
{
	POINTF ptDes;
	//判断移动的方向，并计算下一步的位置
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

	SetPos(ptDes);		//设置对象到下一步的位置
};


/*检查对象是否已超出焦点框，如果未超出，返回FALSE;
如果超出，则返回TRUE，如果bRectify为TRUE，将把对象位置设置到最近的焦点框边缘*/
BOOL GamePhysics::CheckErr(BOOL bRectify)
{	
	//判断是否超出焦点框
	if(IsPointInBound(m_ptPos,m_rFocusBound))
		return FALSE;
	//判断是否需要修正位置
	if(bRectify)
	{
		//计算距焦点框的最近位置
		POINTF pt=m_ptPos;
	
		if(m_rFocusBound.left>m_ptPos.x)
			pt.x=(float)m_rFocusBound.left;
		else if(m_rFocusBound.right<m_ptPos.x)
			pt.x=(float)m_rFocusBound.right;

		if(m_rFocusBound.top>m_ptPos.y)
			pt.y=(float)m_rFocusBound.top;
		else if(m_rFocusBound.bottom<m_ptPos.y)
			pt.y=(float)m_rFocusBound.bottom;

		SetPos(pt);			//设置到修正后的位置
		SetMoveState(FALSE);
	}
	return TRUE;
}