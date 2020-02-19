
// 180814120Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "180814120.h"
#include "180814120Dlg.h"
#include "afxdialogex.h"

#include <opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace cv;

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


// CMy180814120Dlg 对话框



CMy180814120Dlg::CMy180814120Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy180814120Dlg::IDD, pParent)
	, m_width(0)
	, m_height(0)
	, m_angle(0)
	, m_shear_ratio(0)
	, m_PseudoColorMode(0)
	, m_FilterType(0)
	, m_ShapenType(0)
	, m_thre(0)
	, m_MorphType(0)
	, m_ColorMode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy180814120Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_ANGLE, m_angle);
	DDX_Text(pDX, IDC_SHEAR_RATIO, m_shear_ratio);
	DDX_Radio(pDX, IDC_RADIO1, m_PseudoColorMode);
	DDX_Radio(pDX, IDC_AVER, m_FilterType);
	DDX_Radio(pDX, IDC_RADIO4, m_ShapenType);
	DDX_Text(pDX, IDC_Edit, m_thre);
	DDX_Radio(pDX, IDC_RADIO7, m_MorphType);
	DDX_Radio(pDX, IDC_RADIO11, m_ColorMode);
	//  DDX_Control(pDX, IDC_BUTTON6, m_ipl);
}

BEGIN_MESSAGE_MAP(CMy180814120Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CMy180814120Dlg::OnBnClickedOpen)
	ON_STN_CLICKED(IDC_PIC, &CMy180814120Dlg::OnStnClickedPic)
	ON_BN_CLICKED(IDC_RESIZE, &CMy180814120Dlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_ROTATION, &CMy180814120Dlg::OnBnClickedRotation)
	ON_BN_CLICKED(IDC_HSHEAR, &CMy180814120Dlg::OnBnClickedHshear)
	ON_BN_CLICKED(IDC_VAHEAR, &CMy180814120Dlg::OnBnClickedVahear)
	ON_BN_CLICKED(IDC_HISTEQ, &CMy180814120Dlg::OnBnClickedHisteq)
	ON_BN_CLICKED(IDC_PSEUDO, &CMy180814120Dlg::OnBnClickedPseudo)
	ON_BN_CLICKED(IDC_FILTER, &CMy180814120Dlg::OnBnClickedFilter)
	ON_BN_CLICKED(IDC_SHARP, &CMy180814120Dlg::OnBnClickedSharp)
	ON_BN_CLICKED(IDC_THRE, &CMy180814120Dlg::OnBnClickedThre)
	ON_BN_CLICKED(IDC_MORPH, &CMy180814120Dlg::OnBnClickedMorph)
	ON_BN_CLICKED(IDC_RADIO11, &CMy180814120Dlg::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy180814120Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_C, &CMy180814120Dlg::OnBnClickedC)
	ON_BN_CLICKED(IDC_Cvtcolor, &CMy180814120Dlg::OnBnClickedCvtcolor)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy180814120Dlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMy180814120Dlg 消息处理程序

BOOL CMy180814120Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//Bind OpenCV windows and Picture Control
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
		return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy180814120Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy180814120Dlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy180814120Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy180814120Dlg::OnBnClickedOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL);
	dlg.m_ofn.lpstrTitle = _T("打开图像文件"); //对话框标题
	dlg.m_ofn.lpstrInitialDir = "F:\\"; //默认打开路径
	dlg.m_ofn.lpstrFilter = "bmp (*.bmp)\0*.bmp\0 jpg (*.jpg)\0*.jpg\0 All Files (*.*) \0*.*\0\0"; //打开文件类型

	if (dlg.DoModal() != IDOK)             // 判断是否获得图片         
		return;
	m_path = dlg.GetPathName();

	//多字节字符集下 CString 转 char*  (LPSTR)(LPCSTR)
	src = imread((LPSTR)(LPCSTR)m_path);

	Mat img;  //保存缩放后的图像
	CRect rect;
	GetDlgItem(IDC_PIC)->GetClientRect(&rect); //获取图像显示区

	resize(src, img, Size(rect.Width(), rect.Height()), 0, 0);

	imshow("view", img);


	/****** Unicode字符集下 CString 转 char*  ******/
	/*
	int nLength = m_path.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, m_path, nLength, NULL, 0, NULL, NULL);
	char* VoicePath = new char[nBytes + 1];
	memset(VoicePath, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, m_path, nLength, VoicePath, nBytes, NULL, NULL);
	VoicePath[nBytes] = 0;
	src = imread(VoicePath);
	*/
	/************************************************/

}


void CMy180814120Dlg::OnStnClickedPic()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMy180814120Dlg::OnBnClickedResize()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	Mat dst;

	resize(src, dst, Size(m_width, m_height), 0, 0);

	imshow("缩放后图像", dst);

}


void CMy180814120Dlg::OnBnClickedRotation()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	Mat rot_mat(2, 3, CV_32FC1);//旋转变换矩阵
	Mat rotate_dst;

	// 计算旋转后图像尺寸
	double a = sin(m_angle  * CV_PI / 180);
	double b = cos(m_angle  * CV_PI / 180);
	int width = src.cols;
	int height = src.rows;
	int width_rotate = int(height * fabs(a) + width * fabs(b));
	int height_rotate = int(width * fabs(a) + height * fabs(b));

	//计算图像旋转变换矩阵
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = m_angle;
	double scale = 1;
	rot_mat = getRotationMatrix2D(center, angle, scale);

	// 修改坐标偏移
	rot_mat.at<double>(0, 2) += (width_rotate - width) / 2;
	rot_mat.at<double>(1, 2) += (height_rotate - height) / 2;

	/// 旋转图像
	warpAffine(src, rotate_dst, rot_mat, Size(width_rotate, height_rotate));

	namedWindow("旋转后图像");
	imshow("旋转后图像", rotate_dst);


}


void CMy180814120Dlg::OnBnClickedHshear()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//计算错切后图像大小
	double ratio = m_shear_ratio;
	int dst_wid;
	int dst_hei;

	if (ratio < 0)
	{
		dst_wid = g_src.cols + g_src.rows*ratio*(-1);
	}
	else
	{
		dst_wid = g_src.cols + g_src.rows*ratio;
	}

	dst_hei = g_src.rows;

	dst.create(Size(dst_wid, dst_hei), g_src.type());

	for (int i = 0; i<g_src.rows; i++)
	{
		if (ratio >= 0)
		for (int j = 0; j<g_src.cols; j++)
		{
			dst.at<uchar>(i, j + i*ratio) = g_src.at<uchar>(i, j);
		}
		else
		{
			int offset = (-1)*ratio*g_src.rows;
			for (int j = g_src.cols - 1; j >= 0; j--)
			{
				dst.at<uchar>(i, j + i*ratio + offset) = g_src.at<uchar>(i, j);
			}
		}
	}

	namedWindow("水平错切");
	imshow("水平错切", dst);

}


void CMy180814120Dlg::OnBnClickedVahear()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//计算错切后图像大小
	double ratio = m_shear_ratio;
	int dst_wid;
	int dst_hei;

	if (ratio < 0)
	{
		dst_hei = g_src.rows + g_src.cols*ratio*(-1);
	}
	else
	{
		dst_hei = g_src.rows + g_src.cols*ratio;
	}

	dst_wid = g_src.cols;

	dst.create(Size(dst_wid, dst_hei), g_src.type());

	for (int i = 0; i<g_src.rows; i++)
	{
		if (ratio >= 0)
		for (int j = 0; j<g_src.cols; j++)
		{
			dst.at<uchar>(i + j*ratio, j) = g_src.at<uchar>(i, j);
		}
		else
		{
			int offset = (-1)*ratio*g_src.cols;
			for (int j = g_src.cols - 1; j >= 0; j--)
			{
				dst.at<uchar>(i + j*ratio + offset, j) = g_src.at<uchar>(i, j);
			}
		}
	}

	namedWindow("垂直错切");
	imshow("垂直错切", dst);

}


void CMy180814120Dlg::OnBnClickedHisteq()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, dst;
	cvtColor(src, g_src, CV_BGR2GRAY);
	dst.create(g_src.size(), g_src.type());
	equalizeHist(g_src, dst);
	namedWindow("直方图均衡");
	imshow("直方图均衡", dst);
}


void CMy180814120Dlg::OnBnClickedPseudo()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, tmp_dst, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), CV_8UC3);

	UpdateData(TRUE);
	switch (m_PseudoColorMode)
	{

	case 0:
		for (int i = 0; i<g_src.rows; i++)
		{
			for (int j = 0; j<g_src.cols; j++)
			{
				int tmp = g_src.at<uchar>(i, j);


				if (tmp<60)
				{
					dst.at<Vec3b>(i, j)[0] = 255; //blue
					dst.at<Vec3b>(i, j)[1] = 0; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red
				}
				else if (tmp<150)
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red				
				}
				else
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 0; //green
					dst.at<Vec3b>(i, j)[2] = 255; //red				
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i<g_src.rows; i++)
		{
			for (int j = 0; j<g_src.cols; j++)
			{
				int tmp = g_src.at<uchar>(i, j);


				if (tmp<64)
				{
					dst.at<Vec3b>(i, j)[0] = 255; //blue
					dst.at<Vec3b>(i, j)[1] = tmp; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red
				}
				else if (tmp<128)
				{
					dst.at<Vec3b>(i, j)[0] = tmp; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = 0; //red				
				}
				else if (tmp<192)
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = 255; //green
					dst.at<Vec3b>(i, j)[2] = tmp; //red				
				}
				else
				{
					dst.at<Vec3b>(i, j)[0] = 0; //blue
					dst.at<Vec3b>(i, j)[1] = tmp; //green
					dst.at<Vec3b>(i, j)[2] = 255; //red				
				}
			}
		}
		break;
	case 2:
		break;
	}
	imshow("伪彩色", dst);

}


void CMy180814120Dlg::OnBnClickedFilter()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	switch (m_FilterType)
	{
	case 0:
		blur(g_src, dst, Size(5, 5));       //均值滤波  
		namedWindow("均值滤波");
		imshow("均值滤波", dst);
		break;

	case 1:
		medianBlur(g_src, dst, 7);
		imshow("中值滤波", dst);
		break;

	case 2:
		GaussianBlur(g_src, dst, Size(3, 3), 0, 0);   //高斯滤波  
		namedWindow("Gaussian滤波");
		imshow("Gaussian滤波", dst);

	}

}


void CMy180814120Dlg::OnBnClickedSharp()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, dst;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, abs_dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	switch (m_ShapenType)
	{
	case 0:
		Sobel(g_src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);
		imshow("X方向Sobel", abs_grad_x);

		//【4】求Y方向梯度  
		Sobel(g_src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y);
		imshow("Y方向Sobel", abs_grad_y);

		//【5】合并梯度(近似)  
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		/*
		void Sobel (
		InputArray src,//输入图
		OutputArray dst,//输出图
		int ddepth,//输出图像的深度
		int dx,
		int dy,
		int ksize=3,
		double scale=1,
		double delta=0,
		int borderType=BORDER_DEFAULT );
		第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。
		第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
		第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：
		若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F
		若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F
		若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F
		若src.depth() = CV_64F, 取ddepth = -1/CV_64F
		第四个参数，int类型dx，x 方向上的差分阶数。
		第五个参数，int类型dy，y方向上的差分阶数。
		第六个参数，int类型ksize，有默认值3，表示Sobel核的大小;必须取1，3，5或7。
		第七个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。
		第八个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
		第九个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate处得到更详细的信息。
		*/
		namedWindow("sobel");
		imshow("sobel", dst);
		break;

	case 1:
		Laplacian(g_src, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

		//【6】计算绝对值，并将结果转换成8位  
		convertScaleAbs(dst, abs_dst);
		/*
		void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );
		第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
		第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和通道数。
		第三个参数，int类型的ddept，目标图像的深度。
		第四个参数，int类型的ksize，用于计算二阶导数的滤波器的孔径尺寸，大小必须为正奇数，且有默认值1。
		第五个参数，double类型的scale，计算拉普拉斯值的时候可选的比例因子，有默认值1。
		第六个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
		第七个参数， int类型的borderType，边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate()处得到更详细的信息。
		*/
		namedWindow("Laplace");
		imshow("Laplace", abs_dst);
		break;
	case 2:
		Canny(g_src, dst, 100, 150, 3);
		/*
		void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )
		第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
		第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。
		第三个参数，double类型的threshold1，第一个滞后性阈值。
		第四个参数，double类型的threshold2，第二个滞后性阈值。
		第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。
		第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false。
		*/
		namedWindow("Canny");
		imshow("Canny", dst);

	}


}


void CMy180814120Dlg::OnBnClickedThre()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);
	if (m_thre < 0)
	{
		m_thre = 0;
	}
	if (m_thre > 255)
	{
		m_thre = 255;
	}
	threshold(g_src, dst, m_thre, 255, CV_THRESH_BINARY);//固定阈值分割
	/*
	doublethreshold(InputArray src,OutputArray dst,double thresh,double maxval,int type)
	第一个参数，InputArray类型的src，输入数组，填单通道 , 8或32位浮点类型的Mat即可。
	第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放输出结果，且和第一个参数中的Mat变量有一样的尺寸和类型。
	第三个参数，double类型的thresh，阈值的具体值。
	第四个参数，double类型的maxval，当第五个参数阈值类型type取 THRESH_BINARY 或THRESH_BINARY_INV阈值类型时的最大值.
	第五个参数，int类型的type，阈值类型。
	第五参数有以下几种类型
	0: THRESH_BINARY  当前点值大于阈值时，取Maxval,也就是第四个参数，下面再不说明，否则设置为0
	1: THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval
	2: THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变
	3: THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0
	4:THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变
	*/

	namedWindow("固定阈值分割");
	imshow("固定阈值分割", dst);


}


void CMy180814120Dlg::OnBnClickedMorph()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat g_src, tmp_dst, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	threshold(g_src, tmp_dst, m_thre, 255, CV_THRESH_BINARY);//固定阈值分割

	imshow("二值图像", tmp_dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));//定义结构元素

	switch (m_MorphType)
	{
	case 0:
		erode(tmp_dst, dst, element);
		imshow("腐蚀", dst);
		break;

	case 1:
		dilate(tmp_dst, dst, element);
		imshow("膨胀", dst);
		break;

	case 2:
		morphologyEx(tmp_dst, dst, MORPH_OPEN, element);//开运算
		imshow("开运算", dst);
		break;

	case 3:
		morphologyEx(tmp_dst, dst, MORPH_CLOSE, element);//闭运算
		imshow("闭运算", dst);
		break;
	}


}










void CMy180814120Dlg::OnBnClickedCvtcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat g_src,dst;
	cvtColor(src, g_src, CV_BGR2GRAY);
    dst.create(g_src.size(), g_src.type());
	UpdateData(TRUE);
	switch (m_ColorMode)
	{
	case 0:  //RGB->XYZ
		cvtColor(src, dst, COLOR_BGR2XYZ);
		imshow("RGB", src);
		imshow("XYZ", dst);
		break;
	case 1:  //RGB->YCrCb
		cvtColor(src, dst, COLOR_BGR2YCrCb);
		imshow("RGB", src);
		imshow("YCrCb", dst);
		break;
	case 2:  //RGB->HSV
		cvtColor(src, dst, COLOR_BGR2HSV);
		imshow("RGB", src);
		imshow("HSV", dst);
		break;
	}

}


void CMy180814120Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat  dst;
	UpdateData(TRUE);
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(m_comRatio);
	imwrite("C:\\lena.jpg", src, compression_params);
	dst = imread("C:\\Tulips.jpg");
	imshow("srcImage", src);
	imshow("dstImage", src);
}
