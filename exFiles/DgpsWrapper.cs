
using System;
using System.Runtime.InteropServices;

public class DgpsWrapper : IDisposable {
	const String DLL_LOCATION = "libdgps";

	[DllImport (DLL_LOCATION)]
	private static extern IntPtr DgpsCreateObject(string confFilePath);

	[DllImport (DLL_LOCATION)]
	private static extern void DgpsDeleteObject(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void DgpsSendBestPosData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void DgpsSendBestVelData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void DgpsSetPosition(IntPtr pObj, double latitude, double longitude, double altitude);
	
	[DllImport (DLL_LOCATION)]
	private static extern void DgpsSetVelocities(IntPtr pObj, double latSpeed, double longSpeed, double altAzimuth);

	[DllImport (DLL_LOCATION)]
	private static extern void DgpsSetTimeStamp(IntPtr pObj, float timeStamp);

	private IntPtr m_nativeObject;

	public DgpsWrapper(string confFilePath) {
		this.m_nativeObject = CreateDgpsObject(confFilePath);
	}

	~DgpsWrapper() {Dispose(false);}
	
	public void Dispose() { Dispose(true);}

    protected virtual void Dispose(bool bDisposing) {
        if (this.m_nativeObject != IntPtr.Zero) {
            DgpsCreateObject(this.m_nativeObject);
            this.m_nativeObject = IntPtr.Zero;
        }

        if (bDisposing) {
            GC.SuppressFinalize(this);
        }
    }

	public void SetPosition(double latitude, double longitude, double altitude) {
		DgpsSetPosition(this.m_nativeObject, latitude, longitude, altitude);
	}

	public void SetVelocities(double latSpeed, double longSpeed, double altAzimuth) {
		DgpsSetVelocities(this.m_nativeObject, latSpeed, longSpeed, altAzimuth);
	}

	public void SetTimeStamp(float timeStamp) {
		DgpsSetTimeStamp(this.m_nativeObject, timeStamp);
	}

	public void SendBestPosData() {
		DgpsSendBestPosData(this.m_nativeObject);
	}

	public void SendBestVelData() {
		DgpsSendBestVelData(this.m_nativeObject);
	}
}