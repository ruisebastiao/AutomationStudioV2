//==========================================================================//
//                                                                          //
//	C# - Interfaceclass for uEye_tools                                      //
//                                                                          //
//  Copyright (C) 2005 - 2017                                                //
//  IDS - Imaging Development Systems GmbH                                  //
//  Dimbacherstr. 6-8                                                       //
//  D-74182 Obersulm-Willsbach                                              //
//                                                                          //
//  The information in this document is subject to change without           //
//  notice and should not be construed as a commitment by IDS Imaging GmbH. //
//  IDS Imaging GmbH does not assume any responsibility for any errors      //
//  that may appear in this document.                                       //
//                                                                          //
//  This document, or source code, is provided solely as an example         //
//  of how to utilize IDS software libraries in a sample application.       //
//  IDS Imaging GmbH does not assume any responsibility for the use or      //
//  reliability of any portion of this document or the described software.  //
//                                                                          //
//  General permission to copy or modify, but not for profit, is hereby     //
//  granted,  provided that the above copyright notice is included and      //
//  included and reference made to the fact that reproduction privileges    //
//  were granted by IDS Imaging GmbH.                                       //
//                                                                          //
//  IDS cannot assume any responsibility for the use, or misuse, of any     //
//  portion or misuse, of any portion of this software for other than its   //
//  intended diagnostic purpose in calibrating and testing IDS manufactured //
//  image processing boards and software.                                   //
//                                                                          //
//==========================================================================//


using System;
using System.Runtime.InteropServices;


using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Text;



/// <summary>
/// Zusammenfassung für uEye_tools.
/// </summary>
public class uEye_tools
{
	
    // ----------------------------------------Driver name-----------------------------------------
    //
	public const string DRIVER_DLL_NAME = "ueye_tools.dll";


    // ----------------------------------------Color modes-----------------------------------------
    //
    public const Int32 IS_AVI_CM_RGB32 =    0;	// RGB32
    public const Int32 IS_AVI_CM_RGB24	=	1;	// RGB24
    public const Int32 IS_AVI_CM_Y8		= 6;	// Y8
    public const Int32 IS_AVI_CM_BAYER	=	11;	// Bayer

	// ----------------------------------------Events-----------------------------------------
	//
	public const Int32 IS_AVI_SET_EVENT_FRAME_SAVED = 1;

    // **********************************************
	// return values/error codes
    // **********************************************
    
    public const Int32 IS_AVI_NO_ERR                  =   0   ;
	public const Int32 IS_AVI_ERR_INVALID_FILE        =   301 ;
    public const Int32 IS_AVI_ERR_NEW_FAILED          =   302  ;
    public const Int32 IS_AVI_ERR_CREATESTREAM        =   303  ;
    public const Int32 IS_AVI_ERR_PARAMETER           =   304  ;
    public const Int32 IS_AVI_ERR_NO_CODEC_AVAIL      =   305  ;
    public const Int32 IS_AVI_ERR_INVALID_ID          =   306  ;
    public const Int32 IS_AVI_ERR_COMPRESS            =   307  ;
    public const Int32 IS_AVI_ERR_DECOMPRESS          =   308  ;
    public const Int32 IS_AVI_ERR_CAPTURE_RUNNING     =   309  ;
    public const Int32 IS_AVI_ERR_CAPTURE_NOT_RUNNING =   310  ;
    public const Int32 IS_AVI_ERR_PLAY_RUNNING        =   311  ;
    public const Int32 IS_AVI_ERR_PLAY_NOT_RUNNING    =   312  ;
    public const Int32 IS_AVI_ERR_WRITE_INFO          =   313  ;
    public const Int32 IS_AVI_ERR_INVALID_VALUE       =   314  ;
    public const Int32 IS_AVI_ERR_ALLOC_MEMORY        =   315  ;
    public const Int32 IS_AVI_ERR_INVALID_CM          =   316  ;
    public const Int32 IS_AVI_ERR_COMPRESSION_RUN     =   317  ;
	public const Int32 IS_AVI_ERR_INVALID_SIZE		=   318  ;
    public const Int32 IS_AVI_ERR_INVALID_POSITION    =   319  ;
    public const Int32 IS_AVI_ERR_INVALID_UEYE        =   320  ;
    public const Int32 IS_AVI_ERR_EVENT_FAILED        =   321  ;
	

	// ***********************************************
	// exports from uEye_tools.dll
	// ***********************************************	
     
	[DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_InitAVI",CallingConvention=CallingConvention.StdCall)]				// isavi_InitAVI)			(INT* pnAviID,HANDLE hf);
	private static extern Int32 isavi_InitAVI(ref Int32 pnAviID,Int32 hu);	

    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_ExitAVI",CallingConvention=CallingConvention.StdCall)]				//isavi_ExitAVI)			(INT nAviID);
    private static extern Int32 isavi_ExitAVI (Int32 nAviID); 
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_OpenAVI",CallingConvention=CallingConvention.StdCall)]				//isavi_OpenAVI)			(INT nAviID, const char* strFileName);
    private static extern Int32 isavi_OpenAVI (Int32 nAviID, byte[] strFileName);  
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_StartAVI",CallingConvention=CallingConvention.StdCall)]			// isavi_StartAVI)			(INT nAviID);
    private static extern Int32 isavi_StartAVI (Int32 nAviID);
		
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_StopAVI",CallingConvention=CallingConvention.StdCall)]				// isavi_StopAVI)			(INT nAviID);
    private static extern Int32 isavi_StopAVI (Int32 nAviID);  
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_AddFrame",CallingConvention=CallingConvention.StdCall)]				// isavi_AddFrame  (INT nAviID,char *pcImageMem);
    private static extern Int32 isavi_AddFrame (Int32 nAviID, IntPtr pcImageMem);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_SetFrameRate",CallingConvention=CallingConvention.StdCall)]					// isavi_SetFrameRate (INT nAviID,double fr);
    private static extern Int32 isavi_SetFrameRate (Int32 nAviID,double fr);
	
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_SetImageQuality",CallingConvention=CallingConvention.StdCall)]				// isavi_SetImageQuality (INT nAviID,Int32 q);
    private static extern Int32 isavi_SetImageQuality (Int32 nAviID,Int32 q);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_GetAVISize",CallingConvention=CallingConvention.StdCall)]				// isavi_GetAVISize (INT nAviID,Single *size);
    private static extern Int32 isavi_GetAVISize(Int32 nAviID,ref Single size);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_GetAVIFileName",CallingConvention=CallingConvention.StdCall)]				// isavi_GetAVIFileName (INT nAviID, char* strName);
    private static extern Int32 isavi_GetAVIFileName (Int32 nAviID, byte[] strName);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_SetImageSize",CallingConvention=CallingConvention.StdCall)]				// isavi_SetImageSize)		(INT nAviID,INT cMode, Int32 Width, Int32 Height, Int32 PosX, Int32 PosY, Int32 LineOffset);
    private static extern Int32 isavi_SetImageSize (Int32 nAviID,Int32 cMode, Int32 Width, Int32 Height, Int32 PosX, Int32 PosY, Int32 LineOffset);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_GetnCompressedFrames",CallingConvention=CallingConvention.StdCall)]			// isavi_GetnCompressedFrames (INT nAviID,unsigned Int32 *nFrames);
    private static extern Int32 isavi_GetnCompressedFrames  (Int32 nAviID,ref UInt32 nFrames);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_GetnLostFrames",CallingConvention=CallingConvention.StdCall)]			// isavi_GetnLostFrames (INT nAviID,unsigned Int32 *nLostFrames);
    private static extern Int32 isavi_GetnLostFrames (Int32 nAviID,ref UInt32 nLostFrames);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_ResetFrameCounters",CallingConvention=CallingConvention.StdCall)]			// isavi_ResetFrameCounters (INT nAviID);
    private static extern Int32 isavi_ResetFrameCounters (Int32 nAviID);
		
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_CloseAVI",CallingConvention=CallingConvention.StdCall)]		// isavi_CloseAVI (INT nAviID);
    private static extern Int32 isavi_CloseAVI (Int32 nAviID);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_InitEvent",CallingConvention=CallingConvention.StdCall)]				// isavi_InitEvent (INT nAviID, HANDLE hEv, INT which);
    private static extern Int32 isavi_InitEvent (Int32 nAviID, Int32 hEv, Int32 which);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_EnableEvent",CallingConvention=CallingConvention.StdCall)]				// isavi_EnableEvent (INT nAviID, INT which);
    private static extern Int32 isavi_EnableEvent (Int32 nAviID, Int32 which);
    
    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_DisableEvent",CallingConvention=CallingConvention.StdCall)]			// isavi_DisableEvent (INT nAviID, INT which);
    private static extern Int32 isavi_DisableEvent (Int32 nAviID, Int32 which);

    [DllImport(DRIVER_DLL_NAME ,EntryPoint="isavi_ExitEvent",CallingConvention=CallingConvention.StdCall)]			// isavi_ExitEvent (INT nAviID, INT which);
    private static extern Int32 isavi_ExitEvent (Int32 nAviID, Int32 which);	
 
	// internal variables
	private Int32 m_hAvi;		// internal avi container handle

	// constructor
	public uEye_tools()
	{
		m_hAvi = 0;
	}
    
	//********************************************************************************************
	// Helper functions
	//********************************************************************************************

	// ------------------------------ GetStringFromByte  --------------------------
	//
	private string GetStringFromByte(byte[] pByte, Int32 nStart, Int32 nLength )
	{
		Int32 i=0;
		char[] pChars = new char[nLength];
		for ( i=0; i<nLength; i++)
		{
			pChars[i] = Convert.ToChar(pByte[nStart+i]);
		}
		string strResult = new string(pChars);
		return strResult;
	}


	// -------------------------  IsuEyeOpen  -----------------
	//
	public bool IsOpen()
	{
		if ( m_hAvi == 0 )
			return false;
		else
			return true;
	}


	//*************************************************************************
	// Function wrappers
	//*************************************************************************

	// ---------------------  init avi---------------------
	//
    
	public Int32 InitAVI(Int32  hu )
	{
		Int32 ret = 0;
		Int32 AviID = 0;
        
		ret = isavi_InitAVI(ref AviID, hu);
		if ( ret == IS_AVI_NO_ERR )
			m_hAvi = AviID;

		return ret;
	}

   	// ---------------------  ExitAvi -----------------------
	//
	public Int32 ExitAVI()
	{
		Int32 ret = 0;
		ret = isavi_ExitAVI(m_hAvi);
		if ( ret == IS_AVI_NO_ERR )
			m_hAvi = 0;
		
		return ret;
	}

	// ---------------------  OPenAvi -----------------------
	//
	public Int32 OpenAVI( byte[] strFileName)
	{
		Int32 ret = 0;
		
		ret = isavi_OpenAVI (m_hAvi, strFileName); 
				
		return ret;
	}

	// ---------------------  StartAvi -----------------------
	//
	public Int32 StartAVI()
	{
		Int32 ret = 0;
		
		ret = isavi_StartAVI (m_hAvi);
				
		return ret;
	}

	// ---------------------  StopAvi -----------------------
	//
	public Int32 StopAVI()
	{
		Int32 ret = 0;
		
		ret = isavi_StopAVI (m_hAvi);
				
		return ret;
	}

	// ---------------------  CloseAVI  -----------------------
	//
	public Int32 CloseAVI ()
	{
		Int32 ret = 0;
		
		ret = isavi_CloseAVI (m_hAvi);
				
		return ret;
	}

	
	// ---------------------  AddFrame -----------------------
	//
	public Int32 AddFrame(IntPtr pcImageMem)
	{
		Int32 ret = 0;
		
		ret = isavi_AddFrame (m_hAvi, pcImageMem);
				
		return ret;
	}

	// ---------------------  SetFrameRate -----------------------
	//
	public Int32 SetFrameRate(double fr)
	{
		Int32 ret = 0;
		
		ret = isavi_SetFrameRate (m_hAvi, fr); 
				
		return ret;
	}


	// ---------------------  SetImageQuality -----------------------
	//
	public Int32 SetImageQuality(Int32 q)
	{
		Int32 ret = 0;
		
		ret = isavi_SetImageQuality (m_hAvi, q); 
				
		return ret;
	}

	// ---------------------  GetAVISize -----------------------
	//
	public Int32 GetAVISize(ref Single size)
	{
		Int32 ret = 0;
		
		ret = isavi_GetAVISize (m_hAvi,ref size); 
				
		return ret;
	}

	// ---------------------  GetAVIFileName -----------------------
	//
	public Int32 GetAVIFileName(byte[] strFileName)
	{
		Int32 ret = 0;
		
		ret = isavi_GetAVIFileName (m_hAvi,strFileName); 
				
		return ret;
	}

	// ---------------------  SetImageSize -----------------------
	//
	public Int32 SetImageSize(Int32 cMode, Int32 Width, Int32 Height, Int32 PosX, Int32 PosY, Int32 LineOffset)
	{
		Int32 ret = 0;
		
		ret = isavi_SetImageSize (m_hAvi, cMode, Width, Height, PosX, PosY, LineOffset);
				
		return ret;
	}

	// ---------------------  GetnCompressedFrames -----------------------
	//
	public Int32 GetnCompressedFrames(ref UInt32 nFrames)
	{
		Int32 ret = 0;
		
		ret = isavi_GetnCompressedFrames (m_hAvi,ref nFrames);
				
		return ret;
	}

	// ---------------------  GetnLostFrames -----------------------
	//
	public Int32 GetnLostFrames(ref UInt32 nLostFrames)
	{
		Int32 ret = 0;
		
		ret = isavi_GetnLostFrames (m_hAvi,ref nLostFrames);
				
		return ret;
	}

	// ---------------------  ResetFrameCounters -----------------------
	//
	public Int32 ResetFrameCounters()
	{
		Int32 ret = 0;
		
		ret = isavi_ResetFrameCounters (m_hAvi);
				
		return ret;
	}


	// ---------------------  InitEvent  -----------------------
	//
	public int InitEvent(Int32 hEv, Int32 which)
	{
		Int32 ret = 0;
		ret = isavi_InitEvent( m_hAvi, hEv, which );

		return ret;
	}

	// ---------------------  EnableEvent -----------------------
	//
	public Int32 EnableEvent(Int32 which)
	{
		Int32 ret = 0;
		
		ret = isavi_EnableEvent (m_hAvi,which);
				
		return ret;
	}

	// ---------------------  DisableEvent -----------------------
	//
	public Int32 DisableEvent(Int32 which)
	{
		Int32 ret = 0;
		
		ret = isavi_DisableEvent (m_hAvi,which);
				
		return ret;
	}

	// ---------------------  ExitEvent -----------------------
	//
	public Int32 ExitEvent(Int32 which)
	{
		Int32 ret = 0;
		
		ret = isavi_ExitEvent (m_hAvi,which);
				
		return ret;
	}

}



