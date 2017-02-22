//#include "stdafx.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
  
        void initGame2048(void);
          
//      int  iMatrix[4][4];
//		int  iMatmov[4];
		vector <vector <int>> iMatrix(4);
		vector <int> iMatmov(4);
		vector <int> iMattmp(4);


		string inkey=" ";
        int  iMax;
		string sfilename="                                          ";
   
        void initMatrix(void);
        bool reckonMatrix(void);
		bool TestMatrix(void);
        int  superposition(void);
        void showMatrix(void);
        bool randomInsert(void);
		void playGame2048(void);

int  main()
{
	initGame2048();
	playGame2048();
}

void initGame2048()
{
    iMax = 0;
	
    //初始化矩阵
    for(int i=0;i <4;i++) 
		iMatrix[i].resize(4);//设置数组的大小4X4 
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            iMatrix[i][j] = 0;
        }
    }

	cout << "Enter initial configuration file name:";
    fstream _file;
    cin >> sfilename;
    _file.open(sfilename);
    if(_file)
    {
        for (int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                _file >> iMatrix[i][j];
            }
        }
        _file.close();
    }
    else
    {
        cout << "File not found, using default start configuration\r\n";

        //随机初始化一个位置为2
        randomInsert();
    }
	showMatrix();  //显示矩阵
}
bool randomInsert(void)
{
    //在矩阵空位中随机插入数字2,该位置为0表示空
    //在矩阵中随机定位，然后找到第一个空位置插入, 没有找到空位，则失败
    int xnum=0;
	int ynum=0;
	int point=0; 
    int inum=0;
    bool result = false;
	point=rand()%16;
	xnum=point/4;
	ynum=point%4;
	while((inum<16)&&(iMatrix[xnum][ynum]!=0))  //判断iMaxrix[xnum][ynum] 是否空位
	{											//
		inum++;
		point++;								// 4X4  每行连接可看成一排16个数
		point=point%16;							// point =0,15 ,point=16  point%16=0,xnum=0,ynum=0;  
		xnum=point/4;							// point=25  point%16=9   xnum=point/4=2,ynum=point%4=1
		ynum=point%4;							// 0<==> [0][0]   9<==> [2][1]
	}											
	if(inum<16)									// inum=16 没有空位
	{
	    iMatrix[xnum][ynum]=2;
		result = true;
	}
	return(result);
}
void showMatrix(void)
{
    for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(iMax<iMatrix[i][j])
				iMax=iMatrix[i][j];
		}
	}

    for(int i=0; i<4; i++)
    {
		 //printf("%-2d  %-2d  %-2d  %-2d\r\n", iMatrix[i][0], iMatrix[i][1], iMatrix[i][2], iMatrix[i][3]);
		 cout << "\t" << iMatrix[i][0] << "\t"<< iMatrix[i][1] << "\t"<< iMatrix[i][2] << "\t" << iMatrix[i][3] << endl;
    }
	//printf("pls key: a=left, s=down, w=up, d=right \r\n\r\n");
    cout <<"pls key: a=left, s=down, w=up, d=right" <<endl ;
}
int superposition()   //移动,叠加
{
//  非零数向左移动    2  0  4  2  ==>  2  4  2  0; 0  0  0  2==> 2  0  0  0
//  int iMattmp[4];
	int inum=0;
	int iMatvar=0;
	for(int i=0;i<4;i++)
		iMattmp[i]=iMatmov[i];		//备份

	for (int i=0; i<3; i++)			
	{
		if (iMatmov[i] == 0)		//iMatmov[i]是0,和iMatmov[i+1]到iMatmov[3]中第一个非0数交换
	    {
			inum=i+1;
		    while((inum<4)&&(iMatmov[inum]==0)) //找iMatmov[i+1]到iMatmov[3]中第一个非0数
			{
			inum=inum+1;			
			}

			if((inum<4)&&(iMatmov[inum]!=0))	//iMatmov[i]当前数是0,和 iMatmov[inum]交换
			{
			iMatvar=iMatmov[i];
			iMatmov[i]=iMatmov[inum];
			iMatmov[inum]=iMatvar;
			}
	    }
	}
	//相邻两相同数叠加,只相加一次
	inum=0;
	while((inum<3)&&(iMatmov[inum]!=iMatmov[inum+1]))
	{
	 inum=inum+1;									//iMatmov[inum]!=iMatmov[inum+1],inum<3;   inum++
	}

	if((inum<3)&&(iMatmov[inum]==iMatmov[inum+1]))  //iMatmov[inum]和iMatmov[inum+1]相同,叠加
		{	
		iMatmov[inum]=iMatmov[inum]+iMatmov[inum+1];
		iMatmov[inum+1]=0;
		}

	//非零数向左移动    2  0  4  2  ==>  2  4  2  0; 0  0  0  2==> 2  0  0  0
	for (int i=0; i<3; i++)
	{
		if (iMatmov[i] == 0)		//iMatmov[i]是0,和iMatmov[i+1]到iMatmov[3]中第一个非0数交换
		{
			inum=i+1;
			while((inum<4)&&(iMatmov[inum]==0))	//找iMatmov[i+1]到iMatmov[3]中第一个非0数
			{
			inum=inum+1;
			}

			if((inum<4)&&(iMatmov[inum]!=0))	//iMatmov[i]当前数是0,和 iMatmov[inum]交换
			{
			iMatvar=iMatmov[i];
			iMatmov[i]=iMatmov[inum];
			iMatmov[inum]=iMatvar;
			}
	    }
	}

	inum=0;
	for(int i=0;i<4;i++)
	{
		if(iMatmov[i]!=iMattmp[i])				//iMatmov有移动or叠加
			inum++;								//inum>0,iMatmov有移动or叠加,inum=0iMatmov没有移动
	}

	return inum;
}
void playGame2048(void)
{
    bool update = true;
    bool moveOk = true;
	bool insert = true;
/******   
    //取用户输入按键
  	cin >> inkey;						//输入a s d w
	
    moveOk = TestMatrix();				//判断矩阵是否可更新
	if(moveOk)
	{
		update = reckonMatrix();		//移动矩阵,update=true OK
		if(update)
			insert=randomInsert();		//在矩阵空位中随机插入数字2  insert=true  OK
	}
	else
		update = false;
	if(update)
		showMatrix();					//矩阵有移动,从新显示
******/
    while(update||moveOk)
        {
		cin >> inkey;				    //输入a s d w
        moveOk = TestMatrix();			//判断矩阵是否可更新
		if(moveOk)
			{
			update = reckonMatrix();	//移动矩阵,update=true OK
			if(update)
				insert=randomInsert();	//在矩阵空位中随机插入数字2  insert=true  OK
			}
		else
			update = false;
		if(update)						//矩阵有移动,从新显示
			showMatrix();
        }

	if(iMax==2048)
		cout << "Max nunber is:"<< iMax << "\t"<<"You win";
	else
		cout << "Max number is:"<< iMax << "\t"<<"Game is over ";
}


bool reckonMatrix(void)
{
    int iMatflag=0;
    bool result = false;
	if(inkey=="a")
		{
        for (int i=0; i<4; i++)
            {
             iMatmov[0] = iMatrix[i][0];
             iMatmov[1] = iMatrix[i][1];
             iMatmov[2] = iMatrix[i][2];
             iMatmov[3] = iMatrix[i][3];			//每行 l,iMatflag>0 iMatmov有移动or叠加,iMatflag=0 iMatmov没有移动
             iMatflag=iMatflag+superposition();
             iMatrix[i][0] = iMatmov[0];
             iMatrix[i][1] = iMatmov[1];
             iMatrix[i][2] = iMatmov[2];
             iMatrix[i][3] = iMatmov[3];    
            }
            if(iMatflag>0)
				result = true;
        }
	else
		if(inkey=="s")
         {
            for (int i=0; i<4; i++)
            {
                iMatmov[0] = iMatrix[3][i];
                iMatmov[1] = iMatrix[2][i];
                iMatmov[2] = iMatrix[1][i];
                iMatmov[3] = iMatrix[0][i];
                iMatflag=iMatflag+superposition();	//每列 d,iMatflag>0 iMatmov有移动or叠加,iMatflag=0 iMatmov没有移动
                iMatrix[3][i] = iMatmov[0];
                iMatrix[2][i] = iMatmov[1];
                iMatrix[1][i] = iMatmov[2];
                iMatrix[0][i] = iMatmov[3];
            }
			if(iMatflag>0)
				result = true;
            
        }
        else 
		if(inkey=="w")
        {
            for (int i=0; i<4; i++)
            {
                iMatmov[0] = iMatrix[0][i];
                iMatmov[1] = iMatrix[1][i];
                iMatmov[2] = iMatrix[2][i];
                iMatmov[3] = iMatrix[3][i];
                iMatflag=iMatflag+superposition(); //每列 u,iMatflag>0 iMatmov有移动or叠加,iMatflag=0 iMatmov没有移动
                iMatrix[0][i] = iMatmov[0];
                iMatrix[1][i] = iMatmov[1];
                iMatrix[2][i] = iMatmov[2];
                iMatrix[3][i] = iMatmov[3];
            }
            if(iMatflag>0)
			result = true;
            
        }
		else
        if(inkey=="d")
        {
            for (int i=0; i<4; i++)
            {
                iMatmov[0] = iMatrix[i][3];
                iMatmov[1] = iMatrix[i][2];
                iMatmov[2] = iMatrix[i][1];
                iMatmov[3] = iMatrix[i][0];
                iMatflag=iMatflag+superposition();	//每行 r,iMatflag>0 iMatmov有移动or叠加,iMatflag=0 iMatmov没有移动
                iMatrix[i][3] = iMatmov[0];
                iMatrix[i][2] = iMatmov[1];
                iMatrix[i][1] = iMatmov[2];
                iMatrix[i][0] = iMatmov[3];
            }
			if(iMatflag>0)
                result = true;
       }
    // result=true,矩阵有更新
    return(result);
}

bool TestMatrix(void)
{
    int iMatflag=0;
    bool result = false;
	for (int i=0; i<4; i++)
        {
        iMatmov[0] = iMatrix[i][0];
        iMatmov[1] = iMatrix[i][1];
        iMatmov[2] = iMatrix[i][2];
        iMatmov[3] = iMatrix[i][3];
        iMatflag=iMatflag+superposition();		//每行 l,iMatflag>0 iMatmov可移动or叠加,iMatflag=0 iMatmov不能移动
        }
       
	for (int i=0; i<4; i++)
        {
        iMatmov[0] = iMatrix[3][i];
        iMatmov[1] = iMatrix[2][i];
        iMatmov[2] = iMatrix[1][i];
        iMatmov[3] = iMatrix[0][i];
        iMatflag=iMatflag+superposition();		//每列 d,iMatflag>0 iMatmov可移动or叠加,iMatflag=0 iMatmov不能移动
        }
     
    for (int i=0; i<4; i++)
		{
        iMatmov[0] = iMatrix[0][i];
        iMatmov[1] = iMatrix[1][i];
        iMatmov[2] = iMatrix[2][i];
        iMatmov[3] = iMatrix[3][i];
        iMatflag=iMatflag+superposition();		//每列 u,iMatflag>0 iMatmov可移动or叠加,iMatflag=0 iMatmov不能移动
	     }
    
	for (int i=0; i<4; i++)
		{
        iMatmov[0] = iMatrix[i][3];
        iMatmov[1] = iMatrix[i][2];
        iMatmov[2] = iMatrix[i][1];
        iMatmov[3] = iMatrix[i][0];
        iMatflag=iMatflag+superposition();		//每行 r,iMatflag>0 iMatmov可移动or叠加,iMatflag=0 iMatmov不能移动
        }

	if(iMatflag>0)								//iMatflag>0  矩阵可更新
       result = true;							//result=true 矩阵可更新
    return(result);
}

