
// PlayVideoDlg.h : 头文件
//

#pragma once


// CPlayVideoDlg 对话框
class CPlayVideoDlg : public CDialogEx
{
// 构造
public:
	CPlayVideoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PLAYVIDEO_DIALOG };

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
	IplImage* TheImage;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedShowimg();
	afx_msg void OnBnClickedReadimgButton();
	void ShowImage(IplImage* img,UINT ID);
	void ResizeImage(IplImage* img);
	afx_msg void OnBnClickedEdgedetectButton();
	afx_msg void OnBnClickedReadvideoButton();
	afx_msg void OnBnClickedPlayButton();
private:
	CString vPath;
	int m_run;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//void PaintFontColor(int ID_CTL);
private:
//	COLORREF m_rgbFontColor;
public:
	afx_msg void OnBnClickedCancel();
};
