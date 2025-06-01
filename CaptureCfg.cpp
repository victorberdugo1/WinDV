#include "stdafx.h"
#include "WinDV.h"
#include "CaptureCfg.h"
#include "DShow.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCaptureCfg, CPropertyPage)

CCaptureCfg::CCaptureCfg()
    : CPropertyPage(CCaptureCfg::IDD),
    m_discontinuityTreshold(0),
    m_everyNth(0),
    m_maxAVIFrames(0),
    m_type12(-1),
    m_dtformat(_T("")),
    m_ndigits(-1)
{
}

CCaptureCfg::~CCaptureCfg()
{
}

void CCaptureCfg::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FEXAMPLE, m_fexample);
    DDX_Control(pDX, IDC_DTFORMAT, m_dtformatctl);
    DDX_Control(pDX, IDC_NDIGITS, m_ndigitsctl);
    DDX_Text(pDX, IDC_DISCONTINUITY_TRESHOLD, m_discontinuityTreshold);
    DDV_MinMaxUInt(pDX, m_discontinuityTreshold, 0, 1000000);
    DDX_Text(pDX, IDC_EVERY_NTH, m_everyNth);
    DDV_MinMaxUInt(pDX, m_everyNth, 1, 1000000);
    DDX_Text(pDX, IDC_MAX_FRAMES, m_maxAVIFrames);
    DDV_MinMaxUInt(pDX, m_maxAVIFrames, 10, 1000000);
    DDX_Radio(pDX, IDC_TYPE_1, m_type12);
    DDX_CBString(pDX, IDC_DTFORMAT, m_dtformat);
    DDX_CBIndex(pDX, IDC_NDIGITS, m_ndigits);
}

BEGIN_MESSAGE_MAP(CCaptureCfg, CPropertyPage)
    ON_WM_TIMER()
END_MESSAGE_MAP()

void CCaptureCfg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1) {
        CString tmp;
        m_dtformatctl.GetWindowText(tmp);
        CString tmp2 = FormatTime(tmp, time(nullptr));
        tmp = _T("...example");
        if (!tmp2.IsEmpty()) {
            tmp += _T(".");
            tmp += tmp2;
        }
        int n = m_ndigitsctl.GetCurSel();
        tmp2.Empty();
        if (n > 0) {
            tmp2.Format(_T(".%0*d"), n, 0);
        }
        m_fexample.SetWindowText(tmp + tmp2 + _T(".avi"));
    }
    else {
        CPropertyPage::OnTimer(nIDEvent);
    }
}

BOOL CCaptureCfg::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    CString tmp;
    for (int i = 0; i <= 4; i++) {
        tmp.Format(_T("%d"), i);
        m_ndigitsctl.AddString(tmp);
    }
    m_dtformatctl.AddString(m_dtformat);
    while (!m_dtformathistory.IsEmpty()) {
        tmp = m_dtformathistory.SpanExcluding(_T("\n"));
        int l = tmp.GetLength();
        if (l < m_dtformathistory.GetLength())
            m_dtformathistory = m_dtformathistory.Mid(l + 1);
        else
            m_dtformathistory.Empty();
        m_dtformatctl.AddString(tmp);
    }
    if (!m_dtformat.IsEmpty())
        m_dtformatctl.AddString(_T(""));

    m_ndigitsctl.SetCurSel(m_ndigits);
    OnTimer(1);
    SetTimer(1, 500, nullptr);
    return TRUE;
}

void CCaptureCfg::OnOK()
{
    CPropertyPage::OnOK();
    int i = m_dtformatctl.FindStringExact(-1, m_dtformat);
    if (i >= 0)
        m_dtformatctl.DeleteString(i);
    m_dtformathistory.Empty();
    int n = m_dtformatctl.GetCount();
    if (n > 10) n = 10;
    for (int i = 0; i < n; i++) {
        CString tmp;
        m_dtformatctl.GetLBText(i, tmp);
        if (!tmp.IsEmpty()) {
            if (!m_dtformathistory.IsEmpty())
                m_dtformathistory += _T("\n");
            m_dtformathistory += tmp;
        }
    }
}
