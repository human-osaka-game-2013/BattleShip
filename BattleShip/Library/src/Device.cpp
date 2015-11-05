#include "device.h"
#include "joystick_XInput.h"

//	コンストラクタ
CDevice::CDevice( HWND* _hWnd ) : m_hWnd(_hWnd)
{

}

HRESULT	CDevice::InitDevice()
{
	// Direct3D周りの初期化処理
	if ( FAILED ( InitD3d() ) ) return 0;
	
	//	キーの初期化
	if ( FAILED ( InitDinput() ) ) return 0;

	return 1;
}

// Direct3Dの初期化
// 第1引数：ウインドハンドル
HRESULT CDevice::InitD3d ()
{
	D3DDISPLAYMODE d3ddm;
	
	// DirectX オブジェクトの生成
	if( NULL == ( m_pDirect3D = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3Dの作成に失敗しました","",MB_OK);
		return E_FAIL;
	}

	// Display Mode の設定
	m_pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&m_d3dpp, sizeof ( m_d3dpp ));

	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.BackBufferCount  = 1;
	m_d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.Windowed		   = TRUE;

	if( FAILED( m_pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
										 D3DDEVTYPE_HAL,
										 *m_hWnd,
										 D3DCREATE_HARDWARE_VERTEXPROCESSING,
										 &m_d3dpp,
										 &m_pD3Device ) ) )
	{
		MessageBoxA(0,"HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します",NULL,MB_OK);
		if( FAILED( m_pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_REF,
											 *m_hWnd,
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											 &m_d3dpp,
											 &m_pD3Device ) ) )
		{
			MessageBoxA(0,"DIRECT3Dデバイスの作成に失敗しました",NULL,MB_OK);
				return E_FAIL;
		}    
	}

	return S_OK;
}

//ダイレクトインプットの初期化関数
HRESULT CDevice::InitDinput()
{
	HRESULT hr;
	
	//｢DirectInput｣オブジェクトの作成
	if(FAILED (hr = DirectInput8Create ( GetModuleHandle(NULL),
										 DIRECTINPUT_VERSION,
										 IID_IDirectInput8,
										 (VOID**)&m_pDinput,
										 NULL ) ) )
	{
		return hr;
	}
	//	キーボードデバイスのオブジェクトの作成
	if (FAILED (hr = InitKeyDevice () ) )
	{
		return hr;
	}
	
	//	マウスデバイスのオブジェクトの作成
	if (FAILED (hr = InitMouseDevice ( false ) ) )
	{
		return hr;
	}	

	return S_OK;
}


// キーデバイスオブジェクトの初期化
HRESULT CDevice::InitKeyDevice ()
{
	HRESULT hr;
	
	//｢DirectInputデバイス｣オブジェクトの作成(キーボード)
	if(FAILED (hr = m_pDinput->CreateDevice (	GUID_SysKeyboard,
											&m_pKeyDevice,
											NULL ) ) )
	{
		return hr;
	}
	//デバイスをキーボードに設定
	if(FAILED (hr = m_pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//協調レベルの設定		*当該アプリケーション(ゲーム)と、windowsOS自体のキーボードデバイスの占有率設定
	if(FAILED (hr = m_pKeyDevice->SetCooperativeLevel( *m_hWnd,
													 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )	// * 非排他でバック・グラウンド
	{
		return hr;
	}
	//デバイスを｢取得｣する
	m_pKeyDevice->Acquire();	// * 作成したデバイスへのアクセス権取得
	
	return S_OK;
}

//-----------------------------------------------------------------------------
// マウス用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT CDevice::InitMouseDevice ( bool bForeGroundMode )
{
	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	グローバルハンドル	
	
	//｢DirectInputデバイス｣オブジェクトの作成(マウス)
	if(FAILED (hr = m_pDinput->CreateDevice ( GUID_SysMouseEm,
											&m_pMouseDevice,
											NULL ) ) )
	{
		return hr;
	}

	//デバイスをマウスに設定
	if(FAILED (hr = m_pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// フォアグラウンドでマウスを使うなら
	{
		//	マウスの動作の設定
		if(FAILED (hr = m_pMouseDevice->SetCooperativeLevel( *m_hWnd,
														   DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		{
			return hr;
		}
	}
	else
	{
		//	マウスの動作の設定
		if(FAILED (hr = m_pMouseDevice->SetCooperativeLevel( *m_hWnd,
														   DISCL_EXCLUSIVE | DISCL_BACKGROUND ) ) )
		{
			/*return hr;*/
		}
	}

	//	イベント通知を使ってマウスの動作を検出する方法と、
	//	マウスからのバッファリング入力を読み取る
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	デバイス状態が変化したときに設定されるイベントを指定する
	if (FAILED ( hr = m_pMouseDevice->SetEventNotification ( hGlobal ) ) )
	{
		return hr;
	}

	DIPROPDWORD dipdw;
    // the header
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    // the data
    dipdw.dwData            = DIPROPAXISMODE_REL;

	//	デバイスの動作を定義するプロパティを設定する
	if (FAILED ( hr = m_pMouseDevice->SetProperty( DIPROP_BUFFERSIZE,
												 &dipdw.diph ) ) )
	{
		return hr;
	}

	//デバイスを｢取得｣する
	m_pMouseDevice->Acquire();	// * 作成したデバイスへのアクセス権取得
	
	return S_OK;
}

/*
	デストラクタ
*/
CDevice::~CDevice()
{
	FreeDx( true );
}

// 作成したDirectXオブジェクトの開放
//
void CDevice::FreeDx(bool _flag)
{		
	//	キーデバイスの解放
	if( m_pKeyDevice ) 
	{
		m_pKeyDevice->Unacquire();
	}
	//	マウスデバイスの解放
	if( m_pMouseDevice ) 
	{
		m_pMouseDevice->Unacquire();
	}
	
	SAFE_RELEASE( m_pKeyDevice );
	SAFE_RELEASE( m_pMouseDevice );
	SAFE_RELEASE( m_pDinput );

	if(_flag)
	{
		SAFE_RELEASE( m_pDirect3D );
		SAFE_RELEASE( m_pD3Device );
	}
}