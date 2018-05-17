
using System;
using System.Runtime.InteropServices;

public class InsWrapper : IDisposable {
	const String DLL_LOCATION = "libins";

	[DllImport (DLL_LOCATION)]
	private static extern IntPtr InsCreateObject(string confFilePath);

	[DllImport (DLL_LOCATION)]
	private static extern void InsDeleteObject(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSendStatusMsgData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSendInternalGPSData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSendNavigationData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSendErrorEstimationData(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetTimeStamps(IntPtr pObj, float simTime, float utcTime);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetPose(IntPtr pObj, float latitude, float longitude, float altitude);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetOrientation(IntPtr pObj, float azimuth, float pitch, float roll);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetAzimuthRate(IntPtr pObj, float azimuthRate);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetVelocity(IntPtr pObj, float northVelocity, float eastVelocity, float downVelocity);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetDistances(IntPtr pObj, float distanceTraveled, float odometerDistance);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetMotionDetected(IntPtr pObj, bool motionDetected);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetInternalGpsFields(IntPtr pObj, short gpsFom, short numOfSatelites);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetDirectionErrors(IntPtr pObj, float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetVelocityErrors(IntPtr pObj, float northVelocityError, float eastVelocityError, float downVelocityError);

	[DllImport (DLL_LOCATION)]
	private static extern void InsSetOrientationErrors(IntPtr pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);

	private IntPtr m_nativeObject;

	public InsWrapper(string confFilePath) {
		this.m_nativeObject = InsCreateObject(confFilePath);
	}

	~InsWrapper() {Dispose(false);}
	
	public void Dispose() { Dispose(true);}

    protected virtual void Dispose(bool bDisposing) {
        if (this.m_nativeObject != IntPtr.Zero) {
            InsDeleteObject(this.m_nativeObject);
            this.m_nativeObject = IntPtr.Zero;
        }

        if (bDisposing) {
            GC.SuppressFinalize(this);
        }
    }

	public void SendStatusMsgData() {
		InsSendStatusMsgData(this.m_nativeObject);
	}

	public void SendInternalGPSData() {
		InsSendInternalGPSData(this.m_nativeObject);
	}

	public void SendNavigationData() {
		InsSendNavigationData(this.m_nativeObject);
	}

	public void SendErrorEstimationData() {
		InsSendErrorEstimationData(this.m_nativeObject);
	}

	public void SetTimeStamps(float simTime, float utcTime) {
		InsSetTimeStamps(this.m_nativeObject, simTime, utcTime);
	}

    // INS navigation data message
    public void SetPose(float latitude, float longitude, float altitude) {
		InsSetPose(this.m_nativeObject, latitude, longitude, altitude);
	}

    public void SetOrientation(float azimuth, float pitch, float roll) {
		InsSetOrientation(this.m_nativeObject, azimuth, pitch, roll);
	}

    public void SetAzimuthRate(float azimuthRate) {
		InsSetAzimuthRate(this.m_nativeObject, azimuthRate);
	}

    public void SetVelocity(float northVelocity, float eastVelocity, float downVelocity) {
		InsSetVelocity(this.m_nativeObject, northVelocity, eastVelocity, downVelocity);
	}

    public void SetDistances(float distanceTraveled, float odometerDistance) {
		InsSetDistances(this.m_nativeObject, distanceTraveled, odometerDistance);
	}

    public void SetMotionDetected(bool motionDetected) {
		InsSetMotionDetected(this.m_nativeObject, motionDetected);
	}

    // INS internal GPS
    public void SetInternalGpsFields(short gpsFom, short numOfSatelites) {
		InsSetInternalGpsFields(this.m_nativeObject, gpsFom, numOfSatelites);
	}

    // INS Errors estimation message
    public void SetDirectionErrors(float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError) {
		InsSetDirectionErrors(this.m_nativeObject, horizontalError, verticalError, northingError, eastingError, altitudeError);
	}

    public void SetVelocityErrors(float northVelocityError, float eastVelocityError, float downVelocityError) {
		InsSetVelocityErrors(this.m_nativeObject, northVelocityError, eastVelocityError, downVelocityError);
	}

    public void SetOrientationErrors(float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
		InsSetOrientationErrors(this.m_nativeObject, azimuthErrorEstimation, pitchErrorEstimation, rollErrorEstimation);
	}
}