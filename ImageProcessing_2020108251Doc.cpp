
// ImageProcessing_2020108251Doc.cpp: CImageProcessing2020108251Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_2020108251.h"
#endif

#include "ImageProcessing_2020108251Doc.h"

#include <propkey.h>
#include "CDownSampleDlg.h"
#include "CConstantDlg.h"
#include "CUpSampleDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessing2020108251Doc

IMPLEMENT_DYNCREATE(CImageProcessing2020108251Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessing2020108251Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcessing2020108251Doc 생성/소멸

CImageProcessing2020108251Doc::CImageProcessing2020108251Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessing2020108251Doc::~CImageProcessing2020108251Doc()
{
}

BOOL CImageProcessing2020108251Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessing2020108251Doc serialization

void CImageProcessing2020108251Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessing2020108251Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessing2020108251Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessing2020108251Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessing2020108251Doc 진단

#ifdef _DEBUG
void CImageProcessing2020108251Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessing2020108251Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessing2020108251Doc 명령


BOOL CImageProcessing2020108251Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

	//이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
	if (File.GetLength() == 256 * 256) { //RAW 파일 크기 결정

		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { //RAW 파일의 크기 결정
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox("Not Support Image Size");
		return 0;
	}
	m_size = m_width * m_height;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i<m_size; i++)
		m_InputImage[i] = 255;
	File.Read(m_InputImage, m_size);
	File.Close();

	return TRUE;
}


BOOL CImageProcessing2020108251Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File; //파일 객체 선언
	CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);
	//raw 파일을 다른 이름으로 저장하기를 위한 대화상자 객체 선언

	if (SaveDlg.DoModal() == IDOK) {
		//DoModel 멤버 함수에서 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		//파일 열기
		File.Write(m_InputImage, m_size); //파일 쓰기
		File.Close(); //  파일 닫기
	}
	return CDocument::OnSaveDocument(lpszPathName);
}


void CImageProcessing2020108251Doc::OnDownSampling()
{
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		m_Re_width = m_width / dlg.m_DownSampleRate;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnSumConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;

			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnSubConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0;

			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] - dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnMulConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] * dlg.m_Constant >255)
				m_OutputImage[i] = 255;
			else if (m_InputImage[i] * dlg.m_Constant <0)
				m_OutputImage[i] = 0;

			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnDivConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] / dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			else if (m_InputImage[i] / dlg.m_Constant < 0)
				m_OutputImage[i] = 0;

			else {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
			}
		}
	}
}


void CImageProcessing2020108251Doc::OnUpSampling()
{
	int i, j;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_Re_height = m_height * dlg.m_UpSampleRate;
		m_Re_width = m_width * dlg.m_UpSampleRate;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0;

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[(i * dlg.m_UpSampleRate * m_Re_width) + dlg.m_UpSampleRate * j]
					= m_InputImage[i * m_width + j];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnAndOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i]= (m_InputImage[i] & (unsigned char)dlg.m_Constant);
					
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnOrOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] | (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);

			}
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnXorOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] ^ (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i] = (m_InputImage[i]	^ (unsigned char)dlg.m_Constant);

			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnNegaTransform()
{
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i];
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnGammaCorrection()
{
	CConstantDlg dlg;

	int i;
	double temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);

			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnBinarization()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnQuantization()
{
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		
		TEMP = new double[m_size];

		LEVEL = 256;
		HIGH = 256;

		value = (int)pow(2, dlg.m_Constant);

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
					TEMP[i] = (double)(HIGH / value) * j;
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
		}
	}
	
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHistoStrech()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnEndInStrech()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] <= MIN) {
			m_OutputImage[i] = 0;
		}

		else if (m_InputImage[i] >= MAX) {
			m_OutputImage[i] = 255;
		}

		else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i]) -
				MIN) * HIGH / (MAX - MIN);
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHistoEqual()
{
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	
	m_OutputImage = new unsigned char[m_Re_size];


	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i]
			= (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// TODO: 여기에 구현 코드 추가.
}



