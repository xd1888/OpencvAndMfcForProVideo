
// PlayVideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlayVideo.h"
#include "PlayVideoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlayVideoDlg 对话框




CPlayVideoDlg::CPlayVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayVideoDlg::IDD, pParent)
	, TheImage(NULL)
	, vPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayVideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CPlayVideoDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_ShowImg, &CPlayVideoDlg::OnStnClickedShowimg)
	ON_BN_CLICKED(IDC_ReadImg_Button, &CPlayVideoDlg::OnBnClickedReadimgButton)
	ON_BN_CLICKED(IDC_EdgeDetect_Button, &CPlayVideoDlg::OnBnClickedEdgedetectButton)
	ON_BN_CLICKED(IDC_ReadVideo_Button, &CPlayVideoDlg::OnBnClickedReadvideoButton)
	ON_BN_CLICKED(IDC_Play_Button, &CPlayVideoDlg::OnBnClickedPlayButton)
END_MESSAGE_MAP()


// CPlayVideoDlg 消息处理程序

BOOL CPlayVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CvSize ImgSize;
	ImgSize.height=IMAGE_HEIGHT;
	ImgSize.width=IMAGE_WIDTH;
	TheImage=cvCreateImage(ImgSize,IPL_DEPTH_8U,3);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlayVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlayVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDialog::OnPaint();//重绘对话框
		CDialog::UpdateWindow();//跟新窗口，没这部调用，图盘显示出问题
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlayVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPlayVideoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPlayVideoDlg::OnStnClickedShowimg()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPlayVideoDlg::OnBnClickedReadimgButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(
		TRUE,_T("*.bmp"),NULL,
		OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("image files(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"),
		NULL
		);//选定图片约定
	dlg.m_ofn.lpstrTitle=_T("Open Image");
	if (dlg.DoModal()!=IDOK) {MessageBox(_T("no picture"));}
	CString mPath=dlg.GetPathName();
	IplImage* ipl=cvLoadImage(mPath,1);
	if (!ipl) return;

	if(TheImage) cvZero(TheImage);

	ResizeImage(ipl);
	ShowImage(TheImage,IDC_ShowImg);
	cvReleaseImage(&ipl);;
}


void CPlayVideoDlg::ShowImage(IplImage* img,UINT ID)
{
	CDC* pDC=GetDlgItem(ID)->GetDC();//获得现实控件的DC
	HDC hDC=pDC->GetSafeHdc();//获取HDC（设备句柄）来进行绘图操作
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw=rect.right-rect.left;
	int rh=rect.bottom-rect.top;
	int iw=img->width;
	int ih=img->height;
	int tx=(int)(rw-iw)/2;//是图片显示位置正好在控件的正中
	int ty=(int)(rh-ih)/2;

	SetRect(rect,tx,ty,tx+iw,ty+ih);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC,&rect);

	ReleaseDC(pDC);
	

}


void CPlayVideoDlg::ResizeImage(IplImage* img)
{
	//读取图片的宽和高
	int w=img->width;
	int h=img->height;
	//找出宽和高的较大者
	int max=(w>h)?w:h;
	//计算将图片缩放到TheImage 区域所需的比例因子
	float scale=(float)((float)max/256.0f);
	//缩放将图片缩放到TheImage区域所需要的比例因子
	int nw=(int)(w/scale);
	int nh=(int)(h/scale);

	//为了将缩放后的图片存入TheImage正中部位，需要计算图片在THeImage左上角
	//期望坐标值
	int tlx=(nw>nh)?0:(int)(256-nw)/2;
	int tly=(nw>nh)?(int)(256-nh)/2:0;
	//设置TheImage的ROI区域，用来存入图片img
	cvSetImageROI(TheImage,cvRect(tlx,tly,nw,nh) );
	//对图片img进行缩放，并存入TheImage中
	cvResize(img,TheImage);

	//重置TheImage的ROI准备读入下一幅图片
	cvResetImageROI(TheImage);
}


void CPlayVideoDlg::OnBnClickedEdgedetectButton()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage* gray=0,*edge=0;
	gray=cvCreateImage(cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),IPL_DEPTH_8U,1);
	edge=cvCreateImage(cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),IPL_DEPTH_8U,1);
	cvCvtColor(TheImage,gray,CV_BGR2GRAY);
	cvCanny(gray,edge,30,100,3);

	cvCvtColor(edge,TheImage,CV_GRAY2BGR);
	ShowImage(TheImage,IDC_ShowImg);

	cvReleaseImage(&gray);
	cvReleaseImage(&edge);
}

/************************************************************************/
/* 本地视频处理                                                                     */
/************************************************************************/
void CPlayVideoDlg::OnBnClickedReadvideoButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//cvZero()
	CFileDialog dlg(
		TRUE,
		_T("*.avi"),
		NULL,
		OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("*.avi|*.avi| All Files(*.*)|(*.*)||"),
		NULL
		);
		dlg.m_ofn.lpstrTitle=_T("Open Video");
		if (dlg.DoModal()!=IDOK)
			return;
		vPath=dlg.GetPathName();
		//使无关按钮无效
		GetDlgItem(IDC_Play_Button)->EnableWindow(TRUE);
		GetDlgItem(IDC_ReadImg_Button)->EnableWindow(FALSE);
		//使第一帧的画面显示在控件上
		CvCapture* myCapture=cvCreateFileCapture(vPath);
		IplImage* myImage=cvQueryFrame(myCapture);
		ResizeImage(myImage);
		ShowImage(TheImage,IDC_ShowImg);
		//cvReleaseImage(&myImage);
		cvReleaseCapture(&myCapture);;
}


void CPlayVideoDlg::OnBnClickedPlayButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CvCapture *pCapture=NULL;
	IplImage* pFrame=NULL;
	if (vPath==" ")
	{
		MessageBox("请选择视频文件");
		return;
	}else
	{
		if (!(pCapture=cvCreateFileCapture(vPath)))
		{
			MessageBox("打开视频文件失败");
			return;
		}
	}
	//播放视频时令读入图片和视频，以及播放按钮失效
	GetDlgItem(IDC_ReadImg_Button)->EnableWindow(FALSE);
	GetDlgItem(IDC_ReadVideo_Button)->EnableWindow(FALSE);
	GetDlgItem(IDC_Play_Button)->EnableWindow(FALSE);
	GetDlgItem(IDC_EdgeDetect_Button)->EnableWindow(FALSE);
	
	/************************************************************************/
	/* 下面的这段代码不太明白                                                                     */
	/************************************************************************/
	cvNamedWindow("videoSmile");
	cvResizeWindow("videoSmile",1,1);
	HWND hWnd=(HWND)cvGetWindowHandle("videoSmile");
	HWND hParent=::GetParent(hWnd);
	HWND hwnd1=::FindWindow("CmymfcDlg","PlayVideo");
	::SetParent(hWnd,hwnd1);
	::ShowWindow(hParent,SW_HIDE);

	//读取视频文件的帧数
	int frames=(int)cvGetCaptureProperty(pCapture,CV_CAP_PROP_FRAME_COUNT);
	int numfrm=0;
	//对数据清零
	if (TheImage)
		cvZero(TheImage);

	m_run=1;
	while ( (numfrm<frames)&(m_run==1))
	{
		pFrame=cvQueryFrame(pCapture);
		IplImage* newframe=cvCloneImage(pFrame);
		ResizeImage(newframe); //这个函数的作用使画面为与窗口中间 在这个函数中已经将newframe cvResize到TheImage中了
		ShowImage(TheImage,IDC_ShowImg);
		/************************************************************************/
		/* 这个地方加个存储帧的功能  （未加）                                                                   */
		/************************************************************************/
		if (cvWaitKey(20)==27) break;
		numfrm++;
		cvReleaseImage(&newframe);
	}
	m_run=0;

	//对图像数据清零
	if (TheImage)
	{
		cvZero(TheImage);
		ShowImage(TheImage,IDC_ShowImg);
	}

	GetDlgItem(IDC_ReadImg_Button)->EnableWindow(TRUE);
	GetDlgItem(IDC_ReadVideo_Button)->EnableWindow(TRUE);
	GetDlgItem(IDC_Play_Button)->EnableWindow(TRUE);

	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoSmile");

	return ;

}
