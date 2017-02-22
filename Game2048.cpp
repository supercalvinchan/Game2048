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
	
    //��ʼ������
    for(int i=0;i <4;i++) 
		iMatrix[i].resize(4);//��������Ĵ�С4X4 
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

        //�����ʼ��һ��λ��Ϊ2
        randomInsert();
    }
	showMatrix();  //��ʾ����
}
bool randomInsert(void)
{
    //�ھ����λ�������������2,��λ��Ϊ0��ʾ��
    //�ھ����������λ��Ȼ���ҵ���һ����λ�ò���, û���ҵ���λ����ʧ��
    int xnum=0;
	int ynum=0;
	int point=0; 
    int inum=0;
    bool result = false;
	point=rand()%16;
	xnum=point/4;
	ynum=point%4;
	while((inum<16)&&(iMatrix[xnum][ynum]!=0))  //�ж�iMaxrix[xnum][ynum] �Ƿ��λ
	{											//
		inum++;
		point++;								// 4X4  ÿ�����ӿɿ���һ��16����
		point=point%16;							// point =0,15 ,point=16  point%16=0,xnum=0,ynum=0;  
		xnum=point/4;							// point=25  point%16=9   xnum=point/4=2,ynum=point%4=1
		ynum=point%4;							// 0<==> [0][0]   9<==> [2][1]
	}											
	if(inum<16)									// inum=16 û�п�λ
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
int superposition()   //�ƶ�,����
{
//  �����������ƶ�    2  0  4  2  ==>  2  4  2  0; 0  0  0  2==> 2  0  0  0
//  int iMattmp[4];
	int inum=0;
	int iMatvar=0;
	for(int i=0;i<4;i++)
		iMattmp[i]=iMatmov[i];		//����

	for (int i=0; i<3; i++)			
	{
		if (iMatmov[i] == 0)		//iMatmov[i]��0,��iMatmov[i+1]��iMatmov[3]�е�һ����0������
	    {
			inum=i+1;
		    while((inum<4)&&(iMatmov[inum]==0)) //��iMatmov[i+1]��iMatmov[3]�е�һ����0��
			{
			inum=inum+1;			
			}

			if((inum<4)&&(iMatmov[inum]!=0))	//iMatmov[i]��ǰ����0,�� iMatmov[inum]����
			{
			iMatvar=iMatmov[i];
			iMatmov[i]=iMatmov[inum];
			iMatmov[inum]=iMatvar;
			}
	    }
	}
	//��������ͬ������,ֻ���һ��
	inum=0;
	while((inum<3)&&(iMatmov[inum]!=iMatmov[inum+1]))
	{
	 inum=inum+1;									//iMatmov[inum]!=iMatmov[inum+1],inum<3;   inum++
	}

	if((inum<3)&&(iMatmov[inum]==iMatmov[inum+1]))  //iMatmov[inum]��iMatmov[inum+1]��ͬ,����
		{	
		iMatmov[inum]=iMatmov[inum]+iMatmov[inum+1];
		iMatmov[inum+1]=0;
		}

	//�����������ƶ�    2  0  4  2  ==>  2  4  2  0; 0  0  0  2==> 2  0  0  0
	for (int i=0; i<3; i++)
	{
		if (iMatmov[i] == 0)		//iMatmov[i]��0,��iMatmov[i+1]��iMatmov[3]�е�һ����0������
		{
			inum=i+1;
			while((inum<4)&&(iMatmov[inum]==0))	//��iMatmov[i+1]��iMatmov[3]�е�һ����0��
			{
			inum=inum+1;
			}

			if((inum<4)&&(iMatmov[inum]!=0))	//iMatmov[i]��ǰ����0,�� iMatmov[inum]����
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
		if(iMatmov[i]!=iMattmp[i])				//iMatmov���ƶ�or����
			inum++;								//inum>0,iMatmov���ƶ�or����,inum=0iMatmovû���ƶ�
	}

	return inum;
}
void playGame2048(void)
{
    bool update = true;
    bool moveOk = true;
	bool insert = true;
/******   
    //ȡ�û����밴��
  	cin >> inkey;						//����a s d w
	
    moveOk = TestMatrix();				//�жϾ����Ƿ�ɸ���
	if(moveOk)
	{
		update = reckonMatrix();		//�ƶ�����,update=true OK
		if(update)
			insert=randomInsert();		//�ھ����λ�������������2  insert=true  OK
	}
	else
		update = false;
	if(update)
		showMatrix();					//�������ƶ�,������ʾ
******/
    while(update||moveOk)
        {
		cin >> inkey;				    //����a s d w
        moveOk = TestMatrix();			//�жϾ����Ƿ�ɸ���
		if(moveOk)
			{
			update = reckonMatrix();	//�ƶ�����,update=true OK
			if(update)
				insert=randomInsert();	//�ھ����λ�������������2  insert=true  OK
			}
		else
			update = false;
		if(update)						//�������ƶ�,������ʾ
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
             iMatmov[3] = iMatrix[i][3];			//ÿ�� l,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmovû���ƶ�
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
                iMatflag=iMatflag+superposition();	//ÿ�� d,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmovû���ƶ�
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
                iMatflag=iMatflag+superposition(); //ÿ�� u,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmovû���ƶ�
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
                iMatflag=iMatflag+superposition();	//ÿ�� r,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmovû���ƶ�
                iMatrix[i][3] = iMatmov[0];
                iMatrix[i][2] = iMatmov[1];
                iMatrix[i][1] = iMatmov[2];
                iMatrix[i][0] = iMatmov[3];
            }
			if(iMatflag>0)
                result = true;
       }
    // result=true,�����и���
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
        iMatflag=iMatflag+superposition();		//ÿ�� l,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmov�����ƶ�
        }
       
	for (int i=0; i<4; i++)
        {
        iMatmov[0] = iMatrix[3][i];
        iMatmov[1] = iMatrix[2][i];
        iMatmov[2] = iMatrix[1][i];
        iMatmov[3] = iMatrix[0][i];
        iMatflag=iMatflag+superposition();		//ÿ�� d,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmov�����ƶ�
        }
     
    for (int i=0; i<4; i++)
		{
        iMatmov[0] = iMatrix[0][i];
        iMatmov[1] = iMatrix[1][i];
        iMatmov[2] = iMatrix[2][i];
        iMatmov[3] = iMatrix[3][i];
        iMatflag=iMatflag+superposition();		//ÿ�� u,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmov�����ƶ�
	     }
    
	for (int i=0; i<4; i++)
		{
        iMatmov[0] = iMatrix[i][3];
        iMatmov[1] = iMatrix[i][2];
        iMatmov[2] = iMatrix[i][1];
        iMatmov[3] = iMatrix[i][0];
        iMatflag=iMatflag+superposition();		//ÿ�� r,iMatflag>0 iMatmov���ƶ�or����,iMatflag=0 iMatmov�����ƶ�
        }

	if(iMatflag>0)								//iMatflag>0  ����ɸ���
       result = true;							//result=true ����ɸ���
    return(result);
}

