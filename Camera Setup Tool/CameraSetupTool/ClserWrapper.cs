/***********************************************************************************************************************
 * Module Name:  	CLSERWRAPPER.cs
 * Project:     	Camera Setup Tool for IPA subsystem (ISU-IPA)
 *
 * Purpose:			This file implements a wrapper for the functions that facilitates the 
 *                  serial communication with cameras over the cameralink interface.
 *                  The functions can be used to query information such as camera manufacturer, 
 *                  camera model, camera type (mono or color) etc.
/**********************************************************************************************************************/

using System;
using System.Runtime.InteropServices;

namespace CameraSetupTool
{
    /// <summary>
    /// Represents the wrapper class for the functions required for serial communication
    /// with camera over the camera link interface. 
    /// </summary>
    /// <remarks></remarks>
    public class ClserWrapper
    {

        public const string FileNameClserDll = ".\\clsersis.dll";
        //   public static string FileNameClserDll = System.Environment.GetEnvironmentVariable("SISODIR5") + "\\bin\\clsersis.dll";

        public const int CL_BAUDRATE_115200 = 16;
        public const int CL_BAUDRATE_19200 = 2;
        public const int CL_BAUDRATE_230400 = 32;
        public const int CL_BAUDRATE_38400 = 4;
        public const int CL_BAUDRATE_460800 = 64;
        public const int CL_BAUDRATE_57600 = 8;
        public const int CL_BAUDRATE_921600 = 128;
        public const int CL_BAUDRATE_9600 = 1;
        /// <summary>
        /// This Camera Link library conforms to the October 2000 version of the Camera Link Specifications 
        /// </summary>
        public const int CL_DLL_VERSION_1_0 = 2;
        /// <summary>
        /// This Camera Link library conforms to the November 2002 version of the Camera Link Specifications 
        /// </summary>
        public const int CL_DLL_VERSION_1_1 = 3;
        /// <summary>
        /// This library is not a valid Camera Link library 
        /// </summary>
        public const int CL_DLL_VERSION_NO_VERSION = 1;
        /// <summary>
        /// Requested baud rate not supported by this interface. 
        /// </summary>
        public const int CL_ERR_BAUD_RATE_NOT_SUPPORTED = -10008;
        /// <summary>
        /// User buffer not large enough to hold data. 
        /// </summary>
        public const int CL_ERR_BUFFER_TOO_SMALL = -10001;
        /// <summary>
        /// Could not find the error description for this error code. 
        /// </summary>
        public const int CL_ERR_ERROR_NOT_FOUND = -10007;
        /// <summary>
        /// Function does not exist in the manufacturer's library. 
        /// </summary>
        public const int CL_ERR_FUNCTION_NOT_FOUND = -10099;
        /// <summary>
        /// Not a valid index. 
        /// </summary>
        public const int CL_ERR_INVALID_INDEX = -10005;
        /// <summary>
        /// The serial reference is not valid. 
        /// </summary>
        public const int CL_ERR_INVALID_REFERENCE = -10006;
        /// <summary>
        /// The requested manufacturer's DLL does not exist on your system. 
        /// </summary>
        public const int CL_ERR_MANU_DOES_NOT_EXIST = -10002;
        /// <summary>
        /// Function returned successfully. 
        /// </summary>
        public const int CL_ERR_NO_ERR = 0;
        /// <summary>
        /// System is out of memory and could not perform required actions. 
        /// </summary>
        public const int CL_ERR_OUT_OF_MEMORY = -10009;
        /// <summary>
        /// Port is valid but cannot be opened because it is in use. 
        /// </summary>
        public const int CL_ERR_PORT_IN_USE = -10003;
        /// <summary>
        /// Operation not completed within specified timeout period. 
        /// </summary>
        public const int CL_ERR_TIMEOUT = -10004;
        /// <summary>
        /// The DLL was unable to load due to a lack of memory or because it does not export all required functions.
        /// </summary>
        public const int CL_ERR_UNABLE_TO_LOAD_DLL = -10098;
        public const int CL_OK = 0;

        /// <summary>
        /// discards any bytes that are available in the input buffer
        /// </summary>
        /// <param name="serialCommRef">The serial communication reference obtained from clSerialInit() 
        /// that describes the port to be flushed.</param>
        /// <returns></returns>
        [DllImport(FileNameClserDll)]
        public static extern int clFlushPort(IntPtr serialCommRef);

        /// <summary>
        /// converts an error code to error text for display in a dialog box or in a standard I/O window.
        /// </summary>
        /// <param name="errorCode">The error code used to find the appropriate error text</param>
        /// <param name="errorText">A caller-allocated buffer which contains the NULL-terminated error text 
        /// on function return</param>
        /// <param name="errorTextSize">On success, contains the number of bytes written into the buffer, 
        /// including the NULL-termination character. This value should be the size in bytes of the error text buffer 
        /// passed in. On CL_ERR_BUFFER_TOO_SMALL, contains the size of the buffer needed to write the error text</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	            the error text has been written into errorText 
        /// 	CL_ERR_BUFFER_TOO_SMALL 	errorText is too small to contain the error message, 
        /// 	                            it needs to be scaled to the value written into errorTextSize
        ///     CL_ERR_ERROR_NOT_FOUND 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetErrorText(int errorCode, IntPtr errorText, ref uint errorTextSize);

        /// <summary>
        /// Gets the name of the frame grabber manufacturer who created the DLL and 
        /// the version of the Camera Link specifications with which the DLL complies
        /// </summary>
        /// <param name="manufacturerName">A pointer to a user-allocated buffer into which the function copies the 
        /// manufacturer name. The returned name is NULL-terminated. </param>
        /// <param name="bufferSize">	As an input, this value should be the size of the buffer that is passed. 
        /// On successful return, this parameter contains the number of bytes written into the buffer, including the 
        /// NULL termination character. On CL_ERR_BUFFER_TOO_SMALL, this parameter contains the size of the buffer 
        /// needed to write the data text. </param>
        /// <param name="version">A constant stating the version of the Camera Link specifications with which 
        /// this DLL complies.</param>
        /// <returns>
        /// 	CL_ERR_BUFFER_TOO_SMALL 	manufacturerName is too small to contain the manufacturer name, 
        /// 	                            it needs to be scaled to the value written into bufferSize.
        ///     CL_ERR_NO_ERR 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetManufacturerInfo(IntPtr manufacturerName, ref uint bufferSize, out uint version);

        /// <summary>
        /// Gets the number of bytes that are received at the port specified by serialRef but are not yet read out.
        /// </summary>
        /// <param name="serialCommRef">The serial communication reference obtained from clSerialInit() 
        /// that describes the port</param>
        /// <param name="numBytes">The number of bytes currently available to be read from the port.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetNumBytesAvail(IntPtr serialCommRef, out uint numBytes);

        /// <summary>
        /// Returns the number of serial ports in your system from a specific manufacturer. 
        /// </summary>
        /// <param name="numSerialPorts">The number of serial ports in the system that can be accessed 
        /// with the current DLL</param>
        /// <returns>   CL_ERR_NO_ERR 	</returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetNumSerialPorts(out uint numSerialPorts);

        /// <summary>
        /// Returns a manufacturer-specific identifier for each serial port in the system.
        /// This returns a string which contains the board and port indexes that are used by
        /// Silicon Software framegrabber SDK (e.g. function Fg_InitEx()).
        /// </summary>
        /// <param name="serialIndex">A zero-based index value. The valid range for serialIndex is 0 to (n-1), 
        /// where n is the value of numSerialPorts, as returned by clGetNumSerialPorts(). </param>
        /// <param name="portID">Manufacturer-specific identifier for the serial port </param>
        /// <param name="portIDSize">As an input, this value should be the size of the buffer that is passed. 
        /// On successful return, this parameter contains the number of bytes written into the buffer, including the 
        /// NULL termination character. On CL_ERR_BUFFER_TOO_SMALL, this parameter contains the size of the buffer 
        /// needed to write the data text.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_INDEX 	
        ///     CL_ERR_BUFFER_TOO_SMALL 	portID is too small to contain the port identification string, 
        ///                                 it needs to be scaled to the value written into bufferSize.
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetSerialPortIdentifier(uint serialIndex, IntPtr portID, ref uint portIDSize);

        /// <summary>
        /// Returns the valid baud rates of the current interface. 
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit() 
        /// which describes the port being queried for baud rates.</param>
        /// <param name="baudRates">Bitfield that describes all supported baud rates of the serial port as 
        /// described by serialRefPtr.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clGetSupportedBaudRates(IntPtr serialRef, out uint[] baudRates);

        /// <summary>
        /// closes the serial device and cleans up the resources associated with serialRef.
        /// Upon return, serialRef is no longer usable.
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().</param>
        [DllImport(FileNameClserDll)]
        public static extern void clSerialClose(IntPtr serialRef);

        /// <summary>
        /// Initializes the device referred to by serialIndex and returns a pointer to an 
        /// internal serial reference structure. 
        /// </summary>
        /// <param name="serialIndex">A zero-based index value. For n serial devices in the system supported by this
        /// library, serialIndex has a range of 0 to (n-1).</param>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().
        /// On a successful call, points to a value that contains a pointer to the vendor-specific reference to 
        /// the current session.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_PORT_IN_USE 	
        ///     CL_ERR_INVALID_INDEX 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clSerialInit(uint serialIndex, ref IntPtr serialRef);

        /// <summary>
        /// Reads numBytes from the serial device referred to by serialRef. 
        /// clSerialRead() will return when numBytes are available at the serial port or when the 
        /// serialTimeout period has passed. Upon success, numBytes are copied into buffer. In the case of any error, 
        /// including CL_ERR_TIMEOUT, no data is copied into buffer.
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().</param>
        /// <param name="buffer">Points to a user-allocated buffer. Upon a successful call, buffer contains 
        /// the data read from the serial device. Upon failure, this buffer is not affected. Caller should ensure that 
        /// buffer is at least numBytes in size. </param>
        /// <param name="numBytes">The number of bytes requested by the caller. </param>
        /// <param name="serialTimeout">Indicates the timeout in milliseconds.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        ///     CL_ERR_TIMEOUT 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clSerialRead(IntPtr serialRef, IntPtr buffer, ref uint numBytes, uint serialTimeout);

        /// <summary>
        /// Writes the data in the buffer to the serial device referenced by serialRef. 
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().</param>
        /// <param name="buffer">Contains data to write to the serial port
        /// Note: The type of the input buffer is defined to be "char *" by the CameraLink specification. 
        /// The Silicon Software implementation guarantees to never modify this data, in fact it will cast the 
        /// input pointer to a "const char *" immediately. So it is fine to pass in arbitrary constant data that is 
        /// casted to "char *" to satisfy this interface.
        /// </param>
        /// <param name="bufferSize">Contains the buffer size indicating the maximum number of bytes to be written. 
        /// Upon a successful call, bufferSize contains the number of bytes written to the serial device. </param>
        /// <param name="serialTimeOut">Indicates the timeout in milliseconds.</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        ///     CL_ERR_TIMEOUT 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clSerialWrite(IntPtr serialRef, byte[] buffer, ref uint bufferSize, uint serialTimeOut);

        /// <summary>
        /// Sets the baud rate for the serial port of the selected device. 
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().</param>
        /// <param name="baudRate">	The baud rate that shall be used. 
        /// This parameter expects the values represented by the CL_BAUDRATE constants. </param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        ///     CL_ERR_BAUD_RATE_NOT_SUPPORTED 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clSetBaudRate(IntPtr serialRef, uint baudRate);

        /// <summary>
        /// Sets the parity for the serial port of the selected device.
        /// </summary>
        /// <param name="serialRef">The serial communication reference obtained from clSerialInit().</param>
        /// <param name="parityOn">The parity that shall be used</param>
        /// <returns>
        /// 	CL_ERR_NO_ERR 	
        ///     CL_ERR_INVALID_REFERENCE 	
        /// </returns>
        [DllImport(FileNameClserDll)]
        public static extern int clSetParity(IntPtr serialRef, uint parityOn);
    }
}
