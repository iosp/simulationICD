
using System;
using System.Runtime.InteropServices;

public class IdanWrapper : IDisposable {
	const String DLL_LOCATION = "libidan";

	[DllImport (DLL_LOCATION)]
	private static extern IntPtr CreateIdanObject(string confFilePath);

	[DllImport (DLL_LOCATION)]
	private static extern void DeleteIdanObject(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void RunIdan(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern void GetIdanData(IntPtr pObj);

/***************************************************** HLC Primary *********************************************** */
	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPShutDownCmd(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPEmergencyCmd(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPSteerCmdMsb(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPSteerCmdLsb(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPGasCmdMsb(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCPGasCmdLsb(IntPtr pObj);

/********************************* HLC Secondary ***********************************************************/
	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCSShutDownCmd(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSRoadLightsApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSHighBeamApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSLightsCutoffApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSParkingLightApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSKeySwitchApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSMotorStarterApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSHornApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSLeftTurnSignalApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSRightTurnSignalApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern bool IsHLCSHazardsApplied(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCSGear(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCSParkingBrake(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCSEmergencyCmd(IntPtr pObj);

	[DllImport (DLL_LOCATION)]
	private static extern byte GetHLCSSacsOnCmd(IntPtr pObj);



	private IntPtr m_nativeObject;

	public IdanWrapper(string confFilePath) {
		this.m_nativeObject = CreateIdanObject(confFilePath);
	}

	~IdanWrapper() {Dispose(false);}
	
	public void Dispose() { Dispose(true);}

    protected virtual void Dispose(bool bDisposing) {
        if (this.m_nativeObject != IntPtr.Zero) {
            //DeleteIdanObject(this.m_nativeObject);
             //this.m_nativeObject = IntPtr.Zero;
        }

        if (bDisposing) {
            GC.SuppressFinalize(this);
        }
    }

	public void Run() {
		RunIdan(this.m_nativeObject);
	}

	public void GetData() {
		GetIdanData(this.m_nativeObject);
	}

/***************************************************** HLC Primary *********************************************** */
	public byte GetHLCPShutDownCmd() {
		return GetHLCPShutDownCmd(this.m_nativeObject);
	}

	public byte GetHLCPEmergencyCmd() {
		return GetHLCPEmergencyCmd(this.m_nativeObject);
	}

	public byte GetHLCPSteerCmdMsb() {
		return GetHLCPSteerCmdMsb(this.m_nativeObject);
	}

	public byte GetHLCPSteerCmdLsb() {
		return GetHLCPSteerCmdLsb(this.m_nativeObject);
	}

	public byte GetHLCPGasCmdMsb() {
		return GetHLCPGasCmdMsb(this.m_nativeObject);
	}

	public byte GetHLCPGasCmdLsb() {
		return GetHLCPGasCmdLsb(this.m_nativeObject);
	}

/********************************* HLC Secondary ***********************************************************/
	public byte GetHLCSShutDownCmd() {
		return GetHLCSShutDownCmd(this.m_nativeObject);
	}

	public bool IsHLCSRoadLightsApplied() {
		return IsHLCSRoadLightsApplied(this.m_nativeObject);
	}

	public bool IsHLCSHighBeamApplied() {
		return IsHLCSHighBeamApplied(this.m_nativeObject);
	}

	public bool IsHLCSLightsCutoffApplied() {
		return IsHLCSLightsCutoffApplied(this.m_nativeObject);
	}

	public bool IsHLCSParkingLightApplied() {
		return IsHLCSParkingLightApplied(this.m_nativeObject);
	}

	public bool IsHLCSKeySwitchApplied() {
		return IsHLCSKeySwitchApplied(this.m_nativeObject);
	}

	public bool IsHLCSMotorStarterApplied() {
		return IsHLCSMotorStarterApplied(this.m_nativeObject);
	}

	public bool IsHLCSHornApplied() {
		return IsHLCSHornApplied(this.m_nativeObject);
	}

	public bool IsHLCSLeftTurnSignalApplied() {
		return IsHLCSLeftTurnSignalApplied(this.m_nativeObject);
	}

	public bool IsHLCSRightTurnSignalApplied() {
		return IsHLCSRightTurnSignalApplied(this.m_nativeObject);
	}

	public bool IsHLCSHazardsApplied() {
		return IsHLCSHazardsApplied(this.m_nativeObject);
	}

	public byte GetHLCSGear() {
		return GetHLCSGear(this.m_nativeObject);
	}

	public byte GetHLCSParkingBrake() {
		return GetHLCSParkingBrake(this.m_nativeObject);
	}

	public byte GetHLCSEmergencyCmd() {
		return GetHLCSEmergencyCmd(this.m_nativeObject);
	}

	public byte GetHLCSSacsOnCmd() {
		return GetHLCSSacsOnCmd(this.m_nativeObject);
	}
}