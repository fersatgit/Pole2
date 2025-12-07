{$MINENUMSIZE 4}
{$ALIGN ON}
type
  D3DVALUE = Single;
  TD3DValue = D3DVALUE;
  PD3DValue = ^TD3DValue;
  REFERENCE_TIME = LONGLONG;
  TReferenceTime = REFERENCE_TIME;
  PReferenceTime = ^TReferenceTime;
  INT_PTR = Longint;
  UINT_PTR = LongWord;
  LONG_PTR = Longint;
  ULONG_PTR = LongWord;
  DWORD_PTR = LongWord;
  PINT_PTR = ^INT_PTR;
  PUINT_PTR = ^UINT_PTR;
  PLONG_PTR = ^LONG_PTR;
  PULONG_PTR = ^ULONG_PTR;
  PtrInt = Longint;
  PtrUInt = Longword;
  PPtrInt = ^PtrInt;
  PPtrUInt = ^PtrUInt;
  SIZE_T = ULONG_PTR;
  SSIZE_T = LONG_PTR;
  PSIZE_T = ^SIZE_T;
  PSSIZE_T = ^SSIZE_T;
  SizeInt = SSIZE_T;
  SizeUInt = SIZE_T;
  PSizeInt = PSSIZE_T;
  PSizeUInt = PSIZE_T;

  PWaveFormatEx = ^WaveFormatEx;
  WAVEFORMATEX = packed record
    wFormatTag: Word;         { format type }
    nChannels: Word;          { number of channels (i.e. mono, stereo, etc.) }
    nSamplesPerSec: DWORD;  { sample rate }
    nAvgBytesPerSec: DWORD; { for buffer estimation }
    nBlockAlign: Word;      { block size of data }
    wBitsPerSample: Word;   { number of bits per sample of mono data }
    cbSize: Word;           { the count in bytes of the size of }
  end;

const
  WAVE_FORMAT_PCM       = 1;
  _DXSDK_PRODUCT_MAJOR  = 9;
  _DXSDK_PRODUCT_MINOR  = 18;
  _DXSDK_BUILD_MAJOR    = 944;
  _DXSDK_BUILD_MINOR    = 0000;
  _FACDS = $878;

  MAKE_DSHRESULT_R     = (1 shl 31) or (_FACDS shl 16);
  CLSID_DirectSound: TGUID = '{47d4d946-62e8-11cf-93bc-444553540000}';
  DSDEVID_DefaultPlayback: TGUID = '{def00000-9c6d-47ed-aaf1-4dda8f2b5c03}';

type
  PDSCaps = ^TDSCaps;
  _DSCAPS = packed record
    dwSize                         : DWORD;
    dwFlags                        : DWORD;
    dwMinSecondarySampleRate       : DWORD;
    dwMaxSecondarySampleRate       : DWORD;
    dwPrimaryBuffers               : DWORD;
    dwMaxHwMixingAllBuffers        : DWORD;
    dwMaxHwMixingStaticBuffers     : DWORD;
    dwMaxHwMixingStreamingBuffers  : DWORD;
    dwFreeHwMixingAllBuffers       : DWORD;
    dwFreeHwMixingStaticBuffers    : DWORD;
    dwFreeHwMixingStreamingBuffers : DWORD;
    dwMaxHw3DAllBuffers            : DWORD;
    dwMaxHw3DStaticBuffers         : DWORD;
    dwMaxHw3DStreamingBuffers      : DWORD;
    dwFreeHw3DAllBuffers           : DWORD;
    dwFreeHw3DStaticBuffers        : DWORD;
    dwFreeHw3DStreamingBuffers     : DWORD;
    dwTotalHwMemBytes              : DWORD;
    dwFreeHwMemBytes               : DWORD;
    dwMaxContigFreeHwMemBytes      : DWORD;
    dwUnlockTransferRateHwBuffers  : DWORD;
    dwPlayCpuOverheadSwBuffers     : DWORD;
    dwReserved1                    : DWORD;
    dwReserved2                    : DWORD;
  end;
  DSCAPS = _DSCAPS;
  TDSCaps = _DSCAPS;

  PDSBcaps = ^TDSBcaps;
  _DSBCAPS = packed record
    dwSize                : DWORD;
    dwFlags               : DWORD;
    dwBufferBytes         : DWORD;
    dwUnlockTransferRate  : DWORD;
    dwPlayCpuOverhead     : DWORD;
  end;
  DSBCAPS = _DSBCAPS;
  TDSBcaps = _DSBCAPS;

  PDSBufferDesc = ^TDSBufferDesc;
  _DSBUFFERDESC = packed record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwReserved: DWORD;
    lpwfxFormat: PWaveFormatEx;
    guid3DAlgorithm: TGUID;
  end;
  DSBUFFERDESC = _DSBUFFERDESC;
  TDSBufferDesc = _DSBUFFERDESC;

  PDSCcaps = ^TDSCcaps;
  _DSCCAPS = packed record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwFormats: DWORD;
    dwChannels: DWORD;
  end;
  DSCCAPS = _DSCCAPS;
  TDSCcaps = _DSCCAPS;

  PDSCBCaps = ^TDSCBCaps;
  _DSCBCAPS = packed record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwBufferBytes: DWORD;
    dwReserved: DWORD;
  end;
  DSCBCAPS = _DSCBCAPS;
  TDSCBCaps = _DSCBCAPS;

  PDSBPositionNotify = ^TDSBPositionNotify;
  _DSBPOSITIONNOTIFY = packed record
    dwOffset: DWORD;
    hEventNotify: THandle;
  end;
  DSBPOSITIONNOTIFY = _DSBPOSITIONNOTIFY;
  TDSBPositionNotify = _DSBPOSITIONNOTIFY;

  IReferenceClock = interface(IUnknown)
    ['{56a86897-0ad4-11ce-b03a-0020af0ba770}']
    function GetTime(out pTime: TReferenceTime): HResult; stdcall;
    function AdviseTime(rtBaseTime, rtStreamTime: TReferenceTime; hEvent: THandle; out pdwAdviseCookie: DWORD): HResult; stdcall;
    function AdvisePeriodic(const rtStartTime, rtPeriodTime: TReferenceTime; hSemaphore: THandle; out pdwAdviseCookie: DWORD): HResult; stdcall;
    function Unadvise(dwAdviseCookie: DWORD): HResult; stdcall;
  end;
  IID_IReferenceClock = IReferenceClock;

  IDirectSoundBuffer = interface;

  IDirectSound = interface(IUnknown)
    ['{279AFA83-4981-11CE-A521-0020AF0BE560}']
    function CreateSoundBuffer(const pcDSBufferDesc: TDSBufferDesc; out ppDSBuffer: IDirectSoundBuffer; pUnkOuter: IUnknown): HResult; stdcall;
    function GetCaps(out pDSCaps: TDSCaps): HResult; stdcall;
    function DuplicateSoundBuffer(pDSBufferOriginal: IDirectSoundBuffer; out ppDSBufferDuplicate: IDirectSoundBuffer): HResult; stdcall;
    function SetCooperativeLevel(hwnd: HWND; dwLevel: DWORD): HResult; stdcall;
    function Compact: HResult; stdcall;
    function GetSpeakerConfig(out pdwSpeakerConfig: DWORD): HResult; stdcall;
    function SetSpeakerConfig(dwSpeakerConfig: DWORD): HResult; stdcall;
    function Initialize(pcGuidDevice: PGUID): HResult; stdcall;
  end;
  IID_IDirectSound = IDirectSound;

  IDirectSoundBuffer = interface(IUnknown)
    ['{279AFA85-4981-11CE-A521-0020AF0BE560}']
    function GetCaps(var pDSBufferCaps: TDSBcaps): HResult; stdcall;
    function GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor: PDWORD): HResult; stdcall;
    function GetFormat(pwfxFormat: PWaveFormatEx; dwSizeAllocated: DWORD; pdwSizeWritten: PDWORD): HResult; stdcall;
    function GetVolume(out plVolume: Longint): HResult; stdcall;
    function GetPan(out plPan: Longint): HResult; stdcall;
    function GetFrequency(out pdwFrequency: DWORD): HResult; stdcall;
    function GetStatus(out pdwStatus: DWORD): HResult; stdcall;
    function Initialize(pDirectSound: IDirectSound; const pcDSBufferDesc: TDSBufferDesc): HResult; stdcall;
    function Lock(dwOffset, dwBytes: DWORD; ppvAudioPtr1: PPointer; pdwAudioBytes1: PDWORD; ppvAudioPtr2: PPointer; pdwAudioBytes2: PDWORD; dwFlags: DWORD): HResult; stdcall;
    function Play(dwReserved1, dwPriority, dwFlags: DWORD): HResult; stdcall;
    function SetCurrentPosition(dwNewPosition: DWORD): HResult; stdcall;
    function SetFormat(pcfxFormat: PWaveFormatEx): HResult; stdcall;
    function SetVolume(lVolume: Longint): HResult; stdcall;
    function SetPan(lPan: Longint): HResult; stdcall;
    function SetFrequency(dwFrequency: DWORD): HResult; stdcall;
    function Stop: HResult; stdcall;
    function Unlock(pvAudioPtr1: Pointer; dwAudioBytes1: DWORD; pvAudioPtr2: Pointer; dwAudioBytes2: DWORD): HResult; stdcall;
    function Restore: HResult; stdcall;
  end;
  IID_IDirectSoundBuffer = IDirectSoundBuffer;

  IDirectSoundNotify = interface(IUnknown)
    ['{b0210783-89cd-11d0-af08-00a0c925cd16}']
    function SetNotificationPositions(dwPositionNotifies: DWORD; pcPositionNotifies: PDSBPositionNotify): HResult; stdcall;
  end;
  IID_IDirectSoundNotify = IDirectSoundNotify;

const
  DS_OK                           = S_OK;
  DS_NO_VIRTUALIZATION            = (0 shl 31) or (_FACDS shl 16) or 10; // MAKE_HRESULT(0, _FACDS, 10)
  DSERR_ALLOCATED                 = MAKE_DSHRESULT_R or 10; // MAKE_DSHRESULT(10)
  DSERR_CONTROLUNAVAIL            = MAKE_DSHRESULT_R or 30; // MAKE_DSHRESULT(30)
  DSERR_INVALIDPARAM              = E_INVALIDARG;
  DSERR_INVALIDCALL               = MAKE_DSHRESULT_R or 50; // MAKE_DSHRESULT(50)
  DSERR_GENERIC                   = E_FAIL;
  DSERR_PRIOLEVELNEEDED           = MAKE_DSHRESULT_R or 70; // MAKE_DSHRESULT(70)
  DSERR_OUTOFMEMORY               = E_OUTOFMEMORY;
  DSERR_BADFORMAT                 = MAKE_DSHRESULT_R or 100; // MAKE_DSHRESULT(100)
  DSERR_UNSUPPORTED               = E_NOTIMPL;
  DSERR_NODRIVER                  = MAKE_DSHRESULT_R or 120; // MAKE_DSHRESULT(120)
  DSERR_ALREADYINITIALIZED        = MAKE_DSHRESULT_R or 130; // MAKE_DSHRESULT(130)
  DSERR_NOAGGREGATION             = CLASS_E_NOAGGREGATION;
  DSERR_BUFFERLOST                = MAKE_DSHRESULT_R or 150; // MAKE_DSHRESULT(150)
  DSERR_OTHERAPPHASPRIO           = MAKE_DSHRESULT_R or 160; // MAKE_DSHRESULT(160)
  DSERR_UNINITIALIZED             = MAKE_DSHRESULT_R or 170; // MAKE_DSHRESULT(170)
  DSERR_NOINTERFACE               = E_NOINTERFACE;
  DSERR_ACCESSDENIED              = E_ACCESSDENIED;
  DSERR_BUFFERTOOSMALL            = MAKE_DSHRESULT_R or 180; // MAKE_DSHRESULT(180)
  DSERR_DS8_REQUIRED              = MAKE_DSHRESULT_R or 190; // MAKE_DSHRESULT(190)
  DSERR_SENDLOOP                  = MAKE_DSHRESULT_R or 200; // MAKE_DSHRESULT(200)
  DSERR_BADSENDBUFFERGUID         = MAKE_DSHRESULT_R or 210; // MAKE_DSHRESULT(210)
  DSERR_OBJECTNOTFOUND            = MAKE_DSHRESULT_R or 4449; // MAKE_DSHRESULT(4449)
  DSERR_FXUNAVAILABLE             = MAKE_DSHRESULT_R or 220; // MAKE_DSHRESULT(220)

  DSCAPS_PRIMARYMONO          = $00000001;
  DSCAPS_PRIMARYSTEREO        = $00000002;
  DSCAPS_PRIMARY8BIT          = $00000004;
  DSCAPS_PRIMARY16BIT         = $00000008;
  DSCAPS_CONTINUOUSRATE       = $00000010;
  DSCAPS_EMULDRIVER           = $00000020;
  DSCAPS_CERTIFIED            = $00000040;
  DSCAPS_SECONDARYMONO        = $00000100;
  DSCAPS_SECONDARYSTEREO      = $00000200;
  DSCAPS_SECONDARY8BIT        = $00000400;
  DSCAPS_SECONDARY16BIT       = $00000800;

  DSSCL_NORMAL                = $00000001;
  DSSCL_PRIORITY              = $00000002;
  DSSCL_EXCLUSIVE             = $00000003;
  DSSCL_WRITEPRIMARY          = $00000004;

  DSSPEAKER_DIRECTOUT         = $00000000;
  DSSPEAKER_HEADPHONE         = $00000001;
  DSSPEAKER_MONO              = $00000002;
  DSSPEAKER_QUAD              = $00000003;
  DSSPEAKER_STEREO            = $00000004;
  DSSPEAKER_SURROUND          = $00000005;
  DSSPEAKER_5POINT1           = $00000006;  // obsolete 5.1 setting
  DSSPEAKER_7POINT1           = $00000007;  // obsolete 7.1 setting
  DSSPEAKER_7POINT1_SURROUND  = $00000008;  // correct 7.1 Home Theater setting
  DSSPEAKER_7POINT1_WIDE      = DSSPEAKER_7POINT1;
  DSSPEAKER_5POINT1_SURROUND  = $00000009;  // correct 5.1 setting
  DSSPEAKER_5POINT1_BACK      = DSSPEAKER_5POINT1;
  DSSPEAKER_GEOMETRY_MIN      = $00000005;  //   5 degrees
  DSSPEAKER_GEOMETRY_NARROW   = $0000000A;  //  10 degrees
  DSSPEAKER_GEOMETRY_WIDE     = $00000014;  //  20 degrees
  DSSPEAKER_GEOMETRY_MAX      = $000000B4;  // 180 degrees
  DSBCAPS_PRIMARYBUFFER       = $00000001;
  DSBCAPS_STATIC              = $00000002;
  DSBCAPS_LOCHARDWARE         = $00000004;
  DSBCAPS_LOCSOFTWARE         = $00000008;
  DSBCAPS_CTRL3D              = $00000010;
  DSBCAPS_CTRLFREQUENCY       = $00000020;
  DSBCAPS_CTRLPAN             = $00000040;
  DSBCAPS_CTRLVOLUME          = $00000080;
  DSBCAPS_CTRLPOSITIONNOTIFY  = $00000100;
  DSBCAPS_CTRLFX              = $00000200;
  DSBCAPS_STICKYFOCUS         = $00004000;
  DSBCAPS_GLOBALFOCUS         = $00008000;
  DSBCAPS_GETCURRENTPOSITION2 = $00010000;
  DSBCAPS_MUTE3DATMAXDISTANCE = $00020000;
  DSBCAPS_LOCDEFER            = $00040000;
  DSBCAPS_TRUEPLAYPOSITION    = $00080000;

  DSBPLAY_LOOPING             = $00000001;
  DSBPLAY_LOCHARDWARE         = $00000002;
  DSBPLAY_LOCSOFTWARE         = $00000004;
  DSBPLAY_TERMINATEBY_TIME    = $00000008;
  DSBPLAY_TERMINATEBY_DISTANCE    = $000000010;
  DSBPLAY_TERMINATEBY_PRIORITY    = $000000020;

  DSBSTATUS_PLAYING           = $00000001;
  DSBSTATUS_BUFFERLOST        = $00000002;
  DSBSTATUS_LOOPING           = $00000004;
  DSBSTATUS_LOCHARDWARE       = $00000008;
  DSBSTATUS_LOCSOFTWARE       = $00000010;
  DSBSTATUS_TERMINATED        = $00000020;

  DSBLOCK_FROMWRITECURSOR     = $00000001;
  DSBLOCK_ENTIREBUFFER        = $00000002;

  DSBFREQUENCY_ORIGINAL       = 0;
  DSBFREQUENCY_MIN            = 100;
  DSBFREQUENCY_MAX            = 200000;

  DSBPAN_LEFT                 = -10000;
  DSBPAN_CENTER               = 0;
  DSBPAN_RIGHT                = 10000;

  DSBVOLUME_MIN               = -10000;
  DSBVOLUME_MAX               = 0;

  DSBSIZE_MIN                 = 4;
  DSBSIZE_MAX                 = $0FFFFFFF;
  DSBSIZE_FX_MIN              = 150;  // NOTE: Milliseconds, not bytes

  DSBNOTIFICATIONS_MAX        = 100000;

  DS3DMODE_NORMAL             = $00000000;
  DS3DMODE_HEADRELATIVE       = $00000001;
  DS3DMODE_DISABLE            = $00000002;

  DS3D_IMMEDIATE              = $00000000;
  DS3D_DEFERRED               = $00000001;

var
  // Forced to define as 'var' cos pascal compiler treats all consts as Double
  DS3D_MINDISTANCEFACTOR: Single = 1.175494351e-38; // FLT_MIN;
  {$EXTERNALSYM DS3D_MINDISTANCEFACTOR}
  DS3D_MAXDISTANCEFACTOR: Single = 3.402823466e+38; // FLT_MAX;
  {$EXTERNALSYM DS3D_MAXDISTANCEFACTOR}
const
  DSCBLOCK_ENTIREBUFFER       = $00000001;
  DSCBSTATUS_CAPTURING        = $00000001;
  DSCBSTATUS_LOOPING          = $00000002;
  DSCBSTART_LOOPING           = $00000001;
  DSBPN_OFFSETSTOP            = $FFFFFFFF;
  DS_CERTIFIED                = $00000000;
  DS_UNCERTIFIED              = $00000001;

type
  TDSEnumCallbackA = function(lpGuid: PGUID; lpcstrDescription, lpcstrModule: PAnsiChar;lpContext: Pointer): BOOL; stdcall;
  TDSEnumCallbackW = function(lpGuid: PGUID; lpcstrDescription, lpcstrModule: PWideChar;lpContext: Pointer): BOOL; stdcall;
  TDSEnumCallback = TDSEnumCallbackA;

function DirectSoundCreate(lpGuid: PGUID; out ppDS: IDirectSound; pUnkOuter: IUnknown): HResult; stdcall; external 'dsound.dll';
