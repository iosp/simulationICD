
#include "DgpsData.h"
#include "IWrapper.h"

/**

 * */
class DgpsWrapper : public IWrapper<DgpsData> {
private:
    DgpsData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    DgpsWrapper(const std::string& portName, int baudRate);

    ~DgpsWrapper();

    /**
     * Calls vlp->run
     */ 
    virtual void Run() override;

    /**
     * Take the temporary data and set it to vlp
     */ 
    virtual void SetData() override;

    void SetPosition(double latitude, double longitude, double altitude);

    void SetVelocities(double latSpeed, double longSpeed, double altSpeed);

    void SetTimeStamp(int timeStamp);
};