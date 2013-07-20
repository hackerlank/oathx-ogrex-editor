// GamePlazaDlg.h : 头文件
//

#pragma once


// CGamePlazaDlg 对话框
class CGamePlazaDlg : public CDialog
{
// 构造
public:
	CGamePlazaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GAMEPLAZA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CSize               m_ScreenMetrics;                    //屏幕尺寸
	CRect				m_rcNormalSize;						//正常位置
};
