
// 180814120Dlg.h : 头文件
//

#pragma once
#include<opencv2/core/core.hpp>
#include "afxwin.h"
using namespace cv;

// CMy180814120Dlg 对话框
class CMy180814120Dlg : public CDialogEx
{
// 构造
public:
	CMy180814120Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY180814120_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
