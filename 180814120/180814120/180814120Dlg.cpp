
// 180814120Dlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy180814120Dlg �Ի���



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


// CMy180814120Dlg ��Ϣ�������

BOOL CMy180814120Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//Bind OpenCV windows and Picture Control
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
		return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy180814120Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy180814120Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy180814120Dlg::OnBnClickedOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL);
	dlg.m_ofn.lpstrTitle = _T("��ͼ���ļ�"); //�Ի������
	dlg.m_ofn.lpstrInitialDir = "F:\\"; //Ĭ�ϴ�·��
	dlg.m_ofn.lpstrFilter = "bmp (*.bmp)\0*.bmp\0 jpg (*.jpg)\0*.jpg\0 All Files (*.*) \0*.*\0\0"; //���ļ�����

	if (dlg.DoModal() != IDOK)             // �ж��Ƿ���ͼƬ         
		return;
	m_path = dlg.GetPathName();

	//���ֽ��ַ����� CString ת char*  (LPSTR)(LPCSTR)
	src = imread((LPSTR)(LPCSTR)m_path);

	Mat img;  //�������ź��ͼ��
	CRect rect;
	GetDlgItem(IDC_PIC)->GetClientRect(&rect); //��ȡͼ����ʾ��

	resize(src, img, Size(rect.Width(), rect.Height()), 0, 0);

	imshow("view", img);


	/****** Unicode�ַ����� CString ת char*  ******/
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMy180814120Dlg::OnBnClickedResize()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	Mat dst;

	resize(src, dst, Size(m_width, m_height), 0, 0);

	imshow("���ź�ͼ��", dst);

}


void CMy180814120Dlg::OnBnClickedRotation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	Mat rot_mat(2, 3, CV_32FC1);//��ת�任����
	Mat rotate_dst;

	// ������ת��ͼ��ߴ�
	double a = sin(m_angle  * CV_PI / 180);
	double b = cos(m_angle  * CV_PI / 180);
	int width = src.cols;
	int height = src.rows;
	int width_rotate = int(height * fabs(a) + width * fabs(b));
	int height_rotate = int(width * fabs(a) + height * fabs(b));

	//����ͼ����ת�任����
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = m_angle;
	double scale = 1;
	rot_mat = getRotationMatrix2D(center, angle, scale);

	// �޸�����ƫ��
	rot_mat.at<double>(0, 2) += (width_rotate - width) / 2;
	rot_mat.at<double>(1, 2) += (height_rotate - height) / 2;

	/// ��תͼ��
	warpAffine(src, rotate_dst, rot_mat, Size(width_rotate, height_rotate));

	namedWindow("��ת��ͼ��");
	imshow("��ת��ͼ��", rotate_dst);


}


void CMy180814120Dlg::OnBnClickedHshear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//������к�ͼ���С
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

	namedWindow("ˮƽ����");
	imshow("ˮƽ����", dst);

}


void CMy180814120Dlg::OnBnClickedVahear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	//������к�ͼ���С
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

	namedWindow("��ֱ����");
	imshow("��ֱ����", dst);

}


void CMy180814120Dlg::OnBnClickedHisteq()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Mat g_src, dst;
	cvtColor(src, g_src, CV_BGR2GRAY);
	dst.create(g_src.size(), g_src.type());
	equalizeHist(g_src, dst);
	namedWindow("ֱ��ͼ����");
	imshow("ֱ��ͼ����", dst);
}


void CMy180814120Dlg::OnBnClickedPseudo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	imshow("α��ɫ", dst);

}


void CMy180814120Dlg::OnBnClickedFilter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	switch (m_FilterType)
	{
	case 0:
		blur(g_src, dst, Size(5, 5));       //��ֵ�˲�  
		namedWindow("��ֵ�˲�");
		imshow("��ֵ�˲�", dst);
		break;

	case 1:
		medianBlur(g_src, dst, 7);
		imshow("��ֵ�˲�", dst);
		break;

	case 2:
		GaussianBlur(g_src, dst, Size(3, 3), 0, 0);   //��˹�˲�  
		namedWindow("Gaussian�˲�");
		imshow("Gaussian�˲�", dst);

	}

}


void CMy180814120Dlg::OnBnClickedSharp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		imshow("X����Sobel", abs_grad_x);

		//��4����Y�����ݶ�  
		Sobel(g_src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y);
		imshow("Y����Sobel", abs_grad_y);

		//��5���ϲ��ݶ�(����)  
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		/*
		void Sobel (
		InputArray src,//����ͼ
		OutputArray dst,//���ͼ
		int ddepth,//���ͼ������
		int dx,
		int dy,
		int ksize=3,
		double scale=1,
		double delta=0,
		int borderType=BORDER_DEFAULT );
		��һ��������InputArray ���͵�src��Ϊ����ͼ����Mat���ͼ��ɡ�
		�ڶ���������OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
		������������int���͵�ddepth�����ͼ�����ȣ�֧������src.depth()��ddepth����ϣ�
		��src.depth() = CV_8U, ȡddepth =-1/CV_16S/CV_32F/CV_64F
		��src.depth() = CV_16U/CV_16S, ȡddepth =-1/CV_32F/CV_64F
		��src.depth() = CV_32F, ȡddepth =-1/CV_32F/CV_64F
		��src.depth() = CV_64F, ȡddepth = -1/CV_64F
		���ĸ�������int����dx��x �����ϵĲ�ֽ�����
		�����������int����dy��y�����ϵĲ�ֽ�����
		������������int����ksize����Ĭ��ֵ3����ʾSobel�˵Ĵ�С;����ȡ1��3��5��7��
		���߸�������double���͵�scale�����㵼��ֵʱ��ѡ���������ӣ�Ĭ��ֵ��1����ʾĬ���������û��Ӧ�����ŵġ����ǿ������ĵ��в���getDerivKernels����ؽ��ܣ����õ���������ĸ�����Ϣ��
		�ڰ˸�������double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0��
		�ھŸ������� int���͵�borderType�����ǵ��������ˣ����������һ�����������߽�ģʽ��Ĭ��ֵΪBORDER_DEFAULT��������������ڹٷ��ĵ���borderInterpolate���õ�����ϸ����Ϣ��
		*/
		namedWindow("sobel");
		imshow("sobel", dst);
		break;

	case 1:
		Laplacian(g_src, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

		//��6���������ֵ���������ת����8λ  
		convertScaleAbs(dst, abs_dst);
		/*
		void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );
		��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
		�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ��ͨ������
		������������int���͵�ddept��Ŀ��ͼ�����ȡ�
		���ĸ�������int���͵�ksize�����ڼ�����׵������˲����Ŀ׾��ߴ磬��С����Ϊ������������Ĭ��ֵ1��
		�����������double���͵�scale������������˹ֵ��ʱ���ѡ�ı������ӣ���Ĭ��ֵ1��
		������������double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0��
		���߸������� int���͵�borderType���߽�ģʽ��Ĭ��ֵΪBORDER_DEFAULT��������������ڹٷ��ĵ���borderInterpolate()���õ�����ϸ����Ϣ��
		*/
		namedWindow("Laplace");
		imshow("Laplace", abs_dst);
		break;
	case 2:
		Canny(g_src, dst, 100, 150, 3);
		/*
		void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )
		��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λͼ��
		�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
		������������double���͵�threshold1����һ���ͺ�����ֵ��
		���ĸ�������double���͵�threshold2���ڶ����ͺ�����ֵ��
		�����������int���͵�apertureSize����ʾӦ��Sobel���ӵĿ׾���С������Ĭ��ֵ3��
		������������bool���͵�L2gradient��һ������ͼ���ݶȷ�ֵ�ı�ʶ����Ĭ��ֵfalse��
		*/
		namedWindow("Canny");
		imshow("Canny", dst);

	}


}


void CMy180814120Dlg::OnBnClickedThre()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	threshold(g_src, dst, m_thre, 255, CV_THRESH_BINARY);//�̶���ֵ�ָ�
	/*
	doublethreshold(InputArray src,OutputArray dst,double thresh,double maxval,int type)
	��һ��������InputArray���͵�src���������飬�ͨ�� , 8��32λ�������͵�Mat���ɡ�
	�ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ�����������Һ͵�һ�������е�Mat������һ���ĳߴ�����͡�
	������������double���͵�thresh����ֵ�ľ���ֵ��
	���ĸ�������double���͵�maxval���������������ֵ����typeȡ THRESH_BINARY ��THRESH_BINARY_INV��ֵ����ʱ�����ֵ.
	�����������int���͵�type����ֵ���͡�
	������������¼�������
	0: THRESH_BINARY  ��ǰ��ֵ������ֵʱ��ȡMaxval,Ҳ���ǵ��ĸ������������ٲ�˵������������Ϊ0
	1: THRESH_BINARY_INV ��ǰ��ֵ������ֵʱ������Ϊ0����������ΪMaxval
	2: THRESH_TRUNC ��ǰ��ֵ������ֵʱ������Ϊ��ֵ�����򲻸ı�
	3: THRESH_TOZERO ��ǰ��ֵ������ֵʱ�����ı䣬��������Ϊ0
	4:THRESH_TOZERO_INV  ��ǰ��ֵ������ֵʱ������Ϊ0�����򲻸ı�
	*/

	namedWindow("�̶���ֵ�ָ�");
	imshow("�̶���ֵ�ָ�", dst);


}


void CMy180814120Dlg::OnBnClickedMorph()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Mat g_src, tmp_dst, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst.create(g_src.size(), g_src.type());

	UpdateData(TRUE);

	threshold(g_src, tmp_dst, m_thre, 255, CV_THRESH_BINARY);//�̶���ֵ�ָ�

	imshow("��ֵͼ��", tmp_dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));//����ṹԪ��

	switch (m_MorphType)
	{
	case 0:
		erode(tmp_dst, dst, element);
		imshow("��ʴ", dst);
		break;

	case 1:
		dilate(tmp_dst, dst, element);
		imshow("����", dst);
		break;

	case 2:
		morphologyEx(tmp_dst, dst, MORPH_OPEN, element);//������
		imshow("������", dst);
		break;

	case 3:
		morphologyEx(tmp_dst, dst, MORPH_CLOSE, element);//������
		imshow("������", dst);
		break;
	}


}










void CMy180814120Dlg::OnBnClickedCvtcolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
