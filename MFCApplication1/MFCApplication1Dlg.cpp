﻿
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRect r;
	GetClientRect(r);

	int w = r.Width(), h = r.Height();
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_COUNT; i++) {
		m_list[i].x = rand() % w;
		m_list[i].y = rand() % h;
		m_list[i].r = rand() % 40 + 10;		// 10 ~ 49
		m_list[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	
	SetTimer(1, 200, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CircleData * p = m_list;
		CBrush fill_brush, *p_old_brush = dc.GetCurrentBrush;
		for (int i = 0; i < MAX_COUNT; i++) {
			// dc.Ellipse(m_list[i].x - m_list[i].r, m_list[i].y - m_list[i].r,
			//		m_list[i].x + m_list[i].r, m_list[i].y + m_list[i].r);

			// 위 연산을 좀 더 간단히
			fill_brush.CreateSolidBrush(p->color);
			//p_old_brush = dc.SelectObject(&fill_brush);
			dc.SelectObject(&fill_brush);
			dc.Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			p++;

			dc.SelectObject(p_old_brush);
			fill_brush.DeleteObject();
		}
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	
	if (nIDEvent == 1) {
		CRect r;
		GetClientRect(r);

		int w = r.Width(), h = r.Height();

		CircleData * p = m_list;
		for (int i = 0; i < MAX_COUNT; i++) {
			p->r--;
			if (p->r <= 0) {
				p->x = rand() % w;
				p->y = rand() % h;
				p->r = rand() % 40 + 10;		// 10 ~ 49
				p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			p++;
		}
		Invalidate();

	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}
