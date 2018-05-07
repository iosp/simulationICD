
using System;
using System.Runtime.InteropServices;

public class VelodyneWrapper : IDisposable {
	const String DLL_LOCATION = "libvlp";

	[DllImport (DLL_LOCATION)]
	private static extern IntPtr VLPCreateObject(string confFilePath);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPDeleteObject(IntPtr pVlp);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPSetAzimuth(IntPtr pVlp, double azimuth);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPSetTimeStamp(IntPtr pVlp, float timeStamp);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPSetChannel(IntPtr pVlp, double distance, short reflectivity);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPCloseBlock(IntPtr pVlp);

	[DllImport (DLL_LOCATION)]
	private static extern void VLPSendData(IntPtr pVlp);

	private IntPtr m_nativeObject;

	public VelodyneWrapper(string confFilePath) {
			this.m_nativeObject = VLPCreateObject(confFilePath);
	}

	~VelodyneWrapper() {Dispose(false);}
	
	public void Dispose() { Dispose(true);}

    protected virtual void Dispose(bool bDisposing) {
        if (this.m_nativeObject != IntPtr.Zero) {
            VLPDeleteObject(this.m_nativeObject);
            this.m_nativeObject = IntPtr.Zero;
        }

        if (bDisposing) {
            GC.SuppressFinalize(this);
        }
    }

	public void SetAzimuth(double azimuth) {
		VLPSetAzimuth(this.m_nativeObject, azimuth);
	}

	public void SetTimeStamp(float timeStamp) {
		VLPSetTimeStamp(this.m_nativeObject, timeStamp);
	}

	public void SetChannel(double distance, short reflectivity) {
		VLPSetChannel(this.m_nativeObject, distance, reflectivity);
	}

	public void CloseBlock() {
		VLPCloseBlock(this.m_nativeObject);
	}

	public void SendData() {
		VLPSendData(this.m_nativeObject);
	}
}