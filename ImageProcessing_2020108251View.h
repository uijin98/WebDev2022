
// ImageProcessing_2020108251View.h: CImageProcessing2020108251View 클래스의 인터페이스
//

#pragma once


class CImageProcessing2020108251View : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageProcessing2020108251View() noexcept;
	DECLARE_DYNCREATE(CImageProcessing2020108251View)

// 특성입니다.
public:
	CImageProcessing2020108251Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProcessing2020108251View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDownsample();
	void OnDownSampling();
	afx_msg void OnSumConstant();
	
//	afx_msg void OnMulConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnUpSampling();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	afx_msg void OnNegaTransform();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarization();
	afx_msg void OnQuantization();
	afx_msg void OnHistoStrech();
	afx_msg void OnEndInStrech();
	afx_msg void OnHistoEqual();
	void OnEmbossing();
	afx_msg void OnEmbossing1();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnHpfSharp();
	afx_msg void OnDiffOperatorHor();
	afx_msg void OnNearest();
	afx_msg void OnHomogenOperator();
	afx_msg void OnBilinear();
	afx_msg void OnNearestx4();
	afx_msg void OnBilinearx4();
	afx_msg void OnHomogenoperator_Threshold();
	afx_msg void OnMedianSub();
	afx_msg void OnMeanSub();
	afx_msg void OnmScale();
	afx_msg void OnTranslation();
	afx_msg void OnMirrorhor();
};

#ifndef _DEBUG  // ImageProcessing_2020108251View.cpp의 디버그 버전
inline CImageProcessing2020108251Doc* CImageProcessing2020108251View::GetDocument() const
   { return reinterpret_cast<CImageProcessing2020108251Doc*>(m_pDocument); }
#endif

