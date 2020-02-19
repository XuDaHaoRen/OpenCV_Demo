
// 180814120Dlg.h : ͷ�ļ�
//

#pragma once
#include<opencv2/core/core.hpp>
#include "afxwin.h"
using namespace cv;

// CMy180814120Dlg �Ի���
class CMy180814120Dlg : public CDialogEx
{
// ����
public:
	CMy180814120Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY180814120_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_path;
	Mat src;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnStnClickedPic();
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedRotation();
	afx_msg void OnBnClickedHshear();
	afx_msg void OnBnClickedVahear();
	double m_width;
	double m_height;
	double m_angle;
	double m_shear_ratio;
	int m_PseudoColorMode;
	afx_msg void OnBnClickedHisteq();
	afx_msg void OnBnClickedPseudo();
	afx_msg void OnBnClickedFilter();
	int m_FilterType;
	int m_ShapenType;
	afx_msg void OnBnClickedSharp();
	afx_msg void OnBnClickedThre();
	double m_thre;
	int m_MorphType;
	afx_msg void OnBnClickedMorph();
	afx_msg void OnBnClickedRadio11();
	int m_ColorMode;
	afx_msg void OnBnClickedButton6();
//	CButton m_ipl;
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedCvtcolor();
	afx_msg void OnBnClickedButton7();
};
