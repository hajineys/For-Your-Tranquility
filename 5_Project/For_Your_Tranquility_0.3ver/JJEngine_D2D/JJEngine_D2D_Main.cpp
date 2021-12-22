#include "pch.h"

#include "JJEngine_D2D.h"
#include "JJEngine_Macro.h"

JJEngine* JJEngine::m_pInstance = nullptr;

JJEngine::JJEngine()
	: m_pFactory(nullptr), m_pDWriteFactory(nullptr), m_pNowBrush(nullptr),
	m_pRenderTarget(nullptr), m_pTextFormat(nullptr), m_pImageFactory(nullptr)
	, m_MainFont(L""), m_MainFontSize(0)
{

}

JJEngine::~JJEngine()
{

}

JJEngine* JJEngine::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new JJEngine;
	}

	return m_pInstance;
}

void JJEngine::Initialize(HWND hwnd)
{
	// 컴포넌트를 사용할 수 있도록 프로그램을 초기화한다.
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if (SUCCEEDED(hr))
	{
		// Factory 객체를 생성한다.
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	}

	/// 렌더 타겟 생성
	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetClientRect(hwnd, &rc);	// 클라이언트 영역의 좌표를 얻는다.

		// Render Target을 생성한다.
		hr = m_pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(hwnd, SizeU(rc.right - rc.left, rc.bottom - rc.top)),
			&m_pRenderTarget);

		// 기본 브러쉬 생성
		m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::WhiteSmoke), &m_pNowBrush);
	}

	/// 이미지 팩토리 생성
	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pImageFactory)
		);
	}

	/// write 팩토리 생성
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}

	// 메인으로 쓸 글씨체, 글씨 크기 설정
	if (SUCCEEDED(hr))
	{
		m_MainFont = L"맑은 고딕";
		m_MainFontSize = 20;

		hr = m_pDWriteFactory->CreateTextFormat(
			(WCHAR*)m_MainFont.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_MainFontSize,
			L"", //locale
			&m_pTextFormat);
	}

	// 텍스트 정렬 방식
	if (SUCCEEDED(hr))
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void JJEngine::Release()
{
	/// 프로그램이 종료되기전 CoInitializeEx함수의 반대 역할을 하는 CoUninitialize함수를 호출해야함
	CoUninitialize();

	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pNowBrush);

	// 텍스트 관련
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);

	// Instance 삭제
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void JJEngine::BeginRender()
{
	m_pRenderTarget->BeginDraw();

	// 화면을 지운다.
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
}

void JJEngine::EndRender()
{
	m_pRenderTarget->EndDraw();
}

void JJEngine::SetBrushColor(float r, float g, float b, float a)
{
	SafeRelease(&m_pNowBrush);

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &m_pNowBrush);
}

void JJEngine::SetBrushColor(D2D1::ColorF color)
{
	SafeRelease(&m_pNowBrush);

	m_pRenderTarget->CreateSolidColorBrush(color, &m_pNowBrush);
}

void JJEngine::SetBrushColor(D2D1_COLOR_F color)
{
	SafeRelease(&m_pNowBrush);

	m_pRenderTarget->CreateSolidColorBrush(color, &m_pNowBrush);
}

void JJEngine::SetFontSize(int fontSize)
{
	SafeRelease(&m_pTextFormat);

	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->CreateTextFormat(
			(WCHAR*)m_MainFont.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"", // locale
			&m_pTextFormat);
	}

	// 텍스트 정렬 방식
	if (m_pTextFormat != nullptr)
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void JJEngine::SetFont(wstring fontName)
{
	SafeRelease(&m_pTextFormat);

	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->CreateTextFormat(
			fontName.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_MainFontSize,
			L"", //locale
			&m_pTextFormat);
	}

	// 텍스트 정렬 방식
	if (m_pTextFormat != nullptr)
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void JJEngine::SetFont(wstring fontName, int fontSize)
{
	SafeRelease(&m_pTextFormat);

	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->CreateTextFormat(
			fontName.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"", //locale
			&m_pTextFormat);
	}

	// 텍스트 정렬 방식
	if (m_pTextFormat != nullptr)
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void JJEngine::DrawLine(float x1, float y1, float x2, float y2)
{
	D2D1_POINT_2F startPoint = { x1, y1 };
	D2D1_POINT_2F endPoint = { x2, y2 };

	m_pRenderTarget->DrawLine(startPoint, endPoint, m_pNowBrush);
}

void JJEngine::DrawLine(float x1, float y1, float x2, float y2, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_POINT_2F startPoint = { x1, y1 };
	D2D1_POINT_2F endPoint = { x2, y2 };

	m_pRenderTarget->DrawLine(startPoint, endPoint, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawRectangle(float x1, float y1, float x2, float y2)
{
	D2D1_RECT_F r = { x1,y1,x2,y2 };

	m_pRenderTarget->DrawRectangle(r, m_pNowBrush);
}

void JJEngine::DrawRectangle(float x1, float y1, float x2, float y2, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_RECT_F r = { x1,y1,x2,y2 };

	m_pRenderTarget->DrawRectangle(r, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawFillRectangle(float x1, float y1, float x2, float y2)
{
	D2D1_RECT_F r = { x1,y1,x2,y2 };

	m_pRenderTarget->FillRectangle(r, m_pNowBrush);
}

void JJEngine::DrawFillRectangle(float x1, float y1, float x2, float y2, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_RECT_F r = { x1,y1,x2,y2 };

	m_pRenderTarget->FillRectangle(r, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawEllipse(float x, float y, float size)
{
	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)x, (float)y };
	ellipse.radiusX = size;
	ellipse.radiusY = size;

	m_pRenderTarget->DrawEllipse(ellipse, m_pNowBrush);
}

void JJEngine::DrawEllipse(float x, float y, float size, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)x, (float)y };
	ellipse.radiusX = size;
	ellipse.radiusY = size;

	m_pRenderTarget->DrawEllipse(ellipse, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawEllipse(float x1, float y1, float x2, float y2)
{
	D2D1_RECT_F r = { x1,y1,x2,y2 };

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)(x1 + x2) / 2, (float)(y1 + y2) / 2 };
	ellipse.radiusX = (x2 - x1) / 2;
	ellipse.radiusY = (y2 - y1) / 2;

	m_pRenderTarget->DrawEllipse(ellipse, m_pNowBrush);
}

void JJEngine::DrawEllipse(float x1, float y1, float x2, float y2, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_RECT_F r = { x1,y1,x2,y2 };

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)(x1 + x2) / 2, (float)(y1 + y2) / 2 };
	ellipse.radiusX = (x2 - x1) / 2;
	ellipse.radiusY = (y2 - y1) / 2;

	m_pRenderTarget->DrawEllipse(ellipse, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawFillEllipse(float x, float y, float size, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)x, (float)y };
	ellipse.radiusX = size;
	ellipse.radiusY = size;

	m_pRenderTarget->FillEllipse(ellipse, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawFillEllipse(float x1, float y1, float x2, float y2)
{
	D2D1_RECT_F r = { x1,y1,x2,y2 };

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)(x1 + x2) / 2, (float)(y1 + y2) / 2 };
	ellipse.radiusX = (x2 - x1) / 2;
	ellipse.radiusY = (y2 - y1) / 2;

	m_pRenderTarget->FillEllipse(ellipse, m_pNowBrush);
}

void JJEngine::DrawFillEllipse(float x1, float y1, float x2, float y2, ColorF color)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();

	SetBrushColor(color);

	D2D1_RECT_F r = { x1,y1,x2,y2 };

	D2D1_ELLIPSE ellipse;
	ellipse.point = { (float)(x1 + x2) / 2, (float)(y1 + y2) / 2 };
	ellipse.radiusX = (x2 - x1) / 2;
	ellipse.radiusY = (y2 - y1) / 2;

	m_pRenderTarget->FillEllipse(ellipse, m_pNowBrush);

	SetBrushColor(_oldColor);
}

void JJEngine::DrawText(float x, float y, const WCHAR* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
}

void JJEngine::DrawText(float x, float y, ColorF color, const WCHAR* pch, ...)
{
	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetBrushColor(_oldColor);
}

void JJEngine::DrawText(float x, float y, int fontSize, const WCHAR* pch, ...)
{
	SetFontSize(fontSize);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFontSize(m_MainFontSize);
}

void JJEngine::DrawText(float x, float y, int fontSize, ColorF color, const WCHAR* pch, ...)
{
	SetFontSize(fontSize);

	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetBrushColor(_oldColor);
	SetFontSize(m_MainFontSize);
}

void JJEngine::DrawText(float x, float y, const WCHAR* font, int fontSize, const WCHAR* pch, ...)
{
	SetFont(font, fontSize);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFont(m_MainFont, m_MainFontSize);
}

void JJEngine::DrawText(float x, float y, const WCHAR* font, int fontSize, ColorF color, const WCHAR* pch, ...)
{
	SetFont(font, fontSize);

	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFont(m_MainFont, m_MainFontSize);
	SetBrushColor(_oldColor);
}

void JJEngine::DrawText(float x, float y, const WCHAR* font, const WCHAR* pch, ...)
{
	SetFont(font);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFont(m_MainFont);
}

void JJEngine::DrawText(float x, float y, const WCHAR* font, ColorF color, const WCHAR* pch, ...)
{
	SetFont(font);

	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFont(m_MainFont);
	SetBrushColor(_oldColor);
}

void JJEngine::DrawText(float x, float y, int sizeX, int sizeY, const WCHAR* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + sizeX), (float)(y + sizeY)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
}

void JJEngine::DrawText(float x, float y, int sizeX, int sizeY, JScript script)
{
	DrawText(x, y, sizeX, sizeY, script.NowText.c_str());
}

void JJEngine::DrawText(float x, float y, int sizeX, int sizeY, int fontSize, ColorF color, const WCHAR* pch, ...)
{
	SetFontSize(fontSize);

	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + sizeX), (float)(y + sizeY)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFontSize(m_MainFontSize);
	SetBrushColor(_oldColor);
}

void JJEngine::DrawText(float x, float y, int sizeX, int sizeY, const WCHAR* font, int fontSize, ColorF color, const WCHAR* pch, ...)
{
	SetFont(font, fontSize);

	D2D1_COLOR_F _oldColor = m_pNowBrush->GetColor();
	SetBrushColor(color);

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + sizeX), (float)(y + sizeY)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	SetFont(m_MainFont, m_MainFontSize);
	SetBrushColor(_oldColor);
}

HRESULT JJEngine::LoadBitmapFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = m_pImageFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = m_pImageFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = m_pImageFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void JJEngine::DrawSprite(ID2D1Bitmap* bitmap, float x, float y, float opacity /*=1.0f*/)
{
	D2D1_SIZE_F size = bitmap->GetSize();

	m_pRenderTarget->DrawBitmap(bitmap,
		D2D1::RectF((float)x, (float)y, (float)x + size.width, (float)y + size.height),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((float)0, (float)0, (float)size.width, (float)size.height)
	);
}

void JJEngine::DrawSprite(JImage* sprite, float x, float y, float opacity /*=1.0f*/)
{
	D2D1_SIZE_F size = sprite->Bitmap->GetSize();

	m_pRenderTarget->DrawBitmap(sprite->Bitmap,
		D2D1::RectF((float)x, (float)y, (float)x + size.width / sprite->Frame, (float)y + size.height),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((float)sprite->DrawIndex * (size.width / sprite->Frame), (float)0,
			(float)sprite->DrawIndex * (size.width / sprite->Frame) + (size.width / sprite->Frame), (float)size.height)
	);
}

void JJEngine::DrawSprite(ID2D1Bitmap* spriteSheet, JMotion* motion, float x, float y, float opacity /*=1.0f*/)
{
	JSprite& sprite = motion->SpriteVec[motion->DrawIndex];

	m_pRenderTarget->DrawBitmap(spriteSheet,
		D2D1::RectF((float)x - sprite.Pivot.x, (float)y - sprite.Pivot.y, (float)x - sprite.Pivot.x + sprite.Width, (float)y - sprite.Pivot.y+ sprite.Height),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((float)sprite.DrawPoint.x, (float)sprite.DrawPoint.y,
			(float)sprite.DrawPoint.x + sprite.Width,
			(float)sprite.DrawPoint.y + sprite.Height)
	);
}